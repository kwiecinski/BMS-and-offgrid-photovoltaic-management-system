/* 
 * FILE: main.c
 * DESCRIPTION: Main program body
 * AUTHOR: kwiecinski
 * DATE: 03.2020
 */

#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include "main.h"
#include "inits.h"
#include "interrupts.h"
#include "hw_i2c.h"
#include "hw_uart.h"
#include "sw_uart.h"
#include "ina226.h"
#include "adc.h"

#define BALANCE_THRESHOLD 5

void main(void)
{

    AutoFox_INA226 ina226;
    AutoFox_INA226_Constructor(&ina226);

    Global_Init();
    Interrupt_Init();
    I2C_Init();
    STATUS_LED_D20_OFF;
    STATUS_LED_D21_OFF;
    STATUS_LED_D23_ON;
    STATUS_LED_D5_ON;

    //UART_Init();
    SendErrorStatus(AutoFox_INA226_Init(&ina226, INA226_DEFAULT_I2C_ADDRESS, 2, 50));
    SendErrorStatus(AutoFox_INA226_ConfigureVoltageConversionTime(&ina226, 0b111)); //sample time 8.244ms
    SendErrorStatus(AutoFox_INA226_ConfigureNumSampleAveraging(&ina226, 0b010));

    uint16_t voltage_bus_24V, voltage_batt_12V_high, voltage_batt_12V_low;
    
    ADC_Init();

    while (1)
{           
            voltage_bus_24V = AutoFox_INA226_GetBusVoltage_V(&ina226);
            voltage_batt_12V_low = read_voltage();
            voltage_batt_12V_high = voltage_bus_24V - voltage_batt_12V_low;
        
            printf("24V:%u \r\n", voltage_batt_12V_high);
            printf("12V:%u \r\n", voltage_batt_12V_low);
            printf("BUS:%u \r\n\r\n", voltage_bus_24V);

        if (voltage_batt_12V_low > (voltage_batt_12V_high + BALANCE_THRESHOLD))
        {
            while (1)
            {
                BALANCE_BATT_12V_ON;
                
                __delay_ms(1000);
                 BALANCE_BATT_12V_OFF;
                 __delay_ms(5000);
                 
                voltage_bus_24V = AutoFox_INA226_GetBusVoltage_V(&ina226);
                voltage_batt_12V_low = read_voltage();
                voltage_batt_12V_high = voltage_bus_24V - voltage_batt_12V_low;

                 printf("24V:%u \r\n", voltage_batt_12V_high);
                 printf("12V:%u \r\n", voltage_batt_12V_low);
                 printf("BUS:%u \r\n\r\n", voltage_bus_24V);


                if (voltage_batt_12V_low < (voltage_batt_12V_high + BALANCE_THRESHOLD))
                {
                     BALANCE_BATT_12V_OFF;
                    break;
                }
            }
        }
        //__delay_ms(1000);
    }
}