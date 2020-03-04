/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/*
 This file provides some basic blocking helper functions for common operations on the i2c API
 */

#include "../include/twi0_master.h"
#include "i2c_simple_master.h"

/****************************************************************/
static twi0_operations_t wr1RegCompleteHandler(void *p)
{
    I2C0_SetBuffer(p,1);
    I2C0_SetDataCompleteCallback(NULL,NULL);
    return I2C_CONTINUE;
}

void i2c_write1ByteRegister(twi0_address_t address, uint8_t reg, uint8_t data)
{
    while(!I2C0_Open(address)); // sit here until we get the bus..
    I2C0_SetDataCompleteCallback(wr1RegCompleteHandler,&data);
    I2C0_SetBuffer(&reg,1);
    I2C0_SetAddressNackCallback(I2C0_SetRestartWriteCallback,NULL); //NACK polling?
    I2C0_MasterWrite();
    while(I2C_BUSY == I2C0_Close()); // sit here until finished.
}

void i2c_writeNBytes(twi0_address_t address, void* data, size_t len)
{
    while(!I2C0_Open(address)); // sit here until we get the bus..
    I2C0_SetBuffer(data,len);
    I2C0_SetAddressNackCallback(I2C0_SetRestartWriteCallback,NULL); //NACK polling?
    I2C0_MasterWrite();
    while(I2C_BUSY == I2C0_Close()); // sit here until finished.
}

/****************************************************************/
static twi0_operations_t rd1RegCompleteHandler(void *p)
{
    I2C0_SetBuffer(p,1);
    I2C0_SetDataCompleteCallback(NULL,NULL);
    return I2C_RESTART_READ;
}

uint8_t i2c_read1ByteRegister(twi0_address_t address, uint8_t reg)
{
    uint8_t    d2=42;
    twi0_error_t e;
    int x;

    for(x = 2; x != 0; x--)
    {
        while(!I2C0_Open(address)); // sit here until we get the bus..
        I2C0_SetDataCompleteCallback(rd1RegCompleteHandler,&d2);
        I2C0_SetBuffer(&reg,1);
        I2C0_SetAddressNackCallback(I2C0_SetRestartWriteCallback,NULL); //NACK polling?
        I2C0_MasterWrite();
        while(I2C_BUSY == (e = I2C0_Close())); // sit here until finished.
        if(e==I2C_NOERR) break;
    }
    

    return d2;
}

/****************************************************************/
static twi0_operations_t rd2RegCompleteHandler(void *p)
{
    I2C0_SetBuffer(p,2);
    I2C0_SetDataCompleteCallback(NULL,NULL);
    return I2C_RESTART_READ;
}

uint16_t i2c_read2ByteRegister(twi0_address_t address, uint8_t reg)
{
    // result is little endian
    uint16_t    result;

    while(!I2C0_Open(address)); // sit here until we get the bus..
    I2C0_SetDataCompleteCallback(rd2RegCompleteHandler,&result);
    I2C0_SetBuffer(&reg,1);
    I2C0_SetAddressNackCallback(I2C0_SetRestartWriteCallback,NULL); //NACK polling?
    I2C0_MasterWrite();
    while(I2C_BUSY == I2C0_Close()); // sit here until finished.
    
    return (result << 8 | result >> 8);
}

/****************************************************************/
static twi0_operations_t wr2RegCompleteHandler(void *p)
{
    I2C0_SetBuffer(p,2);
    I2C0_SetDataCompleteCallback(NULL,NULL);
    return I2C_CONTINUE;
}

void i2c_write2ByteRegister(twi0_address_t address, uint8_t reg, uint16_t data)
{
    while(!I2C0_Open(address)); // sit here until we get the bus..
    I2C0_SetDataCompleteCallback(wr2RegCompleteHandler,&data);
    I2C0_SetBuffer(&reg,1);
    I2C0_SetAddressNackCallback(I2C0_SetRestartWriteCallback,NULL); //NACK polling?
    I2C0_MasterWrite();
    while(I2C_BUSY == I2C0_Close()); // sit here until finished.
}

/****************************************************************/
typedef struct
{
    size_t len;
    char *data;
}buf_t;

static twi0_operations_t rdBlkRegCompleteHandler(void *p)
{
    I2C0_SetBuffer(((buf_t *)p)->data,((buf_t*)p)->len);
    I2C0_SetDataCompleteCallback(NULL,NULL);
    return I2C_RESTART_READ;
}

void i2c_readDataBlock(twi0_address_t address, uint8_t reg, void *data, size_t len)
{
    // result is little endian
    buf_t    d;
    d.data = data;
    d.len = len;

    while(!I2C0_Open(address)); // sit here until we get the bus..
    I2C0_SetDataCompleteCallback(rdBlkRegCompleteHandler,&d);
    I2C0_SetBuffer(&reg,1);
    I2C0_SetAddressNackCallback(I2C0_SetRestartWriteCallback,NULL); //NACK polling?
    I2C0_MasterWrite();
    while(I2C_BUSY == I2C0_Close()); // sit here until finished.
}

void i2c_readNBytes(twi0_address_t address, void *data, size_t len)
{
    while(!I2C0_Open(address)); // sit here until we get the bus..
    I2C0_SetBuffer(data,len);
    I2C0_MasterRead();
    while(I2C_BUSY == I2C0_Close()); // sit here until finished.
}