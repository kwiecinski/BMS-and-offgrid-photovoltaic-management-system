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
#include "adc.h"

#define BALANCE_THRESHOLD 100

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
    
    uint16_t bus_voltage, voltage_24V_diff, voltage_12V;
    ADC_Init();

    while(1)
    {     //SendErrorStatus(AutoFox_INA226_Init(&ina226,INA226_DEFAULT_I2C_ADDRESS, 2,50));
        
        bus_voltage=AutoFox_INA226_GetBusVoltage_V(&ina226);
        //unsigned int ADC_ReadVoltage(void);
        if (bus_voltage%100 < 10) 
        {
           // printf("24V Batt Voltage: %d.0%dV \r\n", bus_voltage / 100, bus_voltage % 100);  // Dodaje zero wiod?ce
        } else 
        {
           // printf("24V Batt voltage  Voltage: %d.%dV \r\n", bus_voltage / 100, bus_voltage % 100);
        }
        
        
        voltage_24V_diff=bus_voltage - DisplayVoltage();
        
        
        if (voltage_24V_diff%100 < 10) 
        {
            printf("24V diff Batt Voltage: %d.0%dV \r\n", voltage_24V_diff / 100, voltage_24V_diff % 100);  // Dodaje zero wiod?ce
        } else 
        {
            printf("24V diff voltage  Voltage: %d.%dV \r\n", voltage_24V_diff / 100, voltage_24V_diff % 100);
            
        }
        
        #include <stdint.h>


    if (voltage_12V > (voltage_24V_diff + BALANCE_THRESHOLD)) {
        BALANCE_BATT_12V_ON;
        printf("balance on 12v \n\r");
    } else {
        BALANCE_BATT_12V_OFF;
        printf("balance off 12v \n\r");
    }

    // Check if 24V cell is higher by more than the threshold
    if (voltage_24V_diff > (voltage_12V + BALANCE_THRESHOLD)) {
        BALANCE_BATT_24V_ON;
         printf("balance on 24v \n\r");
    } else {
        BALANCE_BATT_24V_OFF;
         printf("balance off 24v \n\r");
    }

        
        __delay_ms(1000);
    }
}