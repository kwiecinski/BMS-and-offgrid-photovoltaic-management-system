/**
  * TCB2 Generated Driver File
  *
  * @file tcb2.c
  *
  * @ingroup tcb2
  *
  * @brief This file contains the API implementation for the TCB2 module driver.
  *
  * @version TCB2 Driver Version 1.1.2
*/
/*
� [2025] Microchip Technology Inc. and its subsidiaries.

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

#include "../tcb2.h"

const struct TMR_INTERFACE TCB2_Interface = {
    .Initialize = TCB2_Initialize,
    .Start = TCB2_Start,
    .Stop = TCB2_Stop,
    .PeriodCountSet = TCB2_Write,
    .TimeoutCallbackRegister = NULL,
    .Tasks = NULL
};




void TCB2_Initialize(void)
{
    //Compare or Capture
    TCB2.CCMP = 0x11941;

    //Count
    TCB2.CNT = 0x0;

    //ASYNC disabled; CCMPEN disabled; CCMPINIT disabled; CNTMODE INT; 
    TCB2.CTRLB = 0x0;
    
    //DBGRUN disabled; 
    TCB2.DBGCTRL = 0x0;

    //CAPTEI disabled; EDGE disabled; FILTER disabled; 
    TCB2.EVCTRL = 0x0;

    //CAPT disabled; OVF disabled; 
    TCB2.INTCTRL = 0x0;

    //CAPT disabled; OVF disabled; 
    TCB2.INTFLAGS = 0x0;

    //Temporary Value
    TCB2.TEMP = 0x0;

    //CASCADE disabled; CLKSEL DIV1; ENABLE enabled; RUNSTDBY disabled; SYNCUPD disabled; 
    TCB2.CTRLA = 0x1;

}

void TCB2_Start(void)
{
    TCB2.CTRLA |= TCB_ENABLE_bm; /* Start Timer */
}

void TCB2_Stop(void)
{
    TCB2.CTRLA &= ~TCB_ENABLE_bm; /* Stop Timer */
}

void TCB2_Write(uint16_t timerVal)
{
    TCB2.CNT = timerVal;
}

uint16_t TCB2_Read(void)
{
    uint16_t readVal;

    readVal = TCB2.CNT;

    return readVal;
}

void TCB2_EnableCaptInterrupt(void)
{
    TCB2.INTCTRL |= TCB_CAPT_bm; /* Capture or Timeout: enabled */
}

void TCB2_EnableOvfInterrupt(void)
{
	TCB2.INTCTRL |= TCB_OVF_bm; /* Overflow Interrupt: enabled */
}

void TCB2_DisableCaptInterrupt(void)
{
    TCB2.INTCTRL &= ~TCB_CAPT_bm; /* Capture or Timeout: disabled */
}

void TCB2_DisableOvfInterrupt(void)
{
	TCB2.INTCTRL &= ~TCB_OVF_bm; /* Overflow Interrupt: disabled */

}

inline void TCB2_ClearCaptInterruptFlag(void)
{
    TCB2.INTFLAGS &= ~TCB_CAPT_bm;
}

inline void TCB2_ClearOvfInterruptFlag(void)
{
	TCB2.INTFLAGS &= ~TCB_OVF_bm;

}

inline bool TCB2_IsCaptInterruptEnabled(void)
{
    return ((TCB2.INTCTRL & TCB_CAPT_bm) > 0);
}

inline bool TCB2_IsOvfInterruptEnabled(void)
{
        return ((TCB2.INTCTRL & TCB_OVF_bm) > 0);
}

