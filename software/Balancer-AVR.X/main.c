/*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
 */

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
 */
#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "uart_remap.h"
#include "adc_conv.h"
#include "ina226.h"
/*
    Main application
 */

void TCB_ISR_handler(void);
void TCB_ISRc_handler(void);

int main(void)
{
    SYSTEM_Initialize();
    
    //Printf init -------------------------------------------------------------
    stdout = stdout_ptr;
    // ------------------------------------------------------------------------
    
    //INA266 INIT -----------------------------------------------------------------------------------------------
    AutoFox_INA226 ina226;
    AutoFox_INA226_Constructor(&ina226);
    SendErrorStatus(AutoFox_INA226_Init(&ina226, INA226_DEFAULT_I2C_ADDRESS, 100, 5));
    SendErrorStatus(AutoFox_INA226_ConfigureVoltageConversionTime(&ina226, 0b111)); //sample time 8.244ms
    SendErrorStatus(AutoFox_INA226_ConfigureNumSampleAveraging(&ina226, 0b010));
    //-----------------------------------------------------------------------------------------------------------
    DAC0_SetOutput(1);
    
    TCD0_Start();
    
    while (1)
    {
        uint16_t voltage_bus_24V, voltage_batt_12V_high, voltage_batt_12V_low;

        //voltage_bus_24V = AutoFox_INA226_GetBusVoltage_V(&ina226);
        //voltage_batt_12V_low = Get_ADC_Voltage(ADC_CHANNEL_12V_BATT) / 1000;
        //voltage_batt_12V_high = voltage_bus_24V - voltage_batt_12V_low;

       // printf("24V:%u \r\n", voltage_batt_12V_high);
       // printf("12V:%u \r\n", voltage_batt_12V_low);
       // printf("BUS:%u \r\n", voltage_bus_24V);
        printf("GetBusVoltage:%u mV \r\n", AutoFox_INA226_GetBusVoltage_V(&ina226));
        printf("GetShuntVoltage:%ld mV \r\n", AutoFox_INA226_GetShuntVoltage_uV(&ina226) / 1000);
        printf("GetCurrent:%ld mA \r\n\r\n", AutoFox_INA226_GetCurrent_uA(&ina226) / 1000);
        DELAY_milliseconds(2000);
        
       // BALANCE_12V_SetHigh();
       //  BALANCE_24V_SetHigh();
DELAY_milliseconds(2000);
       // BALANCE_12V_SetLow();
       // BALANCE_24V_SetLow();
       

    }
}

void TCB_ISR_handler(void)
{
}



