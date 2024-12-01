/**
 * USART1 Generated Driver API Header File
 * 
 * @file usart1.h
 * 
 * @defgroup usart1 USART1
 * 
 * @brief This file contains API prototypes and other datatypes for USART1 module.
 *
 * @version USART1 Driver Version 2.0.3
*/
/*
© [2024] Microchip Technology Inc. and its subsidiaries.

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

#ifndef USART1_H
#define USART1_H

/**
  Section: Included Files
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "../system/system.h"
#include "uart_drv_interface.h"

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/* Normal Mode, Baud register value */
#define USART1_BAUD_RATE(BAUD_RATE) (((float)16000000 * 64 / (16 * (float)BAUD_RATE)) + 0.5)

#define RS485_MODBUS_interface RS485_MODBUS


#define RS485_MODBUS_Initialize     USART1_Initialize
#define RS485_MODBUS_Deinitialize   USART1_Deinitialize
#define RS485_MODBUS_Write          USART1_Write
#define RS485_MODBUS_Read           USART1_Read
#define RS485_MODBUS__IsRxReady     USART1_IsRxReady
#define RS485_MODBUS_IsTxReady      USART1_IsTxReady
#define RS485_MODBUS_IsTxDone       USART1_IsTxDone

#define RS485_MODBUS_TransmitEnable       USART1_TransmitEnable
#define RS485_MODBUS_TransmitDisable      USART1_TransmitDisable
#define RS485_MODBUS_AutoBaudSet          USART1_AutoBaudSet
#define RS485_MODBUS_AutoBaudQuery        USART1_AutoBaudQuery
#define RS485_MODBUS_BRGCountSet               (NULL)
#define RS485_MODBUS_BRGCountGet               (NULL)
#define RS485_MODBUS_BaudRateSet               (NULL)
#define RS485_MODBUS_BaudRateGet               (NULL)
#define RS485_MODBUS__AutoBaudEventEnableGet   (NULL)
#define RS485_MODBUS_ErrorGet             USART1_ErrorGet

#define RS485_MODBUS_TxCompleteCallbackRegister     (NULL)
#define RS485_MODBUS_RxCompleteCallbackRegister      (NULL)
#define RS485_MODBUS_TxCollisionCallbackRegister  (NULL)
#define RS485_MODBUS_FramingErrorCallbackRegister USART1_FramingErrorCallbackRegister
#define RS485_MODBUS_OverrunErrorCallbackRegister USART1_OverrunErrorCallbackRegister
#define RS485_MODBUS_ParityErrorCallbackRegister  USART1_ParityErrorCallbackRegister
#define RS485_MODBUS_EventCallbackRegister        (NULL)


/**
 @ingroup usart1
 @struct usart1_status_t
 @breif This is an instance of USART1_STATUS for USART1 module
 */
typedef union {
    struct {
        uint8_t perr : 1;     /**<This is a bit field for Parity Error status*/
        uint8_t ferr : 1;     /**<This is a bit field for Framing Error status*/
        uint8_t oerr : 1;     /**<This is a bit field for Overfrun Error status*/
        uint8_t reserved : 5; /**<Reserved*/
    };
    size_t status;            /**<Group byte for status errors*/
}usart1_status_t;



/**
 Section: Data Type Definitions
 */

/**
 * @ingroup usart1
 * @brief External object for usart1_interface.
 */
extern const uart_drv_interface_t RS485_MODBUS;

/**
 * @ingroup usart1
 * @brief This API initializes the USART1 driver.
 *        This routine initializes the USART1 module.
 *        This routine must be called before any other USART1 routine is called.
 *        This routine should only be called once during system initialization.
 * @param None.
 * @return None.
 */
void USART1_Initialize(void);

/**
 * @ingroup usart1
 * @brief This API Deinitializes the USART1 driver.
 *        This routine disables the USART1 module.
 * @param None.
 * @return None.
 */
void USART1_Deinitialize(void);

/**
 * @ingroup usart1
 * @brief This API enables the USART1 module.     
 * @param None.
 * @return None.
 */
void USART1_Enable(void);

/**
 * @ingroup usart1
 * @brief This API disables the USART1 module.
 * @param None.
 * @return None.
 */
void USART1_Disable(void);

/**
 * @ingroup usart1
 * @brief This API enables the USART1 transmitter.
 *        USART1 should also be enable to send bytes over TX pin.
 * @param None.
 * @return None.
 */
void USART1_TransmitEnable(void);

/**
 * @ingroup usart1
 * @brief This API disables the USART1 transmitter.
 * @param None.
 * @return None.
 */
void USART1_TransmitDisable(void);

/**
 * @ingroup usart1
 * @brief This API enables the USART1 Receiver.
 *        USART1 should also be enable to receive bytes over RX pin.
 * @param None.
 * @return None.
 */
void USART1_ReceiveEnable(void);

/**
 * @ingroup usart1
 * @brief This API disables the USART1 Receiver.
 * @param None.
 * @return None.
 */
void USART1_ReceiveDisable(void);



/**
 * @ingroup usart1
 * @brief This API enables the USART1 AutoBaud Detection.
 * @param bool enable.
 * @return None.
 */
void USART1_AutoBaudSet(bool enable);

/**
 * @ingroup usart1
 * @brief This API reads the USART1 AutoBaud Detection Complete bit.
 * @param None.
 * @return None.
 */
bool USART1_AutoBaudQuery(void);

/**
 * @ingroup usart1
 * @brief This API reads the USART1 AutoBaud Detection error bit.
 * @param None.
 * @return None.
 */
bool USART1_IsAutoBaudDetectError(void);

/**
 * @ingroup usart1
 * @brief This API Reset the USART1 AutoBaud Detection error bit.
 * @param None.
 * @return None.
 */
void USART1_AutoBaudDetectErrorReset(void);

/**
 * @ingroup usart1
 * @brief This API checks if USART1 receiver has received data and ready to be read.
 * @param None.
 * @retval true if USART1 receiver FIFO has a data
 * @retval false USART1 receiver FIFO is empty
 */
bool USART1_IsRxReady(void);

/**
 * @ingroup usart1
 * @brief This function checks if USART1 transmitter is ready to accept a data byte.
 * @param None.
 * @retval true if USART1 transmitter FIFO has atleast 1 byte space
 * @retval false if USART1 transmitter FIFO is full
 */
bool USART1_IsTxReady(void);

/**
 * @ingroup usart1
 * @brief This function return the status of transmit shift register (TSR).
 * @param None.
 * @retval true if Data completely shifted out from the TSR
 * @retval false if Data is present in Transmit FIFO and/or in TSR
 */
bool USART1_IsTxDone(void);

/**
 * @ingroup usart1
 * @brief This function gets the error status of the last read byte.
 *        This function should be called before USART1_Read().
 * @param None.
 * @return Status of the last read byte. See usart1_status_t struct for more details.
 */
size_t USART1_ErrorGet(void);

/**
 * @ingroup usart1
 * @brief This function reads the 8 bits from receiver FIFO register.
 * @pre The transfer status should be checked to see if the receiver is not empty
 *      before calling this function. USART1_IsRxReady() should be checked in if () before calling this API.
 * @param None.
 * @return 8-bit data from RX FIFO register.
 */
uint8_t USART1_Read(void);

/**
 * @ingroup usart1
 * @brief This function writes a byte of data to the transmitter FIFO register.
 * @pre The transfer status should be checked to see if the transmitter is ready to accept a byte
 *      before calling this function. USART1_IsTxReady() should be checked in if() before calling this API.
 * @param txData  - Data byte to write to the TX FIFO.
 * @return None.
 */
void USART1_Write(uint8_t txData);

/**
 * @ingroup usart1
 * @brief This API registers the function to be called upon USART1 framing error.
 * @param callbackHandler - a function pointer which will be called upon framing error condition.
 * @return None.
 */
void USART1_FramingErrorCallbackRegister(void (* callbackHandler)(void));

/**
 * @ingroup usart1
 * @brief This API registers the function to be called upon USART1 overrun error.
 * @param callbackHandler - a function pointer which will be called upon overrun error condition.
 * @return None.
 */
void USART1_OverrunErrorCallbackRegister(void (* callbackHandler)(void));

/**
 * @ingroup usart1
 * @brief This API registers the function to be called upon USART1 Parity error.
 * @param callbackHandler - a function pointer which will be called upon Parity error condition.
 * @return None.
 */
void USART1_ParityErrorCallbackRegister(void (* callbackHandler)(void));


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  // USART1_H
