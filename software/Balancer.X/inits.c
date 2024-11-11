#include <xc.h>
#include "inits.h"


void Global_Init(void)
{
    //Ocillator Config - 8MHz Internal
    OSCCONbits.IRCF=0b111;
    OSCCONbits.OSTS=0;
    OSCCONbits.SCS=1;
    
    //PORTA pins as digital I/O;
    //ANSEL: Analog select between analog or digital function on pins AN <7:0>, respectively.
    //1 = Analog input. Pin is assigned as analog input(1).
    //0 = Digital I/O. Pin is assigned to port or special function.
   
    ANSEL=0b10101111;     //for inputs AN0-7
    ANSELH=0x00;          //for inputs AN8-13
    
    TRISC0=0;    //STATUS LED D23
    TRISC1=0;    //PWM out discharge battery 
    TRISC2=0;    //PWM out charge battery
    TRISC3=0;    //SCL - INA226 clock
    TRISC4=1;    //SDA - INA226 data
    TRISC5=0;    //RS485 output/input enable
    TRISC6=0;    //RS485 TX
    TRISC7=1;    //RS485 RX
        
    TRISA0=1;    //ADC INPUT: VBAT 12V
    TRISA1=1;    //ADC INPUT: TEMP BATT 1
    TRISA2=1;    //ADC INPUT: TEMP BATT 2
    TRISA3=1;    //VREF 2.5V INPUT
    TRISA4=0;    //DEBUG UART TX
    TRISA5=1;    //ADC INPUT: TEMP HEATSINK 1
    TRISA6=0;    //STATUS LED D5
    TRISA7=1;    //ADC INPUT: TEMP HEATSINK 2
    
    TRISB0=0;    //PWM FOR HEATSINK FAN 1
    TRISB1=0;    //PWM FOR HEATSINK FAN 2
    TRISB2=0;    //STATUS LED D19
    TRISB3=0;    //STATUS LED D18
    TRISB4=0;    //BALANCE BATT ENABLE 12v
    TRISB5=0;    //BALANCE BATT ENABLE 24v
    TRISB6=0;    //PGC PROGRAMMING INTERFACE / STATUS LED D21
    TRISB7=0;    //PGD PROGRAMMING INTERFACE / STATUS LED D20
    
    BALANCE_BATT_24V_OFF;
    BALANCE_BATT_12V_OFF;
}
