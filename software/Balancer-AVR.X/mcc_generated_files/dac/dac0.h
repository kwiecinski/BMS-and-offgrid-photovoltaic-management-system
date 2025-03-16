/**
 * DAC0 Generated Driver API Header File
 * 
 * @file dac0.h
 * 
 * @defgroup  dac0 DAC0
 * 
 * @brief Contains the API prototypes and other data types for the DAC0 driver.
 *
 * @version DAC0 Driver Version 1.0.0
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


#ifndef DAC0_H_INCLUDED
#define DAC0_H_INCLUDED

#include "../system/utils/compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Data type for the resolution of the DAC */
typedef uint16_t dac_resolution_t;

/**
 * @ingroup dac0
 * @brief  Initializes the DAC0 and must be called only once, before any other DAC0 routine is called.
 * If the enable bit is set to 0, writing to the Data register will not trigger a conversion until the enable bit is set to 1.
 * @param None.
 * @return Initialization status.
 * @retval 1 - The DAC initialization was successful.
 * @retval 0 - The DAC initialization was not successful.
 */
int8_t DAC0_Initialize(void);

/**
 * @ingroup dac0
 * @brief  Enables the DAC0 module.
 * @param None.
 * @return None.
 */
void DAC0_Enable(void);

/**
 * @ingroup dac0
 * @brief  Disables the DAC0 module.
 * @param None.
 * @return None.
 */
void DAC0_Disable(void);

/**
 * @ingroup dac0
 * @brief  Starts a digital-to-analog conversion.
 * @param value - The digital value to be converted to analog voltage by the DAC.
 * @return None.
 */
 void DAC0_SetOutput(dac_resolution_t value);

/**
 * @ingroup dac0
 * @brief  Returns the DAC0 resolution in number of bits.
 * @param None.
 * @return Resolution of the DAC.
 */
uint8_t DAC0_GetResolution(void);

#ifdef __cplusplus
}
#endif

#endif /* DAC0_H_INCLUDED */