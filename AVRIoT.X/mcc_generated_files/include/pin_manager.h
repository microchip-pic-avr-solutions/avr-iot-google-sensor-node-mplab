/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   1.0.0
*/
/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PINS_H_INCLUDED
#define PINS_H_INCLUDED

#include <avr/io.h>
#include "port.h"

//get/set PD5 aliases
#define PD5_SetHigh() do { PORTD_OUTSET = 0x20; } while(0)
#define PD5_SetLow() do { PORTD_OUTCLR = 0x20; } while(0)
#define PD5_Toggle() do { PORTD_OUTTGL = 0x20; } while(0)
#define PD5_GetValue() (VPORTD.IN & (0x1 << 5))
#define PD5_SetDigitalInput() do { PORTD_DIRCLR = 0x20; } while(0)
#define PD5_SetDigitalOutput() do { PORTD_DIRSET = 0x20; } while(0)
#define PD5_SetPullUp() do { PORTD_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PD5_ResetPullUp() do { PORTD_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PD5_SetInverted() do { PORTD_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define PD5_ResetInverted() do { PORTD_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PD5_DisableInterruptOnChange() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PD5_EnableInterruptForBothEdges() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PD5_EnableInterruptForRisingEdge() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PD5_EnableInterruptForFallingEdge() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PD5_DisableDigitalInputBuffer() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PD5_EnableInterruptForLowLevelSensing() do { PORTD.PIN5CTRL = (PORTD.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PA2 aliases
#define PA2_SetHigh() do { PORTA_OUTSET = 0x4; } while(0)
#define PA2_SetLow() do { PORTA_OUTCLR = 0x4; } while(0)
#define PA2_Toggle() do { PORTA_OUTTGL = 0x4; } while(0)
#define PA2_GetValue() (VPORTA.IN & (0x1 << 2))
#define PA2_SetDigitalInput() do { PORTA_DIRCLR = 0x4; } while(0)
#define PA2_SetDigitalOutput() do { PORTA_DIRSET = 0x4; } while(0)
#define PA2_SetPullUp() do { PORTA_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PA2_ResetPullUp() do { PORTA_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PA2_SetInverted() do { PORTA_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define PA2_ResetInverted() do { PORTA_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PA2_DisableInterruptOnChange() do { PORTA.PIN2CTRL = (PORTA.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PA2_EnableInterruptForBothEdges() do { PORTA.PIN2CTRL = (PORTA.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PA2_EnableInterruptForRisingEdge() do { PORTA.PIN2CTRL = (PORTA.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PA2_EnableInterruptForFallingEdge() do { PORTA.PIN2CTRL = (PORTA.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PA2_DisableDigitalInputBuffer() do { PORTA.PIN2CTRL = (PORTA.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PA2_EnableInterruptForLowLevelSensing() do { PORTA.PIN2CTRL = (PORTA.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set SW0 aliases
#define SW0_SetHigh() do { PORTF_OUTSET = 0x40; } while(0)
#define SW0_SetLow() do { PORTF_OUTCLR = 0x40; } while(0)
#define SW0_Toggle() do { PORTF_OUTTGL = 0x40; } while(0)
#define SW0_GetValue() (VPORTF.IN & (0x1 << 6))
#define SW0_SetDigitalInput() do { PORTF_DIRCLR = 0x40; } while(0)
#define SW0_SetDigitalOutput() do { PORTF_DIRSET = 0x40; } while(0)
#define SW0_SetPullUp() do { PORTF_PIN6CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define SW0_ResetPullUp() do { PORTF_PIN6CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define SW0_SetInverted() do { PORTF_PIN6CTRL  |= PORT_INVEN_bm; } while(0)
#define SW0_ResetInverted() do { PORTF_PIN6CTRL  &= ~PORT_INVEN_bm; } while(0)
#define SW0_DisableInterruptOnChange() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define SW0_EnableInterruptForBothEdges() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define SW0_EnableInterruptForRisingEdge() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define SW0_EnableInterruptForFallingEdge() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define SW0_DisableDigitalInputBuffer() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define SW0_EnableInterruptForLowLevelSensing() do { PORTF.PIN6CTRL = (PORTF.PIN6CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set RST aliases
#define RST_SetHigh() do { PORTA_OUTSET = 0x2; } while(0)
#define RST_SetLow() do { PORTA_OUTCLR = 0x2; } while(0)
#define RST_Toggle() do { PORTA_OUTTGL = 0x2; } while(0)
#define RST_GetValue() (VPORTA.IN & (0x1 << 1))
#define RST_SetDigitalInput() do { PORTA_DIRCLR = 0x2; } while(0)
#define RST_SetDigitalOutput() do { PORTA_DIRSET = 0x2; } while(0)
#define RST_SetPullUp() do { PORTA_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define RST_ResetPullUp() do { PORTA_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define RST_SetInverted() do { PORTA_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define RST_ResetInverted() do { PORTA_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define RST_DisableInterruptOnChange() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define RST_EnableInterruptForBothEdges() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define RST_EnableInterruptForRisingEdge() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define RST_EnableInterruptForFallingEdge() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define RST_DisableDigitalInputBuffer() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define RST_EnableInterruptForLowLevelSensing() do { PORTA.PIN1CTRL = (PORTA.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PA4 aliases
#define PA4_SetHigh() do { PORTA_OUTSET = 0x10; } while(0)
#define PA4_SetLow() do { PORTA_OUTCLR = 0x10; } while(0)
#define PA4_Toggle() do { PORTA_OUTTGL = 0x10; } while(0)
#define PA4_GetValue() (VPORTA.IN & (0x1 << 4))
#define PA4_SetDigitalInput() do { PORTA_DIRCLR = 0x10; } while(0)
#define PA4_SetDigitalOutput() do { PORTA_DIRSET = 0x10; } while(0)
#define PA4_SetPullUp() do { PORTA_PIN4CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PA4_ResetPullUp() do { PORTA_PIN4CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PA4_SetInverted() do { PORTA_PIN4CTRL  |= PORT_INVEN_bm; } while(0)
#define PA4_ResetInverted() do { PORTA_PIN4CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PA4_DisableInterruptOnChange() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PA4_EnableInterruptForBothEdges() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PA4_EnableInterruptForRisingEdge() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PA4_EnableInterruptForFallingEdge() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PA4_DisableDigitalInputBuffer() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PA4_EnableInterruptForLowLevelSensing() do { PORTA.PIN4CTRL = (PORTA.PIN4CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PA3 aliases
#define PA3_SetHigh() do { PORTA_OUTSET = 0x8; } while(0)
#define PA3_SetLow() do { PORTA_OUTCLR = 0x8; } while(0)
#define PA3_Toggle() do { PORTA_OUTTGL = 0x8; } while(0)
#define PA3_GetValue() (VPORTA.IN & (0x1 << 3))
#define PA3_SetDigitalInput() do { PORTA_DIRCLR = 0x8; } while(0)
#define PA3_SetDigitalOutput() do { PORTA_DIRSET = 0x8; } while(0)
#define PA3_SetPullUp() do { PORTA_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PA3_ResetPullUp() do { PORTA_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PA3_SetInverted() do { PORTA_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define PA3_ResetInverted() do { PORTA_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PA3_DisableInterruptOnChange() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PA3_EnableInterruptForBothEdges() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PA3_EnableInterruptForRisingEdge() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PA3_EnableInterruptForFallingEdge() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PA3_DisableDigitalInputBuffer() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PA3_EnableInterruptForLowLevelSensing() do { PORTA.PIN3CTRL = (PORTA.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PA6 aliases
#define PA6_SetHigh() do { PORTA_OUTSET = 0x40; } while(0)
#define PA6_SetLow() do { PORTA_OUTCLR = 0x40; } while(0)
#define PA6_Toggle() do { PORTA_OUTTGL = 0x40; } while(0)
#define PA6_GetValue() (VPORTA.IN & (0x1 << 6))
#define PA6_SetDigitalInput() do { PORTA_DIRCLR = 0x40; } while(0)
#define PA6_SetDigitalOutput() do { PORTA_DIRSET = 0x40; } while(0)
#define PA6_SetPullUp() do { PORTA_PIN6CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PA6_ResetPullUp() do { PORTA_PIN6CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PA6_SetInverted() do { PORTA_PIN6CTRL  |= PORT_INVEN_bm; } while(0)
#define PA6_ResetInverted() do { PORTA_PIN6CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PA6_DisableInterruptOnChange() do { PORTA.PIN6CTRL = (PORTA.PIN6CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PA6_EnableInterruptForBothEdges() do { PORTA.PIN6CTRL = (PORTA.PIN6CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PA6_EnableInterruptForRisingEdge() do { PORTA.PIN6CTRL = (PORTA.PIN6CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PA6_EnableInterruptForFallingEdge() do { PORTA.PIN6CTRL = (PORTA.PIN6CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PA6_DisableDigitalInputBuffer() do { PORTA.PIN6CTRL = (PORTA.PIN6CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PA6_EnableInterruptForLowLevelSensing() do { PORTA.PIN6CTRL = (PORTA.PIN6CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PA5 aliases
#define PA5_SetHigh() do { PORTA_OUTSET = 0x20; } while(0)
#define PA5_SetLow() do { PORTA_OUTCLR = 0x20; } while(0)
#define PA5_Toggle() do { PORTA_OUTTGL = 0x20; } while(0)
#define PA5_GetValue() (VPORTA.IN & (0x1 << 5))
#define PA5_SetDigitalInput() do { PORTA_DIRCLR = 0x20; } while(0)
#define PA5_SetDigitalOutput() do { PORTA_DIRSET = 0x20; } while(0)
#define PA5_SetPullUp() do { PORTA_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PA5_ResetPullUp() do { PORTA_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PA5_SetInverted() do { PORTA_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define PA5_ResetInverted() do { PORTA_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PA5_DisableInterruptOnChange() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PA5_EnableInterruptForBothEdges() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PA5_EnableInterruptForRisingEdge() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PA5_EnableInterruptForFallingEdge() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PA5_DisableDigitalInputBuffer() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PA5_EnableInterruptForLowLevelSensing() do { PORTA.PIN5CTRL = (PORTA.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set nCS aliases
#define nCS_SetHigh() do { PORTA_OUTSET = 0x80; } while(0)
#define nCS_SetLow() do { PORTA_OUTCLR = 0x80; } while(0)
#define nCS_Toggle() do { PORTA_OUTTGL = 0x80; } while(0)
#define nCS_GetValue() (VPORTA.IN & (0x1 << 7))
#define nCS_SetDigitalInput() do { PORTA_DIRCLR = 0x80; } while(0)
#define nCS_SetDigitalOutput() do { PORTA_DIRSET = 0x80; } while(0)
#define nCS_SetPullUp() do { PORTA_PIN7CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define nCS_ResetPullUp() do { PORTA_PIN7CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define nCS_SetInverted() do { PORTA_PIN7CTRL  |= PORT_INVEN_bm; } while(0)
#define nCS_ResetInverted() do { PORTA_PIN7CTRL  &= ~PORT_INVEN_bm; } while(0)
#define nCS_DisableInterruptOnChange() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define nCS_EnableInterruptForBothEdges() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define nCS_EnableInterruptForRisingEdge() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define nCS_EnableInterruptForFallingEdge() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define nCS_DisableDigitalInputBuffer() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define nCS_EnableInterruptForLowLevelSensing() do { PORTA.PIN7CTRL = (PORTA.PIN7CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PF1 aliases
#define PF1_SetHigh() do { PORTF_OUTSET = 0x2; } while(0)
#define PF1_SetLow() do { PORTF_OUTCLR = 0x2; } while(0)
#define PF1_Toggle() do { PORTF_OUTTGL = 0x2; } while(0)
#define PF1_GetValue() (VPORTF.IN & (0x1 << 1))
#define PF1_SetDigitalInput() do { PORTF_DIRCLR = 0x2; } while(0)
#define PF1_SetDigitalOutput() do { PORTF_DIRSET = 0x2; } while(0)
#define PF1_SetPullUp() do { PORTF_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PF1_ResetPullUp() do { PORTF_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PF1_SetInverted() do { PORTF_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define PF1_ResetInverted() do { PORTF_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PF1_DisableInterruptOnChange() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PF1_EnableInterruptForBothEdges() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PF1_EnableInterruptForRisingEdge() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PF1_EnableInterruptForFallingEdge() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PF1_DisableDigitalInputBuffer() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PF1_EnableInterruptForLowLevelSensing() do { PORTF.PIN1CTRL = (PORTF.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set PF0 aliases
#define PF0_SetHigh() do { PORTF_OUTSET = 0x1; } while(0)
#define PF0_SetLow() do { PORTF_OUTCLR = 0x1; } while(0)
#define PF0_Toggle() do { PORTF_OUTTGL = 0x1; } while(0)
#define PF0_GetValue() (VPORTF.IN & (0x1 << 0))
#define PF0_SetDigitalInput() do { PORTF_DIRCLR = 0x1; } while(0)
#define PF0_SetDigitalOutput() do { PORTF_DIRSET = 0x1; } while(0)
#define PF0_SetPullUp() do { PORTF_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define PF0_ResetPullUp() do { PORTF_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define PF0_SetInverted() do { PORTF_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define PF0_ResetInverted() do { PORTF_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define PF0_DisableInterruptOnChange() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define PF0_EnableInterruptForBothEdges() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define PF0_EnableInterruptForRisingEdge() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define PF0_EnableInterruptForFallingEdge() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define PF0_DisableDigitalInputBuffer() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define PF0_EnableInterruptForLowLevelSensing() do { PORTF.PIN0CTRL = (PORTF.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set LED_YELLOW aliases
#define LED_YELLOW_SetHigh() do { PORTD_OUTSET = 0x2; } while(0)
#define LED_YELLOW_SetLow() do { PORTD_OUTCLR = 0x2; } while(0)
#define LED_YELLOW_Toggle() do { PORTD_OUTTGL = 0x2; } while(0)
#define LED_YELLOW_GetValue() (VPORTD.IN & (0x1 << 1))
#define LED_YELLOW_SetDigitalInput() do { PORTD_DIRCLR = 0x2; } while(0)
#define LED_YELLOW_SetDigitalOutput() do { PORTD_DIRSET = 0x2; } while(0)
#define LED_YELLOW_SetPullUp() do { PORTD_PIN1CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define LED_YELLOW_ResetPullUp() do { PORTD_PIN1CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define LED_YELLOW_SetInverted() do { PORTD_PIN1CTRL  |= PORT_INVEN_bm; } while(0)
#define LED_YELLOW_ResetInverted() do { PORTD_PIN1CTRL  &= ~PORT_INVEN_bm; } while(0)
#define LED_YELLOW_DisableInterruptOnChange() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define LED_YELLOW_EnableInterruptForBothEdges() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define LED_YELLOW_EnableInterruptForRisingEdge() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define LED_YELLOW_EnableInterruptForFallingEdge() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define LED_YELLOW_DisableDigitalInputBuffer() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define LED_YELLOW_EnableInterruptForLowLevelSensing() do { PORTD.PIN1CTRL = (PORTD.PIN1CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set CE aliases
#define CE_SetHigh() do { PORTF_OUTSET = 0x8; } while(0)
#define CE_SetLow() do { PORTF_OUTCLR = 0x8; } while(0)
#define CE_Toggle() do { PORTF_OUTTGL = 0x8; } while(0)
#define CE_GetValue() (VPORTF.IN & (0x1 << 3))
#define CE_SetDigitalInput() do { PORTF_DIRCLR = 0x8; } while(0)
#define CE_SetDigitalOutput() do { PORTF_DIRSET = 0x8; } while(0)
#define CE_SetPullUp() do { PORTF_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define CE_ResetPullUp() do { PORTF_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define CE_SetInverted() do { PORTF_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define CE_ResetInverted() do { PORTF_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define CE_DisableInterruptOnChange() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define CE_EnableInterruptForBothEdges() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define CE_EnableInterruptForRisingEdge() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define CE_EnableInterruptForFallingEdge() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define CE_DisableDigitalInputBuffer() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define CE_EnableInterruptForLowLevelSensing() do { PORTF.PIN3CTRL = (PORTF.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set LED_RED aliases
#define LED_RED_SetHigh() do { PORTD_OUTSET = 0x1; } while(0)
#define LED_RED_SetLow() do { PORTD_OUTCLR = 0x1; } while(0)
#define LED_RED_Toggle() do { PORTD_OUTTGL = 0x1; } while(0)
#define LED_RED_GetValue() (VPORTD.IN & (0x1 << 0))
#define LED_RED_SetDigitalInput() do { PORTD_DIRCLR = 0x1; } while(0)
#define LED_RED_SetDigitalOutput() do { PORTD_DIRSET = 0x1; } while(0)
#define LED_RED_SetPullUp() do { PORTD_PIN0CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define LED_RED_ResetPullUp() do { PORTD_PIN0CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define LED_RED_SetInverted() do { PORTD_PIN0CTRL  |= PORT_INVEN_bm; } while(0)
#define LED_RED_ResetInverted() do { PORTD_PIN0CTRL  &= ~PORT_INVEN_bm; } while(0)
#define LED_RED_DisableInterruptOnChange() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define LED_RED_EnableInterruptForBothEdges() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define LED_RED_EnableInterruptForRisingEdge() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define LED_RED_EnableInterruptForFallingEdge() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define LED_RED_DisableDigitalInputBuffer() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define LED_RED_EnableInterruptForLowLevelSensing() do { PORTD.PIN0CTRL = (PORTD.PIN0CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set INT aliases
#define INT_SetHigh() do { PORTF_OUTSET = 0x4; } while(0)
#define INT_SetLow() do { PORTF_OUTCLR = 0x4; } while(0)
#define INT_Toggle() do { PORTF_OUTTGL = 0x4; } while(0)
#define INT_GetValue() (VPORTF.IN & (0x1 << 2))
#define INT_SetDigitalInput() do { PORTF_DIRCLR = 0x4; } while(0)
#define INT_SetDigitalOutput() do { PORTF_DIRSET = 0x4; } while(0)
#define INT_SetPullUp() do { PORTF_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define INT_ResetPullUp() do { PORTF_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define INT_SetInverted() do { PORTF_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define INT_ResetInverted() do { PORTF_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define INT_DisableInterruptOnChange() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define INT_EnableInterruptForBothEdges() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define INT_EnableInterruptForRisingEdge() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define INT_EnableInterruptForFallingEdge() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define INT_DisableDigitalInputBuffer() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define INT_EnableInterruptForLowLevelSensing() do { PORTF.PIN2CTRL = (PORTF.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set SW1 aliases
#define SW1_SetHigh() do { PORTF_OUTSET = 0x20; } while(0)
#define SW1_SetLow() do { PORTF_OUTCLR = 0x20; } while(0)
#define SW1_Toggle() do { PORTF_OUTTGL = 0x20; } while(0)
#define SW1_GetValue() (VPORTF.IN & (0x1 << 5))
#define SW1_SetDigitalInput() do { PORTF_DIRCLR = 0x20; } while(0)
#define SW1_SetDigitalOutput() do { PORTF_DIRSET = 0x20; } while(0)
#define SW1_SetPullUp() do { PORTF_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define SW1_ResetPullUp() do { PORTF_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define SW1_SetInverted() do { PORTF_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define SW1_ResetInverted() do { PORTF_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define SW1_DisableInterruptOnChange() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define SW1_EnableInterruptForBothEdges() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define SW1_EnableInterruptForRisingEdge() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define SW1_EnableInterruptForFallingEdge() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define SW1_DisableDigitalInputBuffer() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define SW1_EnableInterruptForLowLevelSensing() do { PORTF.PIN5CTRL = (PORTF.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set LED_BLUE aliases
#define LED_BLUE_SetHigh() do { PORTD_OUTSET = 0x8; } while(0)
#define LED_BLUE_SetLow() do { PORTD_OUTCLR = 0x8; } while(0)
#define LED_BLUE_Toggle() do { PORTD_OUTTGL = 0x8; } while(0)
#define LED_BLUE_GetValue() (VPORTD.IN & (0x1 << 3))
#define LED_BLUE_SetDigitalInput() do { PORTD_DIRCLR = 0x8; } while(0)
#define LED_BLUE_SetDigitalOutput() do { PORTD_DIRSET = 0x8; } while(0)
#define LED_BLUE_SetPullUp() do { PORTD_PIN3CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define LED_BLUE_ResetPullUp() do { PORTD_PIN3CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define LED_BLUE_SetInverted() do { PORTD_PIN3CTRL  |= PORT_INVEN_bm; } while(0)
#define LED_BLUE_ResetInverted() do { PORTD_PIN3CTRL  &= ~PORT_INVEN_bm; } while(0)
#define LED_BLUE_DisableInterruptOnChange() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define LED_BLUE_EnableInterruptForBothEdges() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define LED_BLUE_EnableInterruptForRisingEdge() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define LED_BLUE_EnableInterruptForFallingEdge() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define LED_BLUE_DisableDigitalInputBuffer() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define LED_BLUE_EnableInterruptForLowLevelSensing() do { PORTD.PIN3CTRL = (PORTD.PIN3CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set LED_GREEN aliases
#define LED_GREEN_SetHigh() do { PORTD_OUTSET = 0x4; } while(0)
#define LED_GREEN_SetLow() do { PORTD_OUTCLR = 0x4; } while(0)
#define LED_GREEN_Toggle() do { PORTD_OUTTGL = 0x4; } while(0)
#define LED_GREEN_GetValue() (VPORTD.IN & (0x1 << 2))
#define LED_GREEN_SetDigitalInput() do { PORTD_DIRCLR = 0x4; } while(0)
#define LED_GREEN_SetDigitalOutput() do { PORTD_DIRSET = 0x4; } while(0)
#define LED_GREEN_SetPullUp() do { PORTD_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define LED_GREEN_ResetPullUp() do { PORTD_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define LED_GREEN_SetInverted() do { PORTD_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define LED_GREEN_ResetInverted() do { PORTD_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define LED_GREEN_DisableInterruptOnChange() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define LED_GREEN_EnableInterruptForBothEdges() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define LED_GREEN_EnableInterruptForRisingEdge() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define LED_GREEN_EnableInterruptForFallingEdge() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define LED_GREEN_DisableDigitalInputBuffer() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define LED_GREEN_EnableInterruptForLowLevelSensing() do { PORTD.PIN2CTRL = (PORTD.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set WAKE aliases
#define WAKE_SetHigh() do { PORTF_OUTSET = 0x10; } while(0)
#define WAKE_SetLow() do { PORTF_OUTCLR = 0x10; } while(0)
#define WAKE_Toggle() do { PORTF_OUTTGL = 0x10; } while(0)
#define WAKE_GetValue() (VPORTF.IN & (0x1 << 4))
#define WAKE_SetDigitalInput() do { PORTF_DIRCLR = 0x10; } while(0)
#define WAKE_SetDigitalOutput() do { PORTF_DIRSET = 0x10; } while(0)
#define WAKE_SetPullUp() do { PORTF_PIN4CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define WAKE_ResetPullUp() do { PORTF_PIN4CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define WAKE_SetInverted() do { PORTF_PIN4CTRL  |= PORT_INVEN_bm; } while(0)
#define WAKE_ResetInverted() do { PORTF_PIN4CTRL  &= ~PORT_INVEN_bm; } while(0)
#define WAKE_DisableInterruptOnChange() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define WAKE_EnableInterruptForBothEdges() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define WAKE_EnableInterruptForRisingEdge() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define WAKE_EnableInterruptForFallingEdge() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define WAKE_DisableDigitalInputBuffer() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define WAKE_EnableInterruptForLowLevelSensing() do { PORTF.PIN4CTRL = (PORTF.PIN4CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

void PIN_MANAGER_Initialize();
void PORTD_PD5_DefaultInterruptHandler(void);
void PORTD_PD5_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTA_PA2_DefaultInterruptHandler(void);
void PORTA_PA2_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTF_SW0_DefaultInterruptHandler(void);
void PORTF_SW0_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTA_RST_DefaultInterruptHandler(void);
void PORTA_RST_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTA_PA4_DefaultInterruptHandler(void);
void PORTA_PA4_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTA_PA3_DefaultInterruptHandler(void);
void PORTA_PA3_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTA_PA6_DefaultInterruptHandler(void);
void PORTA_PA6_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTA_PA5_DefaultInterruptHandler(void);
void PORTA_PA5_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTA_nCS_DefaultInterruptHandler(void);
void PORTA_nCS_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTF_PF1_DefaultInterruptHandler(void);
void PORTF_PF1_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTF_PF0_DefaultInterruptHandler(void);
void PORTF_PF0_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTD_LED_YELLOW_DefaultInterruptHandler(void);
void PORTD_LED_YELLOW_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTF_CE_DefaultInterruptHandler(void);
void PORTF_CE_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTD_LED_RED_DefaultInterruptHandler(void);
void PORTD_LED_RED_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTF_INT_DefaultInterruptHandler(void);
void PORTF_INT_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTF_SW1_DefaultInterruptHandler(void);
void PORTF_SW1_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTD_LED_BLUE_DefaultInterruptHandler(void);
void PORTD_LED_BLUE_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTD_LED_GREEN_DefaultInterruptHandler(void);
void PORTD_LED_GREEN_SetInterruptHandler(void (* interruptHandler)(void)) ;
void PORTF_WAKE_DefaultInterruptHandler(void);
void PORTF_WAKE_SetInterruptHandler(void (* interruptHandler)(void)) ;
#endif /* PINS_H_INCLUDED */
