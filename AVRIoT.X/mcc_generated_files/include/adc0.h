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


#ifndef ADC0_H_INCLUDED
#define ADC0_H_INCLUDED

#include "../utils/compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	adc0_window_disabled,
	adc0_window_below,
	adc0_window_above,
	adc0_window_inside,
	adc0_window_outside
} adc0_window_mode_t;

/** Function pointer to callback function called by IRQ.
    NULL=default value: No callback function is to be used.
*/
typedef void (*adc_irq_cb_t)(void);

/** Datatype for the result of the ADC conversion */
typedef uint16_t adc_result_t;

//* Analog channel selection */
typedef ADC_MUXPOS_t adc_0_channel_t;

/**
 * \brief Initialize ADC interface
 * If module is configured to disabled state, the clock to the ADC is disabled
 * if this is supported by the device's clock system.
 *
 * \return Initialization status.
 * \retval 0 the ADC init was successful
 * \retval 1 the ADC init was not successful
 */
int8_t ADC0_Initialize();

/**
 * \brief Enable ADC0
 * 1. If supported by the clock system, enables the clock to the ADC
 * 2. Enables the ADC module by setting the enable-bit in the ADC control register
 *
 * \return Nothing
 */
void ADC0_Enable();

/**
 * \brief Disable ADC0
 * 1. Disables the ADC module by clearing the enable-bit in the ADC control register
 * 2. If supported by the clock system, disables the clock to the ADC
 *
 * \return Nothing
 */
void ADC0_Disable();

/**
 * \brief Enable conversion auto-trigger
 *
 * \return Nothing
 */
void ADC0_EnableAutoTrigger();

/**
 * \brief Disable conversion auto-trigger
 *
 * \return Nothing
 */
void ADC0_DisableAutoTrigger();

/**
 * \brief Set conversion window comparator high threshold
 *
 * \return Nothing
 */
void ADC0_SetWindowHigh(adc_result_t high);

/**
 * \brief Set conversion window comparator low threshold
 *
 * \return Nothing
 */
void ADC0_SetWindowLow(adc_result_t low);

/**
 * \brief Set conversion window mode
 *
 * \return Nothing
 */
void ADC0_SetWindowMode(adc0_window_mode_t mode);

/**
 * \brief Set ADC channel to be used for windowed conversion mode
 *
 * \param[in] channel The ADC channel to start conversion on
 *
 * \return Nothing
 */
void ADC0_SetWindowChannel(adc_0_channel_t channel);

/**
 * \brief Start a conversion on ADC0
 *
 * \param[in] channel The ADC channel to start conversion on
 *
 * \return Nothing
 */
void ADC0_StartConversion(adc_0_channel_t channel);

/**
 * \brief Check if the ADC conversion is done
 *
 * \return The status of ADC converison done check
 * \retval true The ADC conversion is done
 * \retval false The ADC converison is not done
 */
bool ADC0_IsConversionDone();

/**
 * \brief Read a conversion result from ADC0
 *
 * \return Conversion result read from the ADC0 ADC module
 */
adc_result_t ADC0_GetConversionResult(void);

/**
 * \brief Read the conversion window result from ADC0
 *
 * \return Returns true when a comparison results in a trigger condition, false otherwise.
 */
bool ADC0_GetWindowResult(void);

/**
 * \brief Start a conversion, wait until ready, and return the conversion result
 *
 * \return Conversion result read from the ADC0 ADC module
 */
adc_result_t ADC0_GetConversion(adc_0_channel_t channel);

/**
 * \brief Return the number of bits in the ADC conversion result
 *
 * \return The number of bits in the ADC conversion result
 */
uint8_t ADC0_GetResolution();

/**
 * \brief Register a callback function to be called if conversion satisfies window criteria.
 *
 * \param[in] f Pointer to function to be called
 *
 * \return Nothing.
 */
void ADC0_RegisterWindowCallback(adc_irq_cb_t f);

#ifdef __cplusplus
}
#endif

#endif /* ADC0_H_INCLUDED */