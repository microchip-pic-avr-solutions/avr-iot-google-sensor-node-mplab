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


#include "../include/adc0.h"

adc_irq_cb_t ADC0_window_cb = NULL;

/**
 * \brief Initialize ADC interface
 */
int8_t ADC0_Initialize()
{
     
    //DUTYCYC DUTY25; 
	ADC0.CALIB = 0x01;

    //SAMPNUM ACC1; 
	ADC0.CTRLB = 0x00;

    //SAMPCAP disabled; REFSEL VDDREF; PRESC DIV16; 
	ADC0.CTRLC = 0x13;

    //INITDLY DLY0; ASDV ASVOFF; SAMPDLY 0; 
	ADC0.CTRLD = 0x00;

    //WINCM NONE; 
	ADC0.CTRLE = 0x00;

    //DBGRUN disabled; 
	ADC0.DBGCTRL = 0x00;

    //STARTEI disabled; 
	ADC0.EVCTRL = 0x00;

    //WCMP disabled; RESRDY disabled; 
	ADC0.INTCTRL = 0x00;

    //MUXPOS AIN5; 
	ADC0.MUXPOS = 0x05;

    //SAMPLEN 0; 
	ADC0.SAMPCTRL = 0x00;

    // Window comparator high threshold 
	ADC0.WINHT = 0x00;

    // Window comparator low threshold 
	ADC0.WINLT = 0x00;

    //RUNSTBY disabled; RESSEL 10BIT; FREERUN disabled; ENABLE enabled; 
	ADC0.CTRLA = 0x01;


	return 0;
}

void ADC0_Enable()
{
	ADC0.CTRLA |= ADC_ENABLE_bm;
}

void ADC0_Disable()
{
	ADC0.CTRLA &= ~ADC_ENABLE_bm;
}

void ADC0_EnableAutoTrigger()
{
	ADC0.EVCTRL |= ADC_STARTEI_bm;
}

void ADC0_DisableAutoTrigger()
{
	ADC0.EVCTRL &= ~ADC_STARTEI_bm;
}

void ADC0_SetWindowHigh(adc_result_t high)
{
	ADC0.WINHT = high;
}

void ADC0_SetWindowLow(adc_result_t low)
{
	ADC0.WINLT = low;
}

void ADC0_SetWindowMode(adc0_window_mode_t mode)
{
	ADC0.CTRLE = mode;
}

void ADC0_SetWindowChannel(adc_0_channel_t channel)
{
	ADC0.MUXPOS = channel;
}

void ADC0_StartConversion(adc_0_channel_t channel)
{
	ADC0.MUXPOS  = channel;
	ADC0.COMMAND = ADC_STCONV_bm;
}

bool ADC0_IsConversionDone()
{
	return (ADC0.INTFLAGS & ADC_RESRDY_bm);
}

adc_result_t ADC0_GetConversionResult(void)
{
	return (ADC0.RES);
}

bool ADC0_GetWindowResult(void)
{
	bool temp     = (ADC0.INTFLAGS & ADC_WCMP_bm);
	ADC0.INTFLAGS = ADC_WCMP_bm; // Clear intflag if set
	return temp;
}

adc_result_t ADC0_GetConversion(adc_0_channel_t channel)
{
	adc_result_t res;

	ADC0_StartConversion(channel);
	while (!ADC0_IsConversionDone());
	res           = ADC0_GetConversionResult();
	ADC0.INTFLAGS = ADC_RESRDY_bm;
	return res;
}

uint8_t ADC0_GetResolution()
{
	return (ADC0.CTRLA & ADC_RESSEL_bm) ? 10 : 12;
}

void ADC0_RegisterWindowCallback(adc_irq_cb_t f)
{
	ADC0_window_cb = f;
}

ISR(ADC0_WCOMP_vect)
{

	if (ADC0_window_cb != NULL) {
		ADC0_window_cb();
	}
        
	// Clear the interrupt flag
	ADC0.INTFLAGS = ADC_WCMP_bm;
}

ISR(ADC0_RESRDY_vect)
{
    /* Insert your ADC result ready interrupt handling code here */

    /* The interrupt flag has to be cleared manually */
    ADC0.INTFLAGS = ADC_RESRDY_bm;
}