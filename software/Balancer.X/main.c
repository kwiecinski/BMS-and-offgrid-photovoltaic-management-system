/* 
 * FILE: main.c
 * DESCRIPTION: Main program body
 * AUTHOR: kwiecinski
 * DATE: 03.2020
 */

#include <xc.h>

#include "main.h"
#include "inits.h"
#include "interrupts.h"
#include "hw_i2c.h"
#include "hw_uart.h"
#include "sw_uart.h"
#include "ina226.h"


AutoFox_INA226 device;  // Tworzymy obiekt typu 'AutoFox_INA226'


// Funkcja wywo?uj?ca i wysy?aj?ca wynik dzia?ania funkcji
void SendBusVoltage(void)
{
    int32_t busVoltage_uV = AutoFox_INA226_GetBusVoltage_uV(&device);  // Odczyt napi?cia
    SendInt32ToUART(busVoltage_uV);  // Wysy?anie wyniku przez UART w formacie ASCII
}

void main(void) 
{  
    Global_Init();
    Interrupt_Init();
    I2C_Init();
    STATUS_LED_D20_OFF;
    STATUS_LED_D21_OFF;
    STATUS_LED_D23_ON;
    STATUS_LED_D5_ON;
    //UART_Init();
    
    //char tab[]="czesc :) \n\r";
    
    while(1)
    {   
       //SendArrayUART_debug(&tab[0],sizeof(tab));
       //SendBusVoltage();
        
         uint16_t theINA226_ID;
        SendErrorStatus(AutoFox_INA226_ReadRegister(&device, 0xFE, &theINA226_ID));
        SendInt32ToUART(theINA226_ID);
        __delay_ms(1000);

    }
}