/**
 * TCD0 Generated Driver API Header File
 *
 * @file tcd0.h
 *
 * @defgroup tcd0 TCD0
 *
 * @brief This file contains the API prototypes for the TCD0 driver.
 *
 * @version TCD0 Driver Version 2.0.3
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


#ifndef TCD0_H_INCLUDED
#define TCD0_H_INCLUDED

#include "../system/utils/compiler.h"
#include "../system/ccp.h"
#include "./timer_interface.h"

extern const struct TMR_INTERFACE TCD0_Interface;

/**
 * @ingroup tcd0
 * @typedef void *TCD0_cb_t
 * @brief Function pointer to callback function called by the TCD. The default value is set to NULL which means that no callback function will be used.
 */ 
typedef void (*TCD0_cb_t)(void);
/**
 * @ingroup tcd0
 * @brief Initializes the TCD interface.
 * @param None.
 * @return None.
 */ 
void TCD0_Initialize();
/**
 * @ingroup tcd0
 * @brief Starts the 12-bit timer/counter for TCD interface.
 * @param none
 * @return none
 */
void TCD0_Start();
/**
 * @ingroup tcd0
 * @brief Stops the 12-bit timer/counter for TCD interface
 * @param none
 * @return none
 */
void TCD0_Stop();
/**
 * @ingroup tcd0
 * @brief Interrupt Service Routine (ISR) callback function to be called if the Trigger Input Interrupt flag is set.
 * @param TCD0_cb_t cb - Callback function for the trigger input event.
 * @return None.
 */ 
void TCD0_SetTRIGIsrCallback(TCD0_cb_t cb);
/**
 * @ingroup tcd0
 * @brief ISR callback function to be called if the Counter Overflow flag is set.
 * @param TCD0_cb_t cb - Callback function for the counter overflow event.
 * @return None.
 */ 
void TCD0_SetOVFIsrCallback(TCD0_cb_t cb);


#endif /* TCD0_H_INCLUDED */
