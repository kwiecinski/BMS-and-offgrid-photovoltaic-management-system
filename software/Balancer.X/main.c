/* 
 * FILE: main.c
 * DESCRIPTION: Main program body
 * AUTHOR: kwiecinski
 * DATE: 03.2020
 */

#include <xc.h>
#include <stdio.h>
#include "main.h"
#include "inits.h"
#include "interrupts.h"
#include "hw_i2c.h"
#include "hw_uart.h"
#include "sw_uart.h"
#include "ina226.h"
#include "tinyprintf.h"

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
    SendErrorStatus(AutoFox_INA226_Init(&ina226,INA226_DEFAULT_I2C_ADDRESS, 2,50));
    SendErrorStatus(AutoFox_INA226_ConfigureVoltageConversionTime(&ina226, 0b111)); //sample time 8.244ms
    SendErrorStatus(AutoFox_INA226_ConfigureNumSampleAveraging(&ina226, 0b010));
    
    uint16_t bus_voltage;
    
    while(1)
    {     //SendErrorStatus(AutoFox_INA226_Init(&ina226,INA226_DEFAULT_I2C_ADDRESS, 2,50));
        
        bus_voltage=AutoFox_INA226_GetBusVoltage_V(&ina226);
        
    // tfp_printf("Bus Voltage: %u.%u \r\n", bus_voltage / 100, bus_voltage % 100);

          // printf("Bus Voltage: %u \r\n",bus_voltage);
        
        __delay_ms(1000);
    }
}