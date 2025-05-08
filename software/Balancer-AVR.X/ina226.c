/*
Library to facilitate use of the INA226 Voltage, Current & Power monitor
from Texas Instruments.
See spec. here: http://www.ti.com/lit/ds/symlink/ina226.pdf.

Copyright [2018] [AutoFox] autofoxsys@gmail.com

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

This library is for Arduino.

In developing this library, besides reading the INA226 spec, I consulted
the following code:

* Linux drivers for the INA family (written in C)
* https://github.com/SV-Zanshin/INA226 (most useful)

PLATFORM DEPENDENCE
Embodied in 3 functions related to I2C reading/writing

*/

#include <xc.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "ina226.h"
#include "mcc_generated_files/timer/delay.h"



//=============================================================================
//Some helper macros for this source file

#define CALL_FN(fn)              \
    do {                         \
        status s = (fn);         \
        if (s != OK) {           \
            return s;            \
        }                        \
    } while (0)

#define CHECK_INITIALIZED(); if(!this->mInitialized) return NOT_INITIALIZED;

//=============================================================================

static const uint8_t    INA226_CONFIG              = 0x00;
static const uint8_t    INA226_SHUNT_VOLTAGE       = 0x01; // readonly
static const uint8_t    INA226_BUS_VOLTAGE         = 0x02; // readonly
static const uint8_t    INA226_POWER               = 0x03; // readonly
static const uint8_t    INA226_CURRENT             = 0x04; // readonly
static const uint8_t    INA226_CALIBRATION         = 0x05;
static const uint8_t    INA226_MASK_ENABLE         = 0x06;
static const uint8_t    INA226_ALERT_LIMIT         = 0x07;
static const uint8_t    INA226_MANUFACTURER_ID     = 0xFE; // readonly
static const uint8_t    INA226_DIE_ID              = 0xFF; // readonly


//=============================================================================

static const int32_t    INA226_BUS_VOLTAGE_LSB     = 1231; //1250uV per bit
//static const int32_t    INA226_SHUNT_VOLTAGE_LSB   = 2500;    //2500 nano volts per bit (=2.5uV)
static const int32_t    INA226_POWER_LSB_FACTOR    = 25;
static const uint16_t   INA226_MANUFACTURER_ID_K   = 0x5449;
static const uint16_t   INA226_DIE_ID_K            = 0x2260;
//static const uint16_t   INA226_CONFIG_RESET_VALUE  = 0x4127; // value of config reg after a reset

//=============================================================================


static const uint16_t   INA226_CONFIG_DEFAULT       = 0x4527; // Our default config reg settings
//=============================================================================
const uint16_t cResetCommand                = 0x8000;
const uint16_t cOperatingModeMask           = 0x0007;
const uint16_t cAlertPinModeMask            = 0xFC00;
const uint16_t cAlertCauseMask              = 0x001E;
const uint16_t cAlertLatchingMode           = 0x0001;
const uint16_t cSampleAvgMask               = 0x0E00;
const uint16_t cBusVoltageConvTimeMask      = 0x01C0;
const uint16_t cShuntVoltageConvTimeMask    = 0x0038;
const int      cSampleAvgIdxShift           = 9;
const int      cBusVoltConvTimeIdxShift     = 6;
const int      cShuntVoltConvTimeIdxShift   = 3;
const int      cMaxSampleAvgTblIdx          = 7;    //occupies 3 bit positions
const int      cMaxConvTimeTblIdx           = 7; //occupies 3 bit positions
//=============================================================================

void AutoFox_INA226_Constructor(AutoFox_INA226* this)
{
	this->mInitialized = false;
	this->mI2C_Address = INA226_DEFAULT_I2C_ADDRESS;
	this->mConfigRegister = 0;
	this->mCalibrationValue = 0;
	this->mCurrentMicroAmpsPerBit = 0;
	this->mPowerMicroWattPerBit = 0;
}

//----------------------------------------------------------------------------
status AutoFox_INA226_Init(AutoFox_INA226* this, uint8_t aI2C_Address, uint16_t aShuntResistor_mOhms, uint32_t aMaxCurrent_Amps)
{
    this->mInitialized = false;

    // Check if there's a device (any I2C device) at the specified address.
    CALL_FN( AutoFox_INA226_CheckI2cAddress(aI2C_Address) );



    // Good so far, check that it's an INA226 device atthe specified address.
    uint16_t theINA226_ID;
    CALL_FN( AutoFox_INA226_ReadRegister(this, INA226_MANUFACTURER_ID, &theINA226_ID) );
    if(theINA226_ID != INA226_MANUFACTURER_ID_K){
        return INA226_TI_ID_MISMATCH; // Expected to find TI manufacturer ID
    }
    CALL_FN( AutoFox_INA226_ReadRegister(this, INA226_DIE_ID, &theINA226_ID) );
    if(theINA226_ID != INA226_DIE_ID_K){ 
        return INA226_DIE_ID_MISMATCH; // Expected to find INA226 device ID
    }
    this->mI2C_Address = aI2C_Address;

    // Reset the INA226 device
    CALL_FN( AutoFox_INA226_WriteRegister(this, INA226_CONFIG, cResetCommand) );
    // Now set our own default configuration (you can redefine this constant in the header, as needed)
    CALL_FN( AutoFox_INA226_WriteRegister(this, INA226_CONFIG, INA226_CONFIG_DEFAULT) );
    // Read back the configuration register and check that it matches
    CALL_FN( AutoFox_INA226_ReadRegister(this, INA226_CONFIG, &(this->mConfigRegister)) );  
    if(this->mConfigRegister != INA226_CONFIG_DEFAULT){       
        return CONFIG_ERROR;
    }
    // Set up the calibration register and calculate scaling factors
    CALL_FN( AutoFox_INA226_setupCalibration(this, aShuntResistor_mOhms, aMaxCurrent_Amps) );

    this->mInitialized = true;
    return OK;
}

//----------------------------------------------------------------------------

status AutoFox_INA226_setupCalibration(AutoFox_INA226* this, uint16_t aShuntResistor_mOhms, uint32_t aMaxCurrent_Amps)
{
    // Calculate Current_LSB in microamperes per bit to maximize resolution.
    // The max positive value of the INA226 current register is 32767.
    // Therefore, we calculate the Current_LSB as (aMaxCurrent_Amps * 1,000,000 uA) / 32767
    uint32_t theCurrentLSB_uA = (aMaxCurrent_Amps * 1000000 + 32766) / 32767; // Rounded up

    // Calculate calibration register value based on the shunt resistor in milliOhms.
    // Using a fixed point equivalent of the formula (0.00512 / (aShuntResistor_Ohms * Current_LSB))
    // where 0.00512 is converted to integer form by multiplying by 1,000,000.
    uint32_t theCal = (5120000 + (aShuntResistor_mOhms * theCurrentLSB_uA) / 2) / 
                      (aShuntResistor_mOhms * theCurrentLSB_uA); // Rounded

    // Set the calibration and power factors
    this->mCurrentMicroAmpsPerBit = (int32_t)theCurrentLSB_uA;
    this->mCalibrationValue = (uint16_t)theCal;
    this->mPowerMicroWattPerBit = this->mCurrentMicroAmpsPerBit * INA226_POWER_LSB_FACTOR;

    // Write calibration value to the device
    return AutoFox_INA226_WriteRegister(this, INA226_CALIBRATION, this->mCalibrationValue);
}

//----------------------------------------------------------------------------
//Check if a device exists at the specified I2C address

status AutoFox_INA226_CheckI2cAddress(uint8_t aI2C_Address)
{
    //Address is shifted one bit left because of R/W bit

    TWI0_Write(aI2C_Address,NULL,0);
    while (TWI0_IsBusy())
    {
        TWI0_Tasks();
    }
    
    if (TWI0_ErrorGet() == I2C_ERROR_NONE)
    {
        return OK;
    }

    return INVALID_I2C_ADDRESS;
}

//----------------------------------------------------------------------------

status AutoFox_INA226_ReadRegister(AutoFox_INA226* this, uint8_t aRegister, uint16_t* aValue_p)
{
    *aValue_p = 0;

    uint8_t output[3] = {0, 0, 0};

    TWI0_Write(this->mI2C_Address, &aRegister, 1);
    
    while (TWI0_IsBusy())
    {
        TWI0_Tasks();
    }
    
    TWI0_Read(this->mI2C_Address, &output[0], 2);

    while (TWI0_IsBusy())
    {
        TWI0_Tasks();
    }
    
    *aValue_p = (output[0] << 8) | output[1];
    return OK;
}

//----------------------------------------------------------------------------
status AutoFox_INA226_WriteRegister(AutoFox_INA226* this, uint8_t aRegister, uint16_t aValue)
{
    uint8_t buffer[3];
    buffer[0] = aRegister;
    buffer[1] = (uint8_t)((aValue >> 8) & 0xFF); 
    buffer[2] = (uint8_t)(aValue & 0xFF);         

    TWI0_Write(this->mI2C_Address,&buffer[0],3);
   while (TWI0_IsBusy())
    {
        TWI0_Tasks();
    }
    return OK;
}
//----------------------------------------------------------------------------
int32_t AutoFox_INA226_GetShuntVoltage_uV(AutoFox_INA226* this)
{
	//The value retrieved from the INA226 for the shunt voltage
	//needs to be multiplied by 2.5 to yield the value in microvolts.
	//As I don't want to use floating point multiplication I will take the value
	//divide it by 2 (shift right) and add that to 2 times the original value
	//(shift left).
	int16_t theRegisterValue=0;
	int32_t theResult;
	AutoFox_INA226_ReadRegister(this,INA226_SHUNT_VOLTAGE, (uint16_t*)&theRegisterValue);
	theResult = (int32_t)theRegisterValue>>1;
	theResult+= (int32_t)theRegisterValue<<1;
	return theResult;
}
//----------------------------------------------------------------------------
uint16_t AutoFox_INA226_GetBusVoltage_V(AutoFox_INA226* this)
{
    uint16_t theRegisterValue = 0;
    AutoFox_INA226_ReadRegister(this, INA226_BUS_VOLTAGE, &theRegisterValue);
    return (uint16_t)(((uint32_t)theRegisterValue * INA226_BUS_VOLTAGE_LSB)/10000);
}


//----------------------------------------------------------------------------
int32_t AutoFox_INA226_GetCurrent_uA(AutoFox_INA226* this)
{
	int16_t theRegisterValue=0; // signed register, result in mA
	AutoFox_INA226_ReadRegister(this,INA226_CURRENT, (uint16_t*)&theRegisterValue);
	return (int32_t)theRegisterValue * this->mCurrentMicroAmpsPerBit;
}
//----------------------------------------------------------------------------
int32_t AutoFox_INA226_GetPower_uW(AutoFox_INA226* this)
{
	uint16_t theRegisterValue=0;
	int32_t theReturnValue;
	AutoFox_INA226_ReadRegister(this,INA226_POWER, &theRegisterValue);
	theReturnValue = (int32_t)theRegisterValue * this->mPowerMicroWattPerBit;
	return theReturnValue;
}
//----------------------------------------------------------------------------
status AutoFox_INA226_Hibernate(AutoFox_INA226* this)
{
	CHECK_INITIALIZED();
	//Make a most recent copy of the configuration register, which also contains
	//The operating mode (we need a copy of this for when we come out of sleep)
	CALL_FN( AutoFox_INA226_ReadRegister(this,INA226_CONFIG, &(this->mConfigRegister)) );

	//Zero out the operating more, this will put the INA226 into shutdown
	uint16_t theTempConfigValue = this->mConfigRegister & ~(cOperatingModeMask);

	return AutoFox_INA226_WriteRegister(this,INA226_CONFIG, theTempConfigValue);
}
//----------------------------------------------------------------------------
status AutoFox_INA226_Wakeup(AutoFox_INA226* this)
{
	CHECK_INITIALIZED();
	//Write most recent copy of the calibration register - which should restore
	//the most operating mode that was active before hibernation.  Quick check to test if by
	//any chance the last operating mode was a hibernation and in that case set to 
	//ShuntAndBusVoltageContinuous.
	uint16_t theLastOperatingMode = this->mConfigRegister & cOperatingModeMask;
	if(theLastOperatingMode == Shutdown ||
		theLastOperatingMode == 0){
			this->mConfigRegister &= ~cOperatingModeMask;
			this->mConfigRegister |= ShuntAndBusVoltageContinuous;
	}

	return AutoFox_INA226_WriteRegister(this,INA226_CONFIG, this->mConfigRegister);
}
//----------------------------------------------------------------------------
status AutoFox_INA226_SetOperatingMode(AutoFox_INA226* this, enum eOperatingMode aOpMode)
{
	CHECK_INITIALIZED();
	CALL_FN( AutoFox_INA226_ReadRegister(this,INA226_CONFIG, &(this->mConfigRegister)) );

	//Zero out the existing mode then OR in the new mode
	this->mConfigRegister  &= ~(cOperatingModeMask);
	this->mConfigRegister  |= (uint16_t)aOpMode;

	return AutoFox_INA226_WriteRegister(this,INA226_CONFIG, this->mConfigRegister);
}
//----------------------------------------------------------------------------
status  AutoFox_INA226_ConfigureAlertPinTrigger(AutoFox_INA226* this, enum eAlertTrigger aAlertTrigger, int32_t aValue, bool aLatching)
{
	uint16_t theMaskEnableRegister;

	CHECK_INITIALIZED();
	CALL_FN( AutoFox_INA226_ReadRegister(this,INA226_MASK_ENABLE, &theMaskEnableRegister) );

	//Clear the current configuration for the alert pin
	theMaskEnableRegister &= ~ cAlertPinModeMask;
	//...and prepare the new alert configuration (we'll actually set it down below)
	theMaskEnableRegister |= (uint16_t)aAlertTrigger;
	if(aLatching){
		theMaskEnableRegister |= cAlertLatchingMode;
	}
    
    

	//We need to convert the value supplied (parameter) for the trigger to an INA226 register value.
	//The supplied value could be a shunt voltage, bus voltage or power reading.  All values are
	//in micro units (i.e. microvolts or microamps).
	//Remember that when we get any reading (voltage, current or power) from the INA226 we convert
	//it from the INA226's internal regisister representation (check the functions above).  We
	//need to do the inverse conversion when providing a value back to the INA226 to act as a trigger
	//value.

	int32_t theAlertValue=0;

	switch(aAlertTrigger){
	case PowerOverLimit:
		//back convert to INA226 representation for power (in microWatts)
		theAlertValue = (aValue / this->mPowerMicroWattPerBit);
		break;
	case ClearTriggers:
	case ConversionReady:
		//not a voltage or a power, so we don't care about the trigger value
		theAlertValue = 0;
		break;
	case ShuntVoltageOverLimit:
	case ShuntVoltageUnderLimit:
		//theAlertValue = ((double)aValue / ((double)(INA226_SHUNT_VOLTAGE_LSB)/1000.0));
		theAlertValue = (aValue<<1)/5; //same as aValue/2.5
		break;
	case BusVoltageOverLimit:
	case BusVoltageUnderLimit:
		theAlertValue = (aValue / INA226_BUS_VOLTAGE_LSB);
		break;
	default:
		return BAD_PARAMETER;
	}


	//before we set the new config for the alert pin, set the value that will trigger the alert
	CALL_FN( AutoFox_INA226_WriteRegister(this,INA226_ALERT_LIMIT, (int16_t)theAlertValue) );
	//Now set the trigger mode.
	return AutoFox_INA226_WriteRegister(this,INA226_MASK_ENABLE, theMaskEnableRegister);
}
//----------------------------------------------------------------------------
//status AutoFox_INA226_ResetAlertPin(AutoFox_INA226* this)
//{
//	CHECK_INITIALIZED();
//	uint16_t theDummyValue;
//	//Reading the Mask/Enable register will reset the alert pin
//	return AutoFox_INA226_ReadRegister(this,INA226_MASK_ENABLE, theDummyValue);
//}
//----------------------------------------------------------------------------
status AutoFox_INA226_ResetAlertPin(AutoFox_INA226* this, enum  eAlertTriggerCause* aAlertTriggerCause_p )
{
	//preset the return parameter in case the function fails
	*aAlertTriggerCause_p = Unknown;
	CHECK_INITIALIZED();

	uint16_t theTriggerCause;
	//Reading the Mask/Enable register will reset the alert pin and provide us with the
	//cause of the alert
	CALL_FN( AutoFox_INA226_ReadRegister(this,INA226_MASK_ENABLE, &theTriggerCause) );

	//Mask just the bit that interests us (cause of the alert)
	theTriggerCause &= cAlertCauseMask;

	//Cast the trigger cause to the return parameter type
	*aAlertTriggerCause_p = theTriggerCause;
	return OK;
}
//----------------------------------------------------------------------------
status AutoFox_INA226_ConfigureVoltageConversionTime(AutoFox_INA226* this, int aIndexToConversionTimeTable)
{
	CHECK_INITIALIZED();

	if(aIndexToConversionTimeTable < 0 || aIndexToConversionTimeTable > cMaxConvTimeTblIdx ){
		return BAD_PARAMETER;
	}

	//Read the configuration register
	CALL_FN( AutoFox_INA226_ReadRegister(this,INA226_CONFIG, &(this->mConfigRegister)) );
	//Clear the current voltage sampling time settings
	this->mConfigRegister &= ~(cBusVoltageConvTimeMask | cShuntVoltageConvTimeMask);
	//Set the new values
	uint16_t theMergedBusAndShuntConvTimeIndicies = 
		((uint16_t)aIndexToConversionTimeTable << cBusVoltConvTimeIdxShift) |
		((uint16_t)aIndexToConversionTimeTable << cShuntVoltConvTimeIdxShift);

	this->mConfigRegister |= theMergedBusAndShuntConvTimeIndicies;

	return AutoFox_INA226_WriteRegister(this,INA226_CONFIG, this->mConfigRegister);
}
//----------------------------------------------------------------------------
status AutoFox_INA226_ConfigureNumSampleAveraging(AutoFox_INA226* this, int aIndexToSampleAverageTable)
{
	CHECK_INITIALIZED();

	if(aIndexToSampleAverageTable < 0 || aIndexToSampleAverageTable > cMaxSampleAvgTblIdx ){
		return BAD_PARAMETER;
	}

	//Read the configuration register
	CALL_FN( AutoFox_INA226_ReadRegister(this,INA226_CONFIG, &(this->mConfigRegister)) );
	//Clear the current averaging value
	this->mConfigRegister &= ~cSampleAvgMask;
	//Set the new value
	this->mConfigRegister |= (aIndexToSampleAverageTable<<cSampleAvgIdxShift);

	return AutoFox_INA226_WriteRegister(this,INA226_CONFIG, this->mConfigRegister);
}
//----------------------------------------------------------------------------
status AutoFox_INA226_Debug_GetConfigRegister(AutoFox_INA226* this, uint16_t* aConfigReg_p)
{
	CHECK_INITIALIZED();
	//Read the configuration register
	return AutoFox_INA226_ReadRegister(this,INA226_CONFIG, aConfigReg_p);
}





void SendErrorStatus(status err)
{
    char *errorMsg;

    // Wybieramy odpowiedni komunikat w zale?no?ci od warto?ci b??du
    switch(err)
    {
        case OK:
            errorMsg = "OK \r\n";
            break;
        case FAIL:
            errorMsg = "FAIL \r\n";
            break;
        case INA226_TI_ID_MISMATCH:
            errorMsg = "INA226_TI_ID_MISMATCH \r\n";
            break;
        case INA226_DIE_ID_MISMATCH:
            errorMsg = "INA226_DIE_ID_MISMATCH \r\n";
            break;
        case CONFIG_ERROR:
            errorMsg = "CONFIG_ERROR \r\n";
            break;
        case I2C_TRANSMISSION_ERROR:
            errorMsg = "I2C_TRANSMISSION_ERROR \r\n";
            break;
        case BAD_PARAMETER:
            errorMsg = "BAD_PARAMETER \r\n";
            break;
        case NOT_INITIALIZED:
            errorMsg = "NOT_INITIALIZED \r\n";
            break;
        case INVALID_I2C_ADDRESS:
            errorMsg = "INVALID_I2C_ADDRESS \r\n";
            break;
        default:
            errorMsg = "UNKNOWN_ERROR \r\n";
            break;
    }
        printf("%s", errorMsg);  
        
}