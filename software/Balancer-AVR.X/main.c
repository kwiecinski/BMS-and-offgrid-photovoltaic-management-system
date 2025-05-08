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
#include "balance_cells.h"


/*
    Main application
 */


void TCB_ISR_handler(void);
void TCB_ISRc_handler(void);

AutoFox_INA226 ina226;

int main(void)
{
    SYSTEM_Initialize();

    //Printf init -------------------------------------------------------------
    stdout = stdout_ptr;
    // ------------------------------------------------------------------------

    //disable_balancer_24V_WOB_output();
    //disable_balancer_12V_WOB_output();
    while (1)
    {


        uint16_t voltage_bus_24V, voltage_batt_12V_high, voltage_batt_12V_low;

        voltage_bus_24V = AutoFox_INA226_GetBusVoltage_V(&ina226);
        voltage_batt_12V_low = Get_ADC_Voltage(ADC_CHANNEL_12V_BATT)/10;
        voltage_batt_12V_high = voltage_bus_24V - voltage_batt_12V_low;

        printf("24V:%u mV \r\n", voltage_batt_12V_high);
        printf("12V:%u mV \r\n", voltage_batt_12V_low);
        printf("BUS INA:%u   \r\n\r\n", voltage_bus_24V);

        //set_PWM_WOA_24V(DECREASE);
      //  set_PWM_WOB_12V(INCREASE);
        DELAY_milliseconds(100);
balance_cells();
   printf("TCD0.CMPASET: %d \n\r", TCD0.CMPASET);
       printf("TCD0.CMPBSETb: %d \n\r", TCD0.CMPBSET);
        //set_PWM_WOB_12V(DECREASE);
        //set_pwm_frequency(3000);
        //set_PWM_WOB(DECREASE);
        //set_PWM_WOA(DECREASE);
        // set_PWM_WOB(DECREASE);
        // BALANCE_12V_SetHigh();
        // BALANCE_24V_SetHigh();
        // BALANCE_12V_SetLow();
        // BALANCE_24V_SetLow();
  

    }
}

void TCB_ISR_handler(void)
{
}



