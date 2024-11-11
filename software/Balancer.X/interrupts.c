#include <xc.h>
#include "main.h"
#include "interrupts.h"
#include "hw_uart.h"
#include "inits.h"

void Interrupt_Init(void)
{
    //Timer0 Config
    OPTION_REGbits.T0CS=0;      //Internal instruction cycle clock (FOSC/4)
    OPTION_REGbits.PSA=0;       //Prescaler is assigned to the Timer0 module
    OPTION_REGbits.PS=0b000;    //Prescaler Rate Select bits: 1:2
    INTCONbits.T0IE=0;
    
    //TIMER1 Config
    T1CONbits.TMR1ON=0;     //Timer1 Enable
    T1CONbits.TMR1CS=0;     //Clock source - internal
    T1CONbits.T1CKPS=0b00;  //Prescaller 1:1
    
    //Interrupts Global
    INTCONbits.GIE=1;       //Global ISR Enable
    INTCONbits.PEIE=1;      //Peripheral Interrupt Enable
    
}

volatile unsigned int g_timer_led_blink, g_flag;

void __interrupt() 
ISR(void)
{
      
    //////////////////////////////////////////////////////////////////////////
    //
    // Timer0 Interrupt - OVF - 256us
    //
    //////////////////////////////////////////////////////////////////////////

    if (TMR0IE && TMR0IF)
    {
        g_timer_led_blink++;
        if(g_timer_led_blink>=3906)
        {
            if(g_flag)
            {
                STATUS_LED_D18_ON;
                STATUS_LED_D19_OFF;
                g_flag=0;
                
            }else
            {
                STATUS_LED_D18_OFF;
                STATUS_LED_D19_ON;
                g_flag=1;
            }
            
            g_timer_led_blink=0;
        }
        
        TMR0IF=0; 
    }
    


}