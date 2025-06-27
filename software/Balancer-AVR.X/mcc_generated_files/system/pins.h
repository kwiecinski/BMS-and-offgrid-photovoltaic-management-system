/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  1.0.1
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

#ifndef PINS_H_INCLUDED
#define PINS_H_INCLUDED

#include <avr/io.h>
#include "./port.h"

//get/set I2C_CLOCK aliases
#define I2C_CLOCK_SetHigh() do { PORTC_OUTSET = 0x8; } while(0)
#define I2C_CLOCK_SetLow() do { PORTC_OUTCLR = 0x8; } while(0)
#define I2C_CLOCK_Toggle() do { PORTC_OUTTGL = 0x8; } while(0)
#define I2C_CLOCK_GetValue() (VPORTC.IN & (0x1 << 3))
#define I2C_CLOCK_SetDigitalInput() do { PORTC_DIRCLR = 0x8; } while(0)
#define I2C_CLOCK_SetDigitalOutput() do { PORTC_DIRSET = 0x8; } while(0)
#define I2C_CLOCK_SetPullUp() do { PORTC_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define I2C_CLOCK_ResetPullUp() do { PORTC_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define I2C_CLOCK_SetInverted() do { PORTC_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define I2C_CLOCK_ResetInverted() do { PORTC_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define I2C_CLOCK_DisableInterruptOnChange() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define I2C_CLOCK_EnableInterruptForBothEdges() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define I2C_CLOCK_EnableInterruptForRisingEdge() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define I2C_CLOCK_EnableInterruptForFallingEdge() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define I2C_CLOCK_DisableDigitalInputBuffer() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define I2C_CLOCK_EnableInterruptForLowLevelSensing() do { PORTC.PIN3CTRL = (PORTC.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set I2C_DATA aliases
#define I2C_DATA_SetHigh() do { PORTC_OUTSET = 0x4; } while(0)
#define I2C_DATA_SetLow() do { PORTC_OUTCLR = 0x4; } while(0)
#define I2C_DATA_Toggle() do { PORTC_OUTTGL = 0x4; } while(0)
#define I2C_DATA_GetValue() (VPORTC.IN & (0x1 << 2))
#define I2C_DATA_SetDigitalInput() do { PORTC_DIRCLR = 0x4; } while(0)
#define I2C_DATA_SetDigitalOutput() do { PORTC_DIRSET = 0x4; } while(0)
#define I2C_DATA_SetPullUp() do { PORTC_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define I2C_DATA_ResetPullUp() do { PORTC_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define I2C_DATA_SetInverted() do { PORTC_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define I2C_DATA_ResetInverted() do { PORTC_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define I2C_DATA_DisableInterruptOnChange() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define I2C_DATA_EnableInterruptForBothEdges() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define I2C_DATA_EnableInterruptForRisingEdge() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define I2C_DATA_EnableInterruptForFallingEdge() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define I2C_DATA_DisableDigitalInputBuffer() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define I2C_DATA_EnableInterruptForLowLevelSensing() do { PORTC.PIN2CTRL = (PORTC.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PWM_CHARGE aliases
#define PWM_CHARGE_SetHigh() do { PORTF_OUTSET = 0x1; } while(0)
#define PWM_CHARGE_SetLow() do { PORTF_OUTCLR = 0x1; } while(0)
#define PWM_CHARGE_Toggle() do { PORTF_OUTTGL = 0x1; } while(0)
#define PWM_CHARGE_GetValue() (VPORTF.IN & (0x1 << 0))
#define PWM_CHARGE_SetDigitalInput() do { PORTF_DIRCLR = 0x1; } while(0)
#define PWM_CHARGE_SetDigitalOutput() do { PORTF_DIRSET = 0x1; } while(0)
#define PWM_CHARGE_SetPullUp() do { PORTF_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PWM_CHARGE_ResetPullUp() do { PORTF_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PWM_CHARGE_SetInverted() do { PORTF_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define PWM_CHARGE_ResetInverted() do { PORTF_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PWM_CHARGE_DisableInterruptOnChange() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PWM_CHARGE_EnableInterruptForBothEdges() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PWM_CHARGE_EnableInterruptForRisingEdge() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PWM_CHARGE_EnableInterruptForFallingEdge() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PWM_CHARGE_DisableDigitalInputBuffer() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PWM_CHARGE_EnableInterruptForLowLevelSensing() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PWM_DISCHARGE aliases
#define PWM_DISCHARGE_SetHigh() do { PORTF_OUTSET = 0x2; } while(0)
#define PWM_DISCHARGE_SetLow() do { PORTF_OUTCLR = 0x2; } while(0)
#define PWM_DISCHARGE_Toggle() do { PORTF_OUTTGL = 0x2; } while(0)
#define PWM_DISCHARGE_GetValue() (VPORTF.IN & (0x1 << 1))
#define PWM_DISCHARGE_SetDigitalInput() do { PORTF_DIRCLR = 0x2; } while(0)
#define PWM_DISCHARGE_SetDigitalOutput() do { PORTF_DIRSET = 0x2; } while(0)
#define PWM_DISCHARGE_SetPullUp() do { PORTF_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PWM_DISCHARGE_ResetPullUp() do { PORTF_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PWM_DISCHARGE_SetInverted() do { PORTF_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define PWM_DISCHARGE_ResetInverted() do { PORTF_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PWM_DISCHARGE_DisableInterruptOnChange() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PWM_DISCHARGE_EnableInterruptForBothEdges() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PWM_DISCHARGE_EnableInterruptForRisingEdge() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PWM_DISCHARGE_EnableInterruptForFallingEdge() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PWM_DISCHARGE_DisableDigitalInputBuffer() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PWM_DISCHARGE_EnableInterruptForLowLevelSensing() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PWM_BALANCE_24V aliases
#define PWM_BALANCE_24V_SetHigh() do { PORTA_OUTSET = 0x10; } while(0)
#define PWM_BALANCE_24V_SetLow() do { PORTA_OUTCLR = 0x10; } while(0)
#define PWM_BALANCE_24V_Toggle() do { PORTA_OUTTGL = 0x10; } while(0)
#define PWM_BALANCE_24V_GetValue() (VPORTA.IN & (0x1 << 4))
#define PWM_BALANCE_24V_SetDigitalInput() do { PORTA_DIRCLR = 0x10; } while(0)
#define PWM_BALANCE_24V_SetDigitalOutput() do { PORTA_DIRSET = 0x10; } while(0)
#define PWM_BALANCE_24V_SetPullUp() do { PORTA_PIN4CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PWM_BALANCE_24V_ResetPullUp() do { PORTA_PIN4CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PWM_BALANCE_24V_SetInverted() do { PORTA_PIN4CTRL  |= PORT_INVEN_bm; } while(0)
#define PWM_BALANCE_24V_ResetInverted() do { PORTA_PIN4CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PWM_BALANCE_24V_DisableInterruptOnChange() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PWM_BALANCE_24V_EnableInterruptForBothEdges() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PWM_BALANCE_24V_EnableInterruptForRisingEdge() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PWM_BALANCE_24V_EnableInterruptForFallingEdge() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PWM_BALANCE_24V_DisableDigitalInputBuffer() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PWM_BALANCE_24V_EnableInterruptForLowLevelSensing() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PWM_BALANCE_12V aliases
#define PWM_BALANCE_12V_SetHigh() do { PORTA_OUTSET = 0x20; } while(0)
#define PWM_BALANCE_12V_SetLow() do { PORTA_OUTCLR = 0x20; } while(0)
#define PWM_BALANCE_12V_Toggle() do { PORTA_OUTTGL = 0x20; } while(0)
#define PWM_BALANCE_12V_GetValue() (VPORTA.IN & (0x1 << 5))
#define PWM_BALANCE_12V_SetDigitalInput() do { PORTA_DIRCLR = 0x20; } while(0)
#define PWM_BALANCE_12V_SetDigitalOutput() do { PORTA_DIRSET = 0x20; } while(0)
#define PWM_BALANCE_12V_SetPullUp() do { PORTA_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PWM_BALANCE_12V_ResetPullUp() do { PORTA_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PWM_BALANCE_12V_SetInverted() do { PORTA_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define PWM_BALANCE_12V_ResetInverted() do { PORTA_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PWM_BALANCE_12V_DisableInterruptOnChange() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PWM_BALANCE_12V_EnableInterruptForBothEdges() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PWM_BALANCE_12V_EnableInterruptForRisingEdge() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PWM_BALANCE_12V_EnableInterruptForFallingEdge() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PWM_BALANCE_12V_DisableDigitalInputBuffer() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PWM_BALANCE_12V_EnableInterruptForLowLevelSensing() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set TEMP_SMPS aliases
#define TEMP_SMPS_SetHigh() do { PORTD_OUTSET = 0x10; } while(0)
#define TEMP_SMPS_SetLow() do { PORTD_OUTCLR = 0x10; } while(0)
#define TEMP_SMPS_Toggle() do { PORTD_OUTTGL = 0x10; } while(0)
#define TEMP_SMPS_GetValue() (VPORTD.IN & (0x1 << 4))
#define TEMP_SMPS_SetDigitalInput() do { PORTD_DIRCLR = 0x10; } while(0)
#define TEMP_SMPS_SetDigitalOutput() do { PORTD_DIRSET = 0x10; } while(0)
#define TEMP_SMPS_SetPullUp() do { PORTD_PIN4CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define TEMP_SMPS_ResetPullUp() do { PORTD_PIN4CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define TEMP_SMPS_SetInverted() do { PORTD_PIN4CTRL  |= PORT_INVEN_bm; } while(0)
#define TEMP_SMPS_ResetInverted() do { PORTD_PIN4CTRL  &= ~PORT_INVEN_bm; } while(0)
#define TEMP_SMPS_DisableInterruptOnChange() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define TEMP_SMPS_EnableInterruptForBothEdges() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define TEMP_SMPS_EnableInterruptForRisingEdge() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define TEMP_SMPS_EnableInterruptForFallingEdge() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define TEMP_SMPS_DisableDigitalInputBuffer() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define TEMP_SMPS_EnableInterruptForLowLevelSensing() do { PORTD.PIN4CTRL = (PORTD.PIN4CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set TEMP_BALANCER aliases
#define TEMP_BALANCER_SetHigh() do { PORTD_OUTSET = 0x20; } while(0)
#define TEMP_BALANCER_SetLow() do { PORTD_OUTCLR = 0x20; } while(0)
#define TEMP_BALANCER_Toggle() do { PORTD_OUTTGL = 0x20; } while(0)
#define TEMP_BALANCER_GetValue() (VPORTD.IN & (0x1 << 5))
#define TEMP_BALANCER_SetDigitalInput() do { PORTD_DIRCLR = 0x20; } while(0)
#define TEMP_BALANCER_SetDigitalOutput() do { PORTD_DIRSET = 0x20; } while(0)
#define TEMP_BALANCER_SetPullUp() do { PORTD_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define TEMP_BALANCER_ResetPullUp() do { PORTD_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define TEMP_BALANCER_SetInverted() do { PORTD_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define TEMP_BALANCER_ResetInverted() do { PORTD_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define TEMP_BALANCER_DisableInterruptOnChange() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define TEMP_BALANCER_EnableInterruptForBothEdges() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define TEMP_BALANCER_EnableInterruptForRisingEdge() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define TEMP_BALANCER_EnableInterruptForFallingEdge() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define TEMP_BALANCER_DisableDigitalInputBuffer() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define TEMP_BALANCER_EnableInterruptForLowLevelSensing() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set GND_VOLT_DROP aliases
#define GND_VOLT_DROP_SetHigh() do { PORTA_OUTSET = 0x40; } while(0)
#define GND_VOLT_DROP_SetLow() do { PORTA_OUTCLR = 0x40; } while(0)
#define GND_VOLT_DROP_Toggle() do { PORTA_OUTTGL = 0x40; } while(0)
#define GND_VOLT_DROP_GetValue() (VPORTA.IN & (0x1 << 6))
#define GND_VOLT_DROP_SetDigitalInput() do { PORTA_DIRCLR = 0x40; } while(0)
#define GND_VOLT_DROP_SetDigitalOutput() do { PORTA_DIRSET = 0x40; } while(0)
#define GND_VOLT_DROP_SetPullUp() do { PORTA_PIN6CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define GND_VOLT_DROP_ResetPullUp() do { PORTA_PIN6CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define GND_VOLT_DROP_SetInverted() do { PORTA_PIN6CTRL  |= PORT_INVEN_bm; } while(0)
#define GND_VOLT_DROP_ResetInverted() do { PORTA_PIN6CTRL  &= ~PORT_INVEN_bm; } while(0)
#define GND_VOLT_DROP_DisableInterruptOnChange() do { PORTA.PIN6CTRL = (PORTA.PIN6CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define GND_VOLT_DROP_EnableInterruptForBothEdges() do { PORTA.PIN6CTRL = (PORTA.PIN6CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define GND_VOLT_DROP_EnableInterruptForRisingEdge() do { PORTA.PIN6CTRL = (PORTA.PIN6CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define GND_VOLT_DROP_EnableInterruptForFallingEdge() do { PORTA.PIN6CTRL = (PORTA.PIN6CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define GND_VOLT_DROP_DisableDigitalInputBuffer() do { PORTA.PIN6CTRL = (PORTA.PIN6CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define GND_VOLT_DROP_EnableInterruptForLowLevelSensing() do { PORTA.PIN6CTRL = (PORTA.PIN6CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set ADC_I_FAN1 aliases
#define ADC_I_FAN1_SetHigh() do { PORTA_OUTSET = 0x80; } while(0)
#define ADC_I_FAN1_SetLow() do { PORTA_OUTCLR = 0x80; } while(0)
#define ADC_I_FAN1_Toggle() do { PORTA_OUTTGL = 0x80; } while(0)
#define ADC_I_FAN1_GetValue() (VPORTA.IN & (0x1 << 7))
#define ADC_I_FAN1_SetDigitalInput() do { PORTA_DIRCLR = 0x80; } while(0)
#define ADC_I_FAN1_SetDigitalOutput() do { PORTA_DIRSET = 0x80; } while(0)
#define ADC_I_FAN1_SetPullUp() do { PORTA_PIN7CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define ADC_I_FAN1_ResetPullUp() do { PORTA_PIN7CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define ADC_I_FAN1_SetInverted() do { PORTA_PIN7CTRL  |= PORT_INVEN_bm; } while(0)
#define ADC_I_FAN1_ResetInverted() do { PORTA_PIN7CTRL  &= ~PORT_INVEN_bm; } while(0)
#define ADC_I_FAN1_DisableInterruptOnChange() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define ADC_I_FAN1_EnableInterruptForBothEdges() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define ADC_I_FAN1_EnableInterruptForRisingEdge() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define ADC_I_FAN1_EnableInterruptForFallingEdge() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define ADC_I_FAN1_DisableDigitalInputBuffer() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define ADC_I_FAN1_EnableInterruptForLowLevelSensing() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set ADC_I_FAN2 aliases
#define ADC_I_FAN2_SetHigh() do { PORTC_OUTSET = 0x2; } while(0)
#define ADC_I_FAN2_SetLow() do { PORTC_OUTCLR = 0x2; } while(0)
#define ADC_I_FAN2_Toggle() do { PORTC_OUTTGL = 0x2; } while(0)
#define ADC_I_FAN2_GetValue() (VPORTC.IN & (0x1 << 1))
#define ADC_I_FAN2_SetDigitalInput() do { PORTC_DIRCLR = 0x2; } while(0)
#define ADC_I_FAN2_SetDigitalOutput() do { PORTC_DIRSET = 0x2; } while(0)
#define ADC_I_FAN2_SetPullUp() do { PORTC_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define ADC_I_FAN2_ResetPullUp() do { PORTC_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define ADC_I_FAN2_SetInverted() do { PORTC_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define ADC_I_FAN2_ResetInverted() do { PORTC_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define ADC_I_FAN2_DisableInterruptOnChange() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define ADC_I_FAN2_EnableInterruptForBothEdges() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define ADC_I_FAN2_EnableInterruptForRisingEdge() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define ADC_I_FAN2_EnableInterruptForFallingEdge() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define ADC_I_FAN2_DisableDigitalInputBuffer() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define ADC_I_FAN2_EnableInterruptForLowLevelSensing() do { PORTC.PIN1CTRL = (PORTC.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set VOLTAGE_BATT_12V aliases
#define VOLTAGE_BATT_12V_SetHigh() do { PORTD_OUTSET = 0x2; } while(0)
#define VOLTAGE_BATT_12V_SetLow() do { PORTD_OUTCLR = 0x2; } while(0)
#define VOLTAGE_BATT_12V_Toggle() do { PORTD_OUTTGL = 0x2; } while(0)
#define VOLTAGE_BATT_12V_GetValue() (VPORTD.IN & (0x1 << 1))
#define VOLTAGE_BATT_12V_SetDigitalInput() do { PORTD_DIRCLR = 0x2; } while(0)
#define VOLTAGE_BATT_12V_SetDigitalOutput() do { PORTD_DIRSET = 0x2; } while(0)
#define VOLTAGE_BATT_12V_SetPullUp() do { PORTD_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define VOLTAGE_BATT_12V_ResetPullUp() do { PORTD_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define VOLTAGE_BATT_12V_SetInverted() do { PORTD_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define VOLTAGE_BATT_12V_ResetInverted() do { PORTD_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define VOLTAGE_BATT_12V_DisableInterruptOnChange() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define VOLTAGE_BATT_12V_EnableInterruptForBothEdges() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define VOLTAGE_BATT_12V_EnableInterruptForRisingEdge() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define VOLTAGE_BATT_12V_EnableInterruptForFallingEdge() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define VOLTAGE_BATT_12V_DisableDigitalInputBuffer() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define VOLTAGE_BATT_12V_EnableInterruptForLowLevelSensing() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set TEMP_BATT_12V aliases
#define TEMP_BATT_12V_SetHigh() do { PORTD_OUTSET = 0x4; } while(0)
#define TEMP_BATT_12V_SetLow() do { PORTD_OUTCLR = 0x4; } while(0)
#define TEMP_BATT_12V_Toggle() do { PORTD_OUTTGL = 0x4; } while(0)
#define TEMP_BATT_12V_GetValue() (VPORTD.IN & (0x1 << 2))
#define TEMP_BATT_12V_SetDigitalInput() do { PORTD_DIRCLR = 0x4; } while(0)
#define TEMP_BATT_12V_SetDigitalOutput() do { PORTD_DIRSET = 0x4; } while(0)
#define TEMP_BATT_12V_SetPullUp() do { PORTD_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define TEMP_BATT_12V_ResetPullUp() do { PORTD_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define TEMP_BATT_12V_SetInverted() do { PORTD_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define TEMP_BATT_12V_ResetInverted() do { PORTD_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define TEMP_BATT_12V_DisableInterruptOnChange() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define TEMP_BATT_12V_EnableInterruptForBothEdges() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define TEMP_BATT_12V_EnableInterruptForRisingEdge() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define TEMP_BATT_12V_EnableInterruptForFallingEdge() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define TEMP_BATT_12V_DisableDigitalInputBuffer() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define TEMP_BATT_12V_EnableInterruptForLowLevelSensing() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set TEMP_BATT_24V aliases
#define TEMP_BATT_24V_SetHigh() do { PORTD_OUTSET = 0x8; } while(0)
#define TEMP_BATT_24V_SetLow() do { PORTD_OUTCLR = 0x8; } while(0)
#define TEMP_BATT_24V_Toggle() do { PORTD_OUTTGL = 0x8; } while(0)
#define TEMP_BATT_24V_GetValue() (VPORTD.IN & (0x1 << 3))
#define TEMP_BATT_24V_SetDigitalInput() do { PORTD_DIRCLR = 0x8; } while(0)
#define TEMP_BATT_24V_SetDigitalOutput() do { PORTD_DIRSET = 0x8; } while(0)
#define TEMP_BATT_24V_SetPullUp() do { PORTD_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define TEMP_BATT_24V_ResetPullUp() do { PORTD_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define TEMP_BATT_24V_SetInverted() do { PORTD_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define TEMP_BATT_24V_ResetInverted() do { PORTD_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define TEMP_BATT_24V_DisableInterruptOnChange() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define TEMP_BATT_24V_EnableInterruptForBothEdges() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define TEMP_BATT_24V_EnableInterruptForRisingEdge() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define TEMP_BATT_24V_EnableInterruptForFallingEdge() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define TEMP_BATT_24V_DisableDigitalInputBuffer() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define TEMP_BATT_24V_EnableInterruptForLowLevelSensing() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PWM_FAN_SMPS aliases
#define PWM_FAN_SMPS_SetHigh() do { PORTA_OUTSET = 0x8; } while(0)
#define PWM_FAN_SMPS_SetLow() do { PORTA_OUTCLR = 0x8; } while(0)
#define PWM_FAN_SMPS_Toggle() do { PORTA_OUTTGL = 0x8; } while(0)
#define PWM_FAN_SMPS_GetValue() (VPORTA.IN & (0x1 << 3))
#define PWM_FAN_SMPS_SetDigitalInput() do { PORTA_DIRCLR = 0x8; } while(0)
#define PWM_FAN_SMPS_SetDigitalOutput() do { PORTA_DIRSET = 0x8; } while(0)
#define PWM_FAN_SMPS_SetPullUp() do { PORTA_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PWM_FAN_SMPS_ResetPullUp() do { PORTA_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PWM_FAN_SMPS_SetInverted() do { PORTA_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define PWM_FAN_SMPS_ResetInverted() do { PORTA_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PWM_FAN_SMPS_DisableInterruptOnChange() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PWM_FAN_SMPS_EnableInterruptForBothEdges() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PWM_FAN_SMPS_EnableInterruptForRisingEdge() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PWM_FAN_SMPS_EnableInterruptForFallingEdge() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PWM_FAN_SMPS_DisableDigitalInputBuffer() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PWM_FAN_SMPS_EnableInterruptForLowLevelSensing() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PWM_FAN_BALANCER aliases
#define PWM_FAN_BALANCER_SetHigh() do { PORTA_OUTSET = 0x4; } while(0)
#define PWM_FAN_BALANCER_SetLow() do { PORTA_OUTCLR = 0x4; } while(0)
#define PWM_FAN_BALANCER_Toggle() do { PORTA_OUTTGL = 0x4; } while(0)
#define PWM_FAN_BALANCER_GetValue() (VPORTA.IN & (0x1 << 2))
#define PWM_FAN_BALANCER_SetDigitalInput() do { PORTA_DIRCLR = 0x4; } while(0)
#define PWM_FAN_BALANCER_SetDigitalOutput() do { PORTA_DIRSET = 0x4; } while(0)
#define PWM_FAN_BALANCER_SetPullUp() do { PORTA_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PWM_FAN_BALANCER_ResetPullUp() do { PORTA_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PWM_FAN_BALANCER_SetInverted() do { PORTA_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define PWM_FAN_BALANCER_ResetInverted() do { PORTA_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PWM_FAN_BALANCER_DisableInterruptOnChange() do { PORTA.PIN2CTRL = (PORTA.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PWM_FAN_BALANCER_EnableInterruptForBothEdges() do { PORTA.PIN2CTRL = (PORTA.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PWM_FAN_BALANCER_EnableInterruptForRisingEdge() do { PORTA.PIN2CTRL = (PORTA.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PWM_FAN_BALANCER_EnableInterruptForFallingEdge() do { PORTA.PIN2CTRL = (PORTA.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PWM_FAN_BALANCER_DisableDigitalInputBuffer() do { PORTA.PIN2CTRL = (PORTA.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PWM_FAN_BALANCER_EnableInterruptForLowLevelSensing() do { PORTA.PIN2CTRL = (PORTA.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set DEBUG_UART aliases
#define DEBUG_UART_SetHigh() do { PORTC_OUTSET = 0x1; } while(0)
#define DEBUG_UART_SetLow() do { PORTC_OUTCLR = 0x1; } while(0)
#define DEBUG_UART_Toggle() do { PORTC_OUTTGL = 0x1; } while(0)
#define DEBUG_UART_GetValue() (VPORTC.IN & (0x1 << 0))
#define DEBUG_UART_SetDigitalInput() do { PORTC_DIRCLR = 0x1; } while(0)
#define DEBUG_UART_SetDigitalOutput() do { PORTC_DIRSET = 0x1; } while(0)
#define DEBUG_UART_SetPullUp() do { PORTC_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define DEBUG_UART_ResetPullUp() do { PORTC_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define DEBUG_UART_SetInverted() do { PORTC_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define DEBUG_UART_ResetInverted() do { PORTC_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define DEBUG_UART_DisableInterruptOnChange() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define DEBUG_UART_EnableInterruptForBothEdges() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define DEBUG_UART_EnableInterruptForRisingEdge() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define DEBUG_UART_EnableInterruptForFallingEdge() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define DEBUG_UART_DisableDigitalInputBuffer() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define DEBUG_UART_EnableInterruptForLowLevelSensing() do { PORTC.PIN0CTRL = (PORTC.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set RS485_RX aliases
#define RS485_RX_SetHigh() do { PORTA_OUTSET = 0x2; } while(0)
#define RS485_RX_SetLow() do { PORTA_OUTCLR = 0x2; } while(0)
#define RS485_RX_Toggle() do { PORTA_OUTTGL = 0x2; } while(0)
#define RS485_RX_GetValue() (VPORTA.IN & (0x1 << 1))
#define RS485_RX_SetDigitalInput() do { PORTA_DIRCLR = 0x2; } while(0)
#define RS485_RX_SetDigitalOutput() do { PORTA_DIRSET = 0x2; } while(0)
#define RS485_RX_SetPullUp() do { PORTA_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define RS485_RX_ResetPullUp() do { PORTA_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define RS485_RX_SetInverted() do { PORTA_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define RS485_RX_ResetInverted() do { PORTA_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define RS485_RX_DisableInterruptOnChange() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define RS485_RX_EnableInterruptForBothEdges() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define RS485_RX_EnableInterruptForRisingEdge() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define RS485_RX_EnableInterruptForFallingEdge() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define RS485_RX_DisableDigitalInputBuffer() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define RS485_RX_EnableInterruptForLowLevelSensing() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set RS485_TX aliases
#define RS485_TX_SetHigh() do { PORTA_OUTSET = 0x1; } while(0)
#define RS485_TX_SetLow() do { PORTA_OUTCLR = 0x1; } while(0)
#define RS485_TX_Toggle() do { PORTA_OUTTGL = 0x1; } while(0)
#define RS485_TX_GetValue() (VPORTA.IN & (0x1 << 0))
#define RS485_TX_SetDigitalInput() do { PORTA_DIRCLR = 0x1; } while(0)
#define RS485_TX_SetDigitalOutput() do { PORTA_DIRSET = 0x1; } while(0)
#define RS485_TX_SetPullUp() do { PORTA_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define RS485_TX_ResetPullUp() do { PORTA_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define RS485_TX_SetInverted() do { PORTA_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define RS485_TX_ResetInverted() do { PORTA_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define RS485_TX_DisableInterruptOnChange() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define RS485_TX_EnableInterruptForBothEdges() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define RS485_TX_EnableInterruptForRisingEdge() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define RS485_TX_EnableInterruptForFallingEdge() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define RS485_TX_DisableDigitalInputBuffer() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define RS485_TX_EnableInterruptForLowLevelSensing() do { PORTA.PIN0CTRL = (PORTA.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set RS485_OE aliases
#define RS485_OE_SetHigh() do { PORTD_OUTSET = 0x40; } while(0)
#define RS485_OE_SetLow() do { PORTD_OUTCLR = 0x40; } while(0)
#define RS485_OE_Toggle() do { PORTD_OUTTGL = 0x40; } while(0)
#define RS485_OE_GetValue() (VPORTD.IN & (0x1 << 6))
#define RS485_OE_SetDigitalInput() do { PORTD_DIRCLR = 0x40; } while(0)
#define RS485_OE_SetDigitalOutput() do { PORTD_DIRSET = 0x40; } while(0)
#define RS485_OE_SetPullUp() do { PORTD_PIN6CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define RS485_OE_ResetPullUp() do { PORTD_PIN6CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define RS485_OE_SetInverted() do { PORTD_PIN6CTRL  |= PORT_INVEN_bm; } while(0)
#define RS485_OE_ResetInverted() do { PORTD_PIN6CTRL  &= ~PORT_INVEN_bm; } while(0)
#define RS485_OE_DisableInterruptOnChange() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define RS485_OE_EnableInterruptForBothEdges() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define RS485_OE_EnableInterruptForRisingEdge() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define RS485_OE_EnableInterruptForFallingEdge() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define RS485_OE_DisableDigitalInputBuffer() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define RS485_OE_EnableInterruptForLowLevelSensing() do { PORTD.PIN6CTRL = (PORTD.PIN6CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set LED aliases
#define LED_SetHigh() do { PORTF_OUTSET = 0x40; } while(0)
#define LED_SetLow() do { PORTF_OUTCLR = 0x40; } while(0)
#define LED_Toggle() do { PORTF_OUTTGL = 0x40; } while(0)
#define LED_GetValue() (VPORTF.IN & (0x1 << 6))
#define LED_SetDigitalInput() do { PORTF_DIRCLR = 0x40; } while(0)
#define LED_SetDigitalOutput() do { PORTF_DIRSET = 0x40; } while(0)
#define LED_SetPullUp() do { PORTF_PIN6CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define LED_ResetPullUp() do { PORTF_PIN6CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define LED_SetInverted() do { PORTF_PIN6CTRL  |= PORT_INVEN_bm; } while(0)
#define LED_ResetInverted() do { PORTF_PIN6CTRL  &= ~PORT_INVEN_bm; } while(0)
#define LED_DisableInterruptOnChange() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define LED_EnableInterruptForBothEdges() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define LED_EnableInterruptForRisingEdge() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define LED_EnableInterruptForFallingEdge() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define LED_DisableDigitalInputBuffer() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define LED_EnableInterruptForLowLevelSensing() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize();

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PC3 pin. 
 *        This is a predefined interrupt handler to be used together with the PC3_SetInterruptHandler() method.
 *        This handler is called every time the PC3 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PC3_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PC3 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PC3 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PC3_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PC2 pin. 
 *        This is a predefined interrupt handler to be used together with the PC2_SetInterruptHandler() method.
 *        This handler is called every time the PC2 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PC2_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PC2 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PC2 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PC2_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PF0 pin. 
 *        This is a predefined interrupt handler to be used together with the PF0_SetInterruptHandler() method.
 *        This handler is called every time the PF0 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PF0_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PF0 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PF0 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PF0_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PF1 pin. 
 *        This is a predefined interrupt handler to be used together with the PF1_SetInterruptHandler() method.
 *        This handler is called every time the PF1 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PF1_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PF1 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PF1 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PF1_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PA4 pin. 
 *        This is a predefined interrupt handler to be used together with the PA4_SetInterruptHandler() method.
 *        This handler is called every time the PA4 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PA4_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PA4 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PA4 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PA4_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PA5 pin. 
 *        This is a predefined interrupt handler to be used together with the PA5_SetInterruptHandler() method.
 *        This handler is called every time the PA5 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PA5_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PA5 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PA5 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PA5_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PD4 pin. 
 *        This is a predefined interrupt handler to be used together with the PD4_SetInterruptHandler() method.
 *        This handler is called every time the PD4 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PD4_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PD4 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PD4 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PD4_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PD5 pin. 
 *        This is a predefined interrupt handler to be used together with the PD5_SetInterruptHandler() method.
 *        This handler is called every time the PD5 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PD5_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PD5 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PD5 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PD5_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PA6 pin. 
 *        This is a predefined interrupt handler to be used together with the PA6_SetInterruptHandler() method.
 *        This handler is called every time the PA6 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PA6_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PA6 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PA6 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PA6_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PA7 pin. 
 *        This is a predefined interrupt handler to be used together with the PA7_SetInterruptHandler() method.
 *        This handler is called every time the PA7 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PA7_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PA7 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PA7 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PA7_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PC1 pin. 
 *        This is a predefined interrupt handler to be used together with the PC1_SetInterruptHandler() method.
 *        This handler is called every time the PC1 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PC1_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PC1 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PC1 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PC1_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PD1 pin. 
 *        This is a predefined interrupt handler to be used together with the PD1_SetInterruptHandler() method.
 *        This handler is called every time the PD1 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PD1_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PD1 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PD1 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PD1_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PD2 pin. 
 *        This is a predefined interrupt handler to be used together with the PD2_SetInterruptHandler() method.
 *        This handler is called every time the PD2 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PD2_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PD2 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PD2 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PD2_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PD3 pin. 
 *        This is a predefined interrupt handler to be used together with the PD3_SetInterruptHandler() method.
 *        This handler is called every time the PD3 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PD3_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PD3 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PD3 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PD3_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PA3 pin. 
 *        This is a predefined interrupt handler to be used together with the PA3_SetInterruptHandler() method.
 *        This handler is called every time the PA3 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PA3_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PA3 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PA3 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PA3_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PA2 pin. 
 *        This is a predefined interrupt handler to be used together with the PA2_SetInterruptHandler() method.
 *        This handler is called every time the PA2 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PA2_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PA2 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PA2 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PA2_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PC0 pin. 
 *        This is a predefined interrupt handler to be used together with the PC0_SetInterruptHandler() method.
 *        This handler is called every time the PC0 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PC0_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PC0 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PC0 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PC0_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PA1 pin. 
 *        This is a predefined interrupt handler to be used together with the PA1_SetInterruptHandler() method.
 *        This handler is called every time the PA1 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PA1_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PA1 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PA1 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PA1_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PA0 pin. 
 *        This is a predefined interrupt handler to be used together with the PA0_SetInterruptHandler() method.
 *        This handler is called every time the PA0 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PA0_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PA0 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PA0 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PA0_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PD6 pin. 
 *        This is a predefined interrupt handler to be used together with the PD6_SetInterruptHandler() method.
 *        This handler is called every time the PD6 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PD6_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PD6 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PD6 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PD6_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PF6 pin. 
 *        This is a predefined interrupt handler to be used together with the PF6_SetInterruptHandler() method.
 *        This handler is called every time the PF6 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PF6_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PF6 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PF6 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PF6_SetInterruptHandler(void (* interruptHandler)(void)) ; 
#endif /* PINS_H_INCLUDED */
