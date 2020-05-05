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


#ifndef TWI0_MASTER_H
#define TWI0_MASTER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "../utils/compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TWI0_BAUD(F_SCL, T_RISE)    \
    ((((((float)10000000 / (float)F_SCL)) - 10 - ((float)10000000 * T_RISE / 1000000))) / 2)

typedef enum {
    I2C0_NOERR,  // The message was sent.
    I2C0_BUSY,   // Message was NOT sent, bus was busy.
    I2C0_FAIL    // Message was NOT sent, bus failure
                // If you are interested in the failure reason,
                // Sit on the event call-backs.
} twi0_error_t;

typedef enum { I2C0_STOP = 1, I2C0_RESTART_READ, I2C0_RESTART_WRITE, I2C0_CONTINUE, I2C0_RESET_LINK } twi0_operations_t;

typedef twi0_operations_t (*twi0_callback_t)(void *funPtr);

typedef uint8_t twi0_address_t;
//typedef twi0_address_t i2c_address_t;
// common callback responses
twi0_operations_t I2C0_SetReturnStopCallback(void *funPtr);
twi0_operations_t I2C0_SetReturnResetCallback(void *funPtr);
twi0_operations_t I2C0_SetRestartWriteCallback(void *funPtr);
twi0_operations_t I2C0_SetRestartReadCallback(void *funPtr);

/**
 * \brief Initialize I2C interface
 * If module is configured to disabled state, the clock to the I2C is disabled
 * if this is supported by the device's clock system.
 *
 * \return Initialization status.
 * \retval 0 the init was successful
 * \retval 1 the init was not successful
 */
uint8_t I2C0_Initialize(void);

/**
 * \brief Open the I2C for communication
 *
 * \param[in] address The slave address to use in the transfer
 *
 * \return Initialization status.
 * \retval I2C_NOERR The I2C open was successful
 * \retval I2C_BUSY  The I2C open failed because the interface is busy
 * \retval I2C_FAIL  The I2C open failed with an error
 */
twi0_error_t I2C0_Open(twi0_address_t address);

/**
 * \brief Close the I2C interface
 *
 * \return Status of close operation.
 * \retval I2C_NOERR The I2C open was successful
 * \retval I2C_BUSY  The I2C open failed because the interface is busy
 * \retval I2C_FAIL  The I2C open failed with an error
 */
twi0_error_t I2C0_Close(void);

/**
 * \brief Start an operation on an opened I2C interface
 *
 * \param[in] read Set to true for read, false for write
 *
 * \return Status of operation
 * \retval I2C_NOERR The I2C open was successful
 * \retval I2C_BUSY  The I2C open failed because the interface is busy
 * \retval I2C_FAIL  The I2C open failed with an error
 */
twi0_error_t I2C0_MasterOperation(bool read);

/**
 * \brief Identical to I2C0_MasterOperation(false);
 */
twi0_error_t I2C0_MasterWrite(void); // to be depreciated

/**
 * \brief Identical to I2C0_MasterOperation(true);
 */
twi0_error_t I2C0_MasterRead(void); // to be depreciated

/**
 * \brief Set timeout to be used for I2C operations. Uses the Timeout driver.
 *
 * \param[in] to Timeout in ticks
 *
 * \return Nothing
 */
void I2C0_SetTimeout(uint8_t to);

/**
 * \brief Sets up the data buffer to use, and number of bytes to transfer
 *
 * \param[in] buffer Pointer to data buffer to use for read or write data
 * \param[in] bufferSize Number of bytes to read or write from slave
 *
 * \return Nothing
 */
void I2C0_SetBuffer(void *buffer, size_t bufferSize);

// Event Callback functions.

/**
 * \brief Set callback to be called when all specifed data has been transferred.
 *
 * \param[in] cb Pointer to callback function
 * \param[in] p  Pointer to the callback function's parameters
 *
 * \return Nothing
 */
void I2C0_SetDataCompleteCallback(twi0_callback_t cb, void *funPtr);

/**
 * \brief Set callback to be called when there has been a bus collision and arbitration was lost.
 *
 * \param[in] cb Pointer to callback function
 * \param[in] p  Pointer to the callback function's parameters
 *
 * \return Nothing
 */
void I2C0_SetWriteCollisionCallback(twi0_callback_t cb, void *funPtr);

/**
 * \brief Set callback to be called when the transmitted address was NACK'ed.
 *
 * \param[in] cb Pointer to callback function
 * \param[in] p  Pointer to the callback function's parameters
 *
 * \return Nothing
 */
void I2C0_SetAddressNackCallback(twi0_callback_t cb, void *funPtr);

/**
 * \brief Set callback to be called when the transmitted data was NACK'ed.
 *
 * \param[in] cb Pointer to callback function
 * \param[in] p  Pointer to the callback function's parameters
 *
 * \return Nothing
 */
void I2C0_SetDataNackCallback(twi0_callback_t cb, void *funPtr);

/**
 * \brief Set callback to be called when there was a bus timeout.
 *
 * \param[in] cb Pointer to callback function
 * \param[in] p  Pointer to the callback function's parameters
 *
 * \return Nothing
 */
void I2C0_SetTimeoutCallback(twi0_callback_t cb, void *funPtr);

/**
 * \brief Set Address to be called when there was aa address reception.
 *
 * \param[in] address Loads the address of the master
 *
 * \return Nothing
 */
void I2C0_SetAddress(twi0_address_t address);

#ifdef __cplusplus
}
#endif

#endif /* TWI0_MASTER_H */