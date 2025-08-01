


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

   This library is for STM32 using HAL provided by CubeMX

   In developing this library, besides reading the INA226 spec, I consulted
   the following code:

   * Linux drivers for the INA family (written in C)
   * https://github.com/SV-Zanshin/INA226 (most useful)

   PLATFORM DEPENDENCE
   Embodied in 3 functions related to I2C reading/writing

*/


#ifndef __AUTOFOX_INA226_H__
#define __AUTOFOX_INA226_H__


#include <xc.h>
#include <inttypes.h>
#include <stdbool.h>



static const uint8_t    INA226_DEFAULT_I2C_ADDRESS  = 0b1000000;

//Heads up for the classes declared in this header
struct AutoFox_INA226; //This is the one you will use directly
struct INA226_Registers;
struct INA226_HardCodedChipConst;
struct INA226_DefaultSettings;

static const int INA226_I2C_TIMEOUT = 1000;

//Most functions will return an error status
typedef enum {OK=0, FAIL=-1,
    INA226_TI_ID_MISMATCH = -2,
    INA226_DIE_ID_MISMATCH =-3,
    CONFIG_ERROR = -4,
    I2C_TRANSMISSION_ERROR = -5,
    BAD_PARAMETER = -6,
    NOT_INITIALIZED = -7,
    INVALID_I2C_ADDRESS =-8} status;

typedef struct AutoFox_INA226{
    bool     mInitialized;
    uint8_t  mI2C_Address;
    uint16_t mConfigRegister;        //local copy from the INA226
    uint16_t mCalibrationValue;        //local copy from the INA226
    int32_t  mCurrentMicroAmpsPerBit; //This is the Current_LSB, as defined in the INA266 spec
    int32_t  mPowerMicroWattPerBit;
} AutoFox_INA226;

//=============================================================================

enum eOperatingMode {//Shutdown=0,
                    ShuntVoltageTriggered        = 1,
                    BusVoltageTriggered          = 2,
                    ShuntAndBusTriggered         = 3,
                    Shutdown                     = 4,
                    ShuntVoltageContinuous       = 5,
                    BusVoltageContinuous         = 6,
                    ShuntAndBusVoltageContinuous = 7}; //default

enum eAlertTrigger {ClearTriggers                = 0x0000, //default
                    ShuntVoltageOverLimit        = 0x8000,
                    ShuntVoltageUnderLimit       = 0x4000,
                    BusVoltageOverLimit          = 0x2000,
                    BusVoltageUnderLimit         = 0x1000,
                    PowerOverLimit               = 0x0800,
                    ConversionReady              = 0x0400};

enum eAlertTriggerCause{
                    Unknown=0,
                    AlertFunctionFlag            = 0x10,
                    ConversionReadyFlag          = 0x08,
                    MathOverflowFlag             = 0x04,
                    AlertPolarityBit             = 0x02};
//=============================================================================


void AutoFox_INA226_Constructor(AutoFox_INA226*);
status AutoFox_INA226_CheckI2cAddress(uint8_t aI2C_Address);

//Resets the INA226 and configures it according to the supplied parameters - should be called first.
//status AutoFox_INA226_Init(uint8_t aI2C_Address=0x40, double aShuntResistor_Ohms=0.1, double aMaxCurrent_Amps=3.2767);
status AutoFox_INA226_Init(AutoFox_INA226* this, uint8_t aI2C_Address, uint16_t aShuntResistor_mOhms, uint32_t aMaxCurrent_Amps);

int32_t AutoFox_INA226_GetShuntVoltage_uV(AutoFox_INA226*);
uint16_t AutoFox_INA226_GetBusVoltage_V(AutoFox_INA226* this);
int32_t AutoFox_INA226_GetCurrent_uA(AutoFox_INA226*);
int32_t AutoFox_INA226_GetPower_uW(AutoFox_INA226*);

status AutoFox_INA226_SetOperatingMode(AutoFox_INA226*,enum eOperatingMode aOpMode);
status AutoFox_INA226_Hibernate(AutoFox_INA226*); //Enters a very low power mode, no voltage measurements
status AutoFox_INA226_Wakeup(AutoFox_INA226*);    //Wake-up and enter the last operating mode

//The trigger value is in microwatts or microvolts, depending on the trigger
status AutoFox_INA226_ConfigureAlertPinTrigger(AutoFox_INA226*,enum eAlertTrigger aAlertTrigger, int32_t aValue, bool aLatching);
//status AutoFox_INA226_ResetAlertPin(AutoFox_INA226*);
status AutoFox_INA226_ResetAlertPin(AutoFox_INA226*,enum  eAlertTriggerCause* aAlertTriggerCause_p ); //provides feedback as to what caused the alert

//The parameters for the two functions below are indices into the tables defined in the INA226 spec
//These tables are copied below for your information (caNumSamplesAveraged & caVoltageConvTimeMicroSecs)
status AutoFox_INA226_ConfigureVoltageConversionTime(AutoFox_INA226*,int aIndexToConversionTimeTable);
status AutoFox_INA226_ConfigureNumSampleAveraging(AutoFox_INA226*,int aIndexToSampleAverageTable);
status AutoFox_INA226_Debug_GetConfigRegister(AutoFox_INA226*,uint16_t* aConfigReg_p);

//Private functions

status AutoFox_INA226_WriteRegister(AutoFox_INA226*,uint8_t aRegister, uint16_t aValue);
status AutoFox_INA226_ReadRegister(AutoFox_INA226*,uint8_t aRegister, uint16_t* aValue_p);
status AutoFox_INA226_setupCalibration(AutoFox_INA226* this, uint16_t aShuntResistor_mOhms, uint32_t aMaxCurrent_Amps);
void SendErrorStatus(status err);


extern AutoFox_INA226 ina226; 
#endif //__AUTOFOX_INA226_H__
