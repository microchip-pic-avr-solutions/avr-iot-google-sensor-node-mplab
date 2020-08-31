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


#include "../include/spi0.h"
#include "../include/pin_manager.h"

typedef struct spi0_descriptor_s {
    spi0_transfer_status_t status;
} spi0_descriptor_t;

spi0_configuration_t spi0_configurations[] = {
    { 0x23, 0x0 },
    { 0x31, 0x0 }
};

static spi0_descriptor_t spi0_desc;

uint8_t SPI0_Initialize()
{
    //DORD disabled; MASTER enabled; CLK2X disabled; PRESC DIV16; ENABLE enabled; 
    SPI0.CTRLA = 0x23;

    //BUFEN disabled; BUFWR disabled; SSD disabled; MODE 0; 
    SPI0.CTRLB = 0x00;

    //RXCIE disabled; TXCIE disabled; DREIE disabled; SSIE disabled; IE disabled; 
    SPI0.INTCTRL = 0x00;

    spi0_desc.status = SPI0_FREE;

    //RXCIF disabled; IF disabled; TXCIF disabled; WRCOL disabled; DREIF disabled; SSIF disabled; BUFOVF disabled; 
    SPI0.INTFLAGS = 0x00;

    return 0;
}

void SPI0_Enable()
{
    SPI0.CTRLA |= SPI_ENABLE_bm;
}

void SPI0_Disable()
{
    SPI0.CTRLA &= ~SPI_ENABLE_bm;
}

bool SPI0_OpenConfiguration(uint8_t spiUniqueConfiguration){
    return SPI0_Open(spi0_configurations[spiUniqueConfiguration]);
}

bool SPI0_Open(spi0_configuration_t spiUniqueConfiguration)
{
    if (spi0_desc.status == SPI0_FREE) {
        spi0_desc.status = SPI0_IDLE;
        SPI0.CTRLA                = spiUniqueConfiguration.CTRLAvalue;
        SPI0.CTRLB                = spiUniqueConfiguration.CTRLBvalue;
        return true;
    } else {
        return false;
    }
}

void SPI0_Close(void)
{
    spi0_desc.status = SPI0_FREE;
}

uint8_t SPI0_ExchangeByte(uint8_t data)
{
    SPI0.DATA = data;
    while (!(SPI0.INTFLAGS & SPI_RXCIF_bm));
    return SPI0.DATA;
}

bool SPI0_Selected()
{
/**
 * \brief returns true if SS pin is selected 
 * TODO: Place your code
 */
return true;
}

uint8_t SPI0_GetRxData()
{
    return SPI0.DATA;
}

void SPI0_WriteTxData(uint8_t data)
{
    SPI0.DATA = data;
}

void SPI0_WaitDataready()
{
    while (!(SPI0.INTFLAGS & SPI_RXCIF_bm))
        ;
}

void SPI0_ExchangeBlock(void *block, size_t size)
{
    uint8_t *b = (uint8_t *)block;
    while (size--) {
        SPI0.DATA = *b;
        while (!(SPI0.INTFLAGS & SPI_RXCIF_bm))
            ;
        *b = SPI0.DATA;
        b++;
    }
}

void SPI0_WriteBlock(void *block, size_t size)
{
    uint8_t *b = (uint8_t *)block;
    uint8_t  rdata;
    while (size--) {
        SPI0.DATA = *b;
        while (!(SPI0.INTFLAGS & SPI_RXCIF_bm))
            ;
        rdata = SPI0.DATA;
        (void)(rdata); // Silence compiler warning
        b++;
    }
}

void SPI0_ReadBlock(void *block, size_t size)
{
    uint8_t *b = (uint8_t *)block;
    while (size--) {
        SPI0.DATA = 0;
        while (!(SPI0.INTFLAGS & SPI_RXCIF_bm))
            ;
        *b = SPI0.DATA;
        b++;
    }
}

void SPI0_WriteByte(uint8_t data)
{

    SPI0.DATA = data;
}

uint8_t SPI0_ReadByte()
{
    return SPI0.DATA;
}