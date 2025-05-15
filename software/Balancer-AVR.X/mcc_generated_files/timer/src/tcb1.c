/**
  * TCB1 Generated Driver File
  *
  * @file tcb1.c
  *
  * @ingroup tcb1
  *
  * @brief This file contains the API implementation for the TCB1 module driver.
  *
  * @version TCB1 Driver Version 1.1.2
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

#include "../tcb1.h"

const struct TMR_INTERFACE TCB1_Interface = {
    .Initialize = TCB1_Initialize,
    .Start = TCB1_Start,
    .Stop = TCB1_Stop,
    .PeriodCountSet = TCB1_Write,
    .TimeoutCallbackRegister = NULL,
    .Tasks = NULL
};




void TCB1_Initialize(void)
{
    //Compare or Capture
    TCB1.CCMP = 0x8CA0;

    //Count
    TCB1.CNT = 0x0;

    //ASYNC disabled; CCMPEN enabled; CCMPINIT disabled; CNTMODE PWM8; 
    TCB1.CTRLB = 0x17;
    
    //DBGRUN disabled; 
    TCB1.DBGCTRL = 0x0;

    //CAPTEI disabled; EDGE disabled; FILTER disabled; 
    TCB1.EVCTRL = 0x0;

    //CAPT disabled; OVF disabled; 
    TCB1.INTCTRL = 0x0;

    //CAPT disabled; OVF disabled; 
    TCB1.INTFLAGS = 0x0;

    //Temporary Value
    TCB1.TEMP = 0x0;

    //CASCADE disabled; CLKSEL DIV2; ENABLE enabled; RUNSTDBY disabled; SYNCUPD disabled; 
    TCB1.CTRLA = 0x3;

}

void TCB1_Start(void)
{
    TCB1.CTRLA |= TCB_ENABLE_bm; /* Start Timer */
}

void TCB1_Stop(void)
{
    TCB1.CTRLA &= ~TCB_ENABLE_bm; /* Stop Timer */
}

void TCB1_Write(uint16_t timerVal)
{
    TCB1.CNT = timerVal;
}

uint16_t TCB1_Read(void)
{
    uint16_t readVal;

    readVal = TCB1.CNT;

    return readVal;
}

void TCB1_EnableCaptInterrupt(void)
{
    TCB1.INTCTRL |= TCB_CAPT_bm; /* Capture or Timeout: enabled */
}

void TCB1_EnableOvfInterrupt(void)
{
	TCB1.INTCTRL |= TCB_OVF_bm; /* Overflow Interrupt: enabled */
}

void TCB1_DisableCaptInterrupt(void)
{
    TCB1.INTCTRL &= ~TCB_CAPT_bm; /* Capture or Timeout: disabled */
}

void TCB1_DisableOvfInterrupt(void)
{
	TCB1.INTCTRL &= ~TCB_OVF_bm; /* Overflow Interrupt: disabled */

}

inline void TCB1_ClearCaptInterruptFlag(void)
{
    TCB1.INTFLAGS &= ~TCB_CAPT_bm;
}

inline void TCB1_ClearOvfInterruptFlag(void)
{
	TCB1.INTFLAGS &= ~TCB_OVF_bm;

}

inline bool TCB1_IsCaptInterruptEnabled(void)
{
    return ((TCB1.INTCTRL & TCB_CAPT_bm) > 0);
}

inline bool TCB1_IsOvfInterruptEnabled(void)
{
        return ((TCB1.INTCTRL & TCB_OVF_bm) > 0);
}

/* 8-bit PWM API's */      
void TCB1_PWM_Enable(void)
{
    TCB1.CTRLA |= TCB_ENABLE_bm;
}

void TCB1_PWM_Disable(void)
{
    TCB1.CTRLA &= ~TCB_ENABLE_bm;
}

void TCB1_load_counter(TCB1_pwm_register_t counter_value)
{
    TCB1.CNT = counter_value;
}

void TCB1_load_top(TCB1_pwm_register_t top_value)
{
    TCB1.CCMPL = top_value;
}

void TCB1_load_duty_cycle(TCB1_pwm_register_t duty_value)
{
	TCB1.CTRLA &= ~TCB_ENABLE_bm;
	TCB1.CCMPH = duty_value;
	TCB1.CNT   = 0;
	TCB1.CTRLA |= TCB_ENABLE_bm;
}
