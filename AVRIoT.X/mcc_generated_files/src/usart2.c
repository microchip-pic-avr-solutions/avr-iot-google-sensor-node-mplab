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


#include "../include/usart2.h"

#if defined(__GNUC__)

int USART2_printCHAR(char character, FILE *stream)
{
    USART2_Write(character);
    return 0;
}

FILE USART2_stream = FDEV_SETUP_STREAM(USART2_printCHAR, NULL, _FDEV_SETUP_WRITE);

#elif defined(__ICCAVR__)

int putchar(int outChar)
{
    USART2_Write(outChar);
    return outChar;
}
#endif

/* Static Variables holding the ringbuffer used in IRQ mode */
static uint8_t          USART2_rxbuf[USART2_RX_BUFFER_SIZE];
static volatile uint8_t USART2_rx_head;
static volatile uint8_t USART2_rx_tail;
static volatile uint8_t USART2_rx_elements;
static uint8_t          USART2_txbuf[USART2_TX_BUFFER_SIZE];
static volatile uint8_t USART2_tx_head;
static volatile uint8_t USART2_tx_tail;
static volatile uint8_t USART2_tx_elements;

void (*USART2_rx_isr_cb)(void) = &USART2_DefaultRxIsrCb;

void (*USART2_tx_isr_cb)(void) = &USART2_DefaultTxIsrCb;

void USART2_DefaultRxIsrCb(void)
{
    uint8_t data;
    uint8_t tmphead;

    /* Read the received data */
    data = USART2.RXDATAL;
    /* Calculate buffer index */
    tmphead = (USART2_rx_head + 1) & USART2_RX_BUFFER_MASK;
        
    if (tmphead == USART2_rx_tail) {
            /* ERROR! Receive buffer overflow */
    }else {
    /*Store new index*/
    USART2_rx_head = tmphead;
    
    /* Store received data in buffer */
    USART2_rxbuf[tmphead] = data;
    USART2_rx_elements++;
    }
}

void USART2_DefaultTxIsrCb(void)
{
    uint8_t tmptail;

    /* Check if all data is transmitted */
    if (USART2_tx_elements != 0) {
        /* Calculate buffer index */
        tmptail = (USART2_tx_tail + 1) & USART2_TX_BUFFER_MASK;
        /* Store new index */
        USART2_tx_tail = tmptail;
        /* Start transmission */
        USART2.TXDATAL = USART2_txbuf[tmptail];
        
        USART2_tx_elements--;
    }

    if (USART2_tx_elements == 0) {
            /* Disable Tx interrupt */
            USART2.CTRLA &= ~(1 << USART_DREIE_bp);
    }
}

void USART2_SetISRCb(usart_callback cb, usart2_cb_t type)
{
    switch (type) {
        case USART2_RX_CB:
                USART2_rx_isr_cb = cb;
                break;
        case USART2_TX_CB:
                USART2_tx_isr_cb = cb;
                break;
        default:
                // do nothing
                break;
    }
}

void USART2_SetRXISRCb(usart_callback cb)
{
    USART2_SetISRCb(cb,USART2_RX_CB);
}

void USART2_SetTXISRCb(usart_callback cb)
{
    USART2_SetISRCb(cb,USART2_TX_CB);
}

/* Interrupt service routine for RX complete */
ISR(USART2_RXC_vect)
{
    if (USART2_rx_isr_cb != NULL)
    {
        (*USART2_rx_isr_cb)();
    }
}

/* Interrupt service routine for Data Register Empty */
ISR(USART2_DRE_vect)
{
    if (USART2_tx_isr_cb != NULL)
    {
        (*USART2_tx_isr_cb)();
    }
}

ISR(USART2_TXC_vect)
{
    USART2.STATUS |= USART_TXCIF_bm;
}

bool USART2_IsTxReady()
{
    return (USART2_tx_elements != USART2_TX_BUFFER_SIZE);
}

bool USART2_IsRxReady()
{
    return (USART2_rx_elements != 0);
}

bool USART2_IsTxBusy()
{
    return (!(USART2.STATUS & USART_TXCIF_bm));
}

bool USART2_IsTxDone()
{
    return (USART2.STATUS & USART_TXCIF_bm);
}

uint8_t USART2_Read(void)
{
    uint8_t tmptail;

    /* Wait for incoming data */
    while (USART2_rx_elements == 0)
            ;
    /* Calculate buffer index */
    tmptail = (USART2_rx_tail + 1) & USART2_RX_BUFFER_MASK;
    /* Store new index */
    USART2_rx_tail = tmptail;
    ENTER_CRITICAL(R);
    USART2_rx_elements--;
    EXIT_CRITICAL(R);

    /* Return data */
    return USART2_rxbuf[tmptail];
}

void USART2_Write(const uint8_t data)
{
    uint8_t tmphead;

    /* Calculate buffer index */
    tmphead = (USART2_tx_head + 1) & USART2_TX_BUFFER_MASK;
    /* Wait for free space in buffer */
    while (USART2_tx_elements == USART2_TX_BUFFER_SIZE)
            ;
    /* Store data in buffer */
    USART2_txbuf[tmphead] = data;
    /* Store new index */
    USART2_tx_head = tmphead;
    ENTER_CRITICAL(W);
    USART2_tx_elements++;
    EXIT_CRITICAL(W);
    /* Enable Tx interrupt */
    USART2.CTRLA |= (1 << USART_DREIE_bp);
}

void USART2_Initialize()
{
    //set baud rate register
    USART2.BAUD = (uint16_t)USART2_BAUD_RATE(9600);
	
    //RXCIE enabled; TXCIE enabled; DREIE disabled; RXSIE enabled; LBME disabled; ABEIE disabled; RS485 OFF; 
    USART2.CTRLA = 0xD0;
	
    //RXEN enabled; TXEN enabled; SFDEN disabled; ODME disabled; RXMODE NORMAL; MPCM disabled; 
    USART2.CTRLB = 0xC0;
	
    //CMODE ASYNCHRONOUS; PMODE DISABLED; SBMODE 1BIT; CHSIZE 8BIT; UDORD disabled; UCPHA disabled; 
    USART2.CTRLC = 0x03;
	
    //DBGCTRL_DBGRUN
    USART2.DBGCTRL = 0x00;
	
    //EVCTRL_IREI
    USART2.EVCTRL = 0x00;
	
    //RXPLCTRL_RXPL
    USART2.RXPLCTRL = 0x00;
	
    //TXPLCTRL_TXPL
    USART2.TXPLCTRL = 0x00;
	

    uint8_t x;

    /* Initialize ringbuffers */
    x = 0;

    USART2_rx_tail     = x;
    USART2_rx_head     = x;
    USART2_rx_elements = x;
    USART2_tx_tail     = x;
    USART2_tx_head     = x;
    USART2_tx_elements = x;

#if defined(__GNUC__)
    stdout = &USART2_stream;
#endif

}

void USART2_Enable()
{
    USART2.CTRLB |= USART_RXEN_bm | USART_TXEN_bm;
}

void USART2_EnableRx()
{
    USART2.CTRLB |= USART_RXEN_bm;
}

void USART2_EnableTx()
{
    USART2.CTRLB |= USART_TXEN_bm;
}

void USART2_Disable()
{
    USART2.CTRLB &= ~(USART_RXEN_bm | USART_TXEN_bm);
}

uint8_t USART2_GetData()
{
    return USART2.RXDATAL;
}