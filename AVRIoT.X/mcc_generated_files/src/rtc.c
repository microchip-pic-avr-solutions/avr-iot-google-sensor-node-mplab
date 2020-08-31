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


#include "../include/rtc.h"

/**
 * \brief Initialize rtc interface
 *
 * \return Initialization status.
 */

void (*RTC_OVF_isr_cb)(void) = NULL;
void (*RTC_CMP_isr_cb)(void) = NULL;
void (*RTC_PIT_isr_cb)(void) = NULL;

/**
 * \brief Initialize RTC interface
 */
int8_t RTC_Initialize()
{
        while (RTC.STATUS > 0) { /* Wait for all register to be synchronized */
    }
    //Compare 
    RTC.CMP = 0x00;

    //Count
    RTC.CNT = 0x00;

    //Period
    RTC.PER = 0xFFFF;

    //Clock selection
    RTC.CLKSEL = 0x01;

    //DBGRUN disabled; 
    RTC.DBGCTRL = 0x00;

    //CMP disabled; OVF enabled; 
    RTC.INTCTRL = 0x01;

    //PERIOD OFF; PITEN disabled; 
    RTC.PITCTRLA = 0x00;

    //DBGRUN disabled; 
    RTC.PITDBGCTRL = 0x00;

    //PI disabled; 
	RTC.PITINTCTRL = 0x00;

    //RUNSTDBY disabled; PRESCALER DIV1; CORREN disabled; RTCEN enabled; 
    RTC.CTRLA = 0x01;

    return 0;
}

void RTC_SetOVFIsrCallback(RTC_cb_t cb)
{
    RTC_OVF_isr_cb = cb;
}

void RTC_SetCMPIsrCallback(RTC_cb_t cb)
{
    RTC_CMP_isr_cb = cb;
}

ISR(RTC_CNT_vect)
{
    if (RTC.INTFLAGS & RTC_OVF_bm )
    {
        if (RTC_OVF_isr_cb != NULL) 
        {
            (*RTC_OVF_isr_cb)();
        } 
    }  
    
    if (RTC.INTFLAGS & RTC_CMP_bm )
    {
        if (RTC_CMP_isr_cb != NULL) 
        {
            (*RTC_CMP_isr_cb)();
        } 
    }   
    RTC.INTFLAGS = (RTC_OVF_bm | RTC_CMP_bm);
}

ISR(RTC_PIT_vect)
{
   if (RTC_PIT_isr_cb != NULL) 
   {
    (*RTC_PIT_isr_cb)();
   } 
   RTC.INTFLAGS = RTC_PI_bm;
}

inline void RTC_WriteCounter(uint16_t timerVal)
{
    while (RTC.STATUS & RTC_CNTBUSY_bm);
    RTC.CNT = timerVal;
}

inline uint16_t RTC_ReadCounter(void)
{
    return RTC.CNT;
}

inline void RTC_WritePeroid(uint16_t timerVal)
{
    while (RTC.STATUS & RTC_PERBUSY_bm);
    RTC.PER = timerVal;
}

inline uint16_t RTC_ReadPeriod(void)
{
    return RTC.PER;
}

inline void RTC_EnableCMPInterrupt(void)
{
    RTC.INTCTRL |= RTC_CMP_bm; 
}

inline void RTC_DisableCMPInterrupt(void)
{
    RTC.INTCTRL &= ~RTC_CMP_bm; 
}

inline void RTC_EnableOVFInterrupt(void)
{
    RTC.INTCTRL |= RTC_OVF_bm; 
}

inline void RTC_DisableOVFInterrupt(void)
{
    RTC.INTCTRL &= ~RTC_OVF_bm; 
}

inline void RTC_EnablePITInterrupt(void)
{
    RTC.INTCTRL |= RTC_PI_bm;  
}

inline void RTC_DisablePITInterrupt(void)
{
    RTC.INTCTRL &= ~RTC_PI_bm; 
}

inline void RTC_ClearOVFInterruptFlag(void)
{
    RTC.INTFLAGS &= ~RTC_OVF_bm;
}

inline bool RTC_IsOVFInterruptEnabled(void)
{
    return ((RTC.INTCTRL & RTC_OVF_bm) > 0);
}
