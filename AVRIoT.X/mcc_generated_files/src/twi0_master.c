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

#include "../include/twi0_master.h"
#include <stdbool.h>
#include <stdlib.h>

/***************************************************************************/
// I2C STATES
typedef enum {
    I2C_IDLE = 0,
    I2C_SEND_ADR_READ,
    I2C_SEND_ADR_WRITE,
    I2C_TX,
    I2C_RX,
    I2C_TX_EMPTY,
    I2C_SEND_RESTART_READ,
    I2C_SEND_RESTART_WRITE,
    I2C_SEND_RESTART,
    I2C_SEND_STOP,
    I2C_RX_DO_ACK,
    I2C_TX_DO_ACK,
    I2C_RX_DO_NACK_STOP,
    I2C_RX_DO_NACK_RESTART,
    I2C_RESET,
    I2C_ADDRESS_NACK,
    I2C_BUS_COLLISION,
    I2C_BUS_ERROR
} twi0_fsm_states_t;

// I2C Event Callback List
typedef enum {
    I2C_DATA_COMPLETE = 0,
    I2C_WRITE_COLLISION,
    I2C_ADDRESSNACK,
    I2C_DATA_NACK,
    I2C_TIMEOUT,
    I2C_NULL
} I2C0_callbackIndex_t;

// I2C Status Structure
typedef struct {
    twi0_callback_t callbackTable[6];
    void *       callbackPayload[6];
    uint16_t         timeout;
    uint16_t         timeout_value;
    twi0_address_t    address;
    uint8_t *        data_ptr;
    size_t           data_length;
    twi0_fsm_states_t state;
    twi0_error_t      error;
    unsigned         addressNACKCheck : 1;
    unsigned         busy : 1;
    unsigned         inUse : 1;
    unsigned         bufferFree : 1;
    /*if timeoutDriverEnabled
    timerStruct_t timeout;
    */
} I2C0_status_t;
I2C0_status_t I2C0_status = {0};
typedef twi0_fsm_states_t(stateHandlerFunction)(void);

/* I2C Interfaces */
void I2C0_Poller(void);

/* I2C Internal API's */
/* Master */
void I2C0_MasterOpen(void);
void I2C0_MasterClose(void);
char I2C0_MasterGetRxData(void);
void I2C0_MasterTxData(char d);
void I2C0_MasterTxAddr(char d);
void I2C0_MasterResetBus(void);
void I2C0_MasterIsRxOrTx(void);
void I2C0_MasterStop(void);
bool I2C0_MasterIsNack(void);
void I2C0_MasterSendAck(void);
void I2C0_MasterSendNack(void);
void I2C0_MasterClearBusCollision(void);
bool I2C0_MasterBusErrorOverride();
bool I2C0_MasterArbitrationlostOverride(void);
void I2C0_MasterEnableIrq(void);
bool I2C0_MasterIsIrqEnabled(void);
void I2C0_MasterDisableIrq(void);
void I2C0_MasterClearIrq(void);
void I2C0_MasterWaitForEvent(void);
static void I2C0_set_callback(I2C0_callbackIndex_t idx, twi0_callback_t cb, void *funPtr);
static twi0_operations_t I2C0_RETURN_STOP(void *funPtr);
static twi0_operations_t I2C0_RETURN_RESET(void *funPtr);
static void I2C0_MasterIsr(void);

/* Helper Functions */
static twi0_fsm_states_t I2C0_DO_IDLE(void);
static twi0_fsm_states_t I2C0_DO_SEND_ADR_READ(void);
static twi0_fsm_states_t I2C0_DO_SEND_ADR_WRITE(void);
static twi0_fsm_states_t I2C0_DO_TX(void);
static twi0_fsm_states_t I2C0_DO_RX(void);
static twi0_fsm_states_t I2C0_DO_TX_EMPTY(void);
static twi0_fsm_states_t I2C0_DO_SEND_RESTART_READ(void);
static twi0_fsm_states_t I2C0_DO_SEND_RESTART_WRITE(void);
static twi0_fsm_states_t I2C0_DO_SEND_RESTART(void);
static twi0_fsm_states_t I2C0_DO_SEND_STOP(void);
static twi0_fsm_states_t I2C0_DO_RX_ACK(void);
static twi0_fsm_states_t I2C0_DO_TX_ACK(void);
static twi0_fsm_states_t I2C0_DO_RX_NACK_STOP(void);
static twi0_fsm_states_t I2C0_DO_RX_NACK_RESTART(void);
static twi0_fsm_states_t I2C0_DO_RESET(void);
static twi0_fsm_states_t I2C0_DO_ADDRESS_NACK(void);
static twi0_fsm_states_t I2C0_DO_BUS_COLLISION(void);
static twi0_fsm_states_t I2C0_DO_BUS_ERROR(void);

typedef twi0_fsm_states_t(stateHandlerFunction)(void);
stateHandlerFunction *I2C0_fsmStateTable[] = {
    I2C0_DO_IDLE,               // I2C_IDLE
    I2C0_DO_SEND_ADR_READ,      // I2C_SEND_ADR_READ
    I2C0_DO_SEND_ADR_WRITE,     // I2C_SEND_ADR_WRITE
    I2C0_DO_TX,                 // I2C_TX
    I2C0_DO_RX,                 // I2C_RX
    I2C0_DO_TX_EMPTY,           // I2C_TX_EMPTY
    I2C0_DO_SEND_RESTART_READ,  // I2C_SEND_RESTART_READ
    I2C0_DO_SEND_RESTART_WRITE, // I2C_SEND_RESTART_WRITE
    I2C0_DO_SEND_RESTART,       // I2C_SEND_RESTART
    I2C0_DO_SEND_STOP,          // I2C_SEND_STOP
    I2C0_DO_RX_ACK,          // I2C_RX_DO_ACK
    I2C0_DO_TX_ACK,          // I2C_TX_DO_ACK
    I2C0_DO_RX_NACK_STOP,       // I2C_RX_DO_NACK_STOP
    I2C0_DO_RX_NACK_RESTART,    // I2C_RX_DO_NACK_RESTART
    I2C0_DO_RESET,              // I2C_RESET
    I2C0_DO_ADDRESS_NACK,    // I2C_ADDRESS_NACK
    I2C0_DO_BUS_COLLISION,      // I2C_BUS_COLLISION
    I2C0_DO_BUS_ERROR           // I2C_BUS_ERROR
};

void I2C0_SetDataCompleteCallback(twi0_callback_t cb, void *funPtr)
{
    I2C0_set_callback(I2C_DATA_COMPLETE, cb, funPtr);
}

void I2C0_SetWriteCollisionCallback(twi0_callback_t cb, void *funPtr)
{
    I2C0_set_callback(I2C_WRITE_COLLISION, cb, funPtr);
}

void I2C0_SetAddressNackCallback(twi0_callback_t cb, void *funPtr)
{
    I2C0_set_callback(I2C_ADDRESSNACK, cb, funPtr);
}

void I2C0_SetDataNackCallback(twi0_callback_t cb, void *funPtr)
{
    I2C0_set_callback(I2C_DATA_NACK, cb, funPtr);
}

void I2C0_SetTimeoutCallback(twi0_callback_t cb, void *funPtr)
{
    I2C0_set_callback(I2C_TIMEOUT, cb, funPtr);
}

uint8_t I2C0_Initialize()
{
    //SDASETUP 4CYC; SDAHOLD OFF; FMPEN disabled; 
    TWI0.CTRLA = 0x00;
    
    //Debug Run
    TWI0.DBGCTRL = 0x00;
    
    //Master Baud Rate Control
    TWI0.MBAUD = (uint8_t)TWI0_BAUD(100000, 0);
    
    //RIEN disabled; WIEN disabled; QCEN disabled; TIMEOUT DISABLED; SMEN disabled; ENABLE enabled; 
    TWI0.MCTRLA = 0x01;
    
    //RIF disabled; WIF disabled; CLKHOLD disabled; ARBLOST disabled; BUSERR disabled; BUSSTATE UNKNOWN; 
    TWI0.MSTATUS = 0x00;
    
    //Master Address
    TWI0.MADDR = 0x00;
    
    //FLUSH disabled; ACKACT ACK; MCMD NOACT; 
    TWI0.MCTRLB = 0x00;
    
    //Master Data
    TWI0.MDATA = 0x00;
    
    return 0;
}

// when you call open, you supply a device address.
// if you get the bus, the function returns true
twi0_error_t I2C0_Open(twi0_address_t address)
{
    twi0_error_t ret = I2C_BUSY;

    if (!I2C0_status.inUse) {
        I2C0_status.address          = address;
        I2C0_status.busy             = 0;
        I2C0_status.inUse            = 1;
        I2C0_status.addressNACKCheck = 0;
        I2C0_status.state            = I2C_RESET;
        I2C0_status.timeout_value    = 500; // MCC should determine a reasonable starting value here.
        I2C0_status.bufferFree       = 1;
        
        // set all the call backs to a default of sending stop
        I2C0_status.callbackTable[I2C_DATA_COMPLETE]     = I2C0_RETURN_STOP;
        I2C0_status.callbackPayload[I2C_DATA_COMPLETE]   = NULL;
        I2C0_status.callbackTable[I2C_WRITE_COLLISION]   = I2C0_RETURN_STOP;
        I2C0_status.callbackPayload[I2C_WRITE_COLLISION] = NULL;
        I2C0_status.callbackTable[I2C_ADDRESSNACK]      = I2C0_RETURN_STOP;
        I2C0_status.callbackPayload[I2C_ADDRESSNACK]    = NULL;
        I2C0_status.callbackTable[I2C_DATA_NACK]         = I2C0_RETURN_STOP;
        I2C0_status.callbackPayload[I2C_DATA_NACK]       = NULL;
        I2C0_status.callbackTable[I2C_TIMEOUT]          = I2C0_RETURN_RESET;
        I2C0_status.callbackPayload[I2C_TIMEOUT]        = NULL;

        I2C0_MasterResetBus();
        // Reset module
        I2C0_MasterClearIrq();

        ret = I2C_NOERR;
    }
    return ret;
}

void I2C0_SetAddress(twi0_address_t address)
{
    I2C0_status.address = address;
}

// close the bus if it is not busy
twi0_error_t I2C0_Close(void)
{
    twi0_error_t ret = I2C_BUSY;
    // Bus is in error state, reset I2C hardware and report error
    if (I2C0_MasterBusErrorOverride()) {
        I2C0_status.busy  = false;
        I2C0_status.error = I2C_FAIL;
    }
    if (!I2C0_status.busy) {
        I2C0_status.inUse = 0;
        // close it down
        I2C0_status.address = 0xff; // 8-bit address is invalid so this is FREE
        I2C0_MasterClearIrq();
        I2C0_MasterDisableIrq();
        ret = I2C0_status.error;
    }
    return ret;
}

void I2C0_SetTimeout(uint8_t to)
{
    I2C0_MasterDisableIrq();
    I2C0_status.timeout_value = to;
    I2C0_MasterEnableIrq();
}

void I2C0_SetBuffer(void *buffer, size_t bufferSize)
{
    if (I2C0_status.bufferFree) {
        I2C0_status.data_ptr    = buffer;
        I2C0_status.data_length = bufferSize;
        I2C0_status.bufferFree  = false;
    }
}
twi0_error_t I2C0_MasterOperation(bool read)
{
    twi0_error_t ret = I2C_BUSY;
    if (!I2C0_status.busy) {
        I2C0_status.busy = true;
        ret                       = I2C_NOERR;

        if (read) {
            I2C0_status.state = I2C_SEND_ADR_READ;
        } else {
            I2C0_status.state = I2C_SEND_ADR_WRITE;
        }
        I2C0_MasterIsr();

        I2C0_Poller();
    }
    return ret;
}

twi0_error_t I2C0_MasterRead(void)

{
    return I2C0_MasterOperation(true);
}



twi0_error_t I2C0_MasterWrite(void)
{
    return I2C0_MasterOperation(false);
}

/************************************************************************/
/* Helper Functions                                                     */
/************************************************************************/

void I2C0_Poller(void)
{
    while (I2C0_status.busy)
    {
        I2C0_MasterWaitForEvent();
        I2C0_MasterIsr();
    }
}

static twi0_fsm_states_t I2C0_DO_RESET(void)
{
    I2C0_MasterResetBus();
    I2C0_status.busy  = false; // Bus Free
    I2C0_status.error = I2C_NOERR;
    return I2C_RESET; // park the FSM on reset
}

static twi0_fsm_states_t I2C0_DO_IDLE(void)
{
    I2C0_status.busy  = false; // Bus Free
    I2C0_status.error = I2C_NOERR;
    return I2C_IDLE; // park the FSM on IDLE
}

static twi0_fsm_states_t I2C0_DO_SEND_RESTART_READ(void)
{
    return I2C0_DO_SEND_ADR_READ();
}

static twi0_fsm_states_t I2C0_DO_SEND_RESTART_WRITE(void)
{
    return I2C0_DO_SEND_ADR_WRITE();
}

static twi0_fsm_states_t I2C0_DO_SEND_RESTART(void)
{
    return I2C0_DO_SEND_ADR_READ();
}

static twi0_fsm_states_t I2C0_DO_SEND_STOP(void)
{
    I2C0_MasterStop();
    return I2C0_DO_IDLE();
}

// TODO: probably need 2 addressNACK's one from read and one from write.
//       the do NACK before RESTART or STOP is a special case that a new state simplifies.
static twi0_fsm_states_t I2C0_DO_ADDRESS_NACK(void)
{
    I2C0_status.addressNACKCheck = 0;
    I2C0_status.error            = I2C_FAIL;
    switch (I2C0_status.callbackTable[I2C_ADDRESSNACK](I2C0_status.callbackPayload[I2C_ADDRESSNACK])) {
    case I2C_RESTART_READ:
        return I2C0_DO_SEND_RESTART_READ();
    case I2C_RESTART_WRITE:
        return I2C0_DO_SEND_RESTART_WRITE();
    default:
        return I2C0_DO_SEND_STOP();
    }
}

static twi0_fsm_states_t I2C0_DO_SEND_ADR_READ(void)
{

    I2C0_status.addressNACKCheck = 1;
    I2C0_MasterTxAddr(I2C0_status.address << 1 | 1);
    return I2C_RX;
}

static twi0_fsm_states_t I2C0_DO_SEND_ADR_WRITE(void)
{

    I2C0_status.addressNACKCheck = 1;
    I2C0_MasterTxAddr(I2C0_status.address << 1);
    return I2C_TX;
}

static twi0_fsm_states_t I2C0_DO_RX_ACK(void)
{
    I2C0_MasterSendAck();
    return I2C_RX;
}

static twi0_fsm_states_t I2C0_DO_TX_ACK(void)
{
    I2C0_MasterSendAck();
    return I2C_TX;
}

static twi0_fsm_states_t I2C0_DO_RX_NACK_STOP(void)
{
    I2C0_MasterSendNack();
    I2C0_MasterStop();
    return I2C0_DO_IDLE();
}

static twi0_fsm_states_t I2C0_DO_RX_NACK_RESTART(void)
{
    I2C0_MasterSendNack();
    return I2C_SEND_RESTART;
}

static twi0_fsm_states_t I2C0_DO_TX(void)
{
    if (I2C0_MasterIsNack()) // Slave replied with NACK
    {
        switch (I2C0_status.callbackTable[I2C_DATA_NACK](I2C0_status.callbackPayload[I2C_DATA_NACK])) {
        case I2C_RESTART_READ:
            return I2C0_DO_SEND_RESTART_READ();
        case I2C_RESTART_WRITE:
            return I2C0_DO_SEND_RESTART_WRITE();
        default:
        case I2C_CONTINUE:
        case I2C_STOP:
            return I2C0_DO_SEND_STOP();
        }
    } else {
        I2C0_status.addressNACKCheck = 0;
        I2C0_MasterTxData(*I2C0_status.data_ptr++);
        return (--I2C0_status.data_length) ? I2C_TX : I2C_TX_EMPTY;
    }
}

static twi0_fsm_states_t I2C0_DO_RX(void)
{
    I2C0_status.addressNACKCheck = 0;

    if (I2C0_status.data_length == 1)
        I2C0_MasterSendNack(); // Next byte will be last to be received, setup NACK
    else
        I2C0_MasterSendAck(); // More bytes to receive, setup ACK

    if (--I2C0_status.data_length) {
        *I2C0_status.data_ptr = I2C0_MasterGetRxData();
        I2C0_status.data_ptr++;
        I2C0_MasterIsRxOrTx();
        return I2C_RX;
    } else {
        *I2C0_status.data_ptr = I2C0_MasterGetRxData();
        I2C0_status.data_ptr++;
        I2C0_status.bufferFree = true;
        switch (I2C0_status.callbackTable[I2C_DATA_COMPLETE](I2C0_status.callbackPayload[I2C_DATA_COMPLETE])) {
        case I2C_RESTART_WRITE:
        case I2C_RESTART_READ:
            return I2C0_DO_RX_NACK_RESTART();
        default:
        case I2C_CONTINUE:
        case I2C_STOP:
            return I2C0_DO_RX_NACK_STOP();
        }
    }
}

static twi0_fsm_states_t I2C0_DO_TX_EMPTY(void)
{
    if (I2C0_MasterIsNack()) // Slave replied with NACK
    {
        switch (I2C0_status.callbackTable[I2C_DATA_NACK](I2C0_status.callbackPayload[I2C_DATA_NACK])) {
        case I2C_RESTART_READ:
            return I2C0_DO_SEND_RESTART_READ();
        case I2C_RESTART_WRITE:
            return I2C0_DO_SEND_RESTART_WRITE();
        default:
        case I2C_CONTINUE:
        case I2C_STOP:
            return I2C0_DO_SEND_STOP();
        }
    } else {
        I2C0_status.bufferFree = true;
        switch (I2C0_status.callbackTable[I2C_DATA_COMPLETE](I2C0_status.callbackPayload[I2C_DATA_COMPLETE])) {
        case I2C_RESTART_READ:
            return I2C0_DO_SEND_RESTART_READ();
        case I2C_RESTART_WRITE:
            return I2C0_DO_SEND_RESTART_WRITE();
        case I2C_CONTINUE:
            return I2C0_DO_TX();
        default:
        case I2C_STOP:
            return I2C0_DO_SEND_STOP();
        }
    }
}

static twi0_fsm_states_t I2C0_DO_BUS_COLLISION(void)
{
    // Clear bus collision status flag
    I2C0_MasterClearBusCollision();

    I2C0_status.error = I2C_FAIL;
    switch (I2C0_status.callbackTable[I2C_WRITE_COLLISION](I2C0_status.callbackPayload[I2C_WRITE_COLLISION])) {
    case I2C_RESTART_READ:
        return I2C0_DO_SEND_RESTART_READ();
    case I2C_RESTART_WRITE:
        return I2C0_DO_SEND_RESTART_WRITE();
    default:
        return I2C0_DO_RESET();
    }
}

static twi0_fsm_states_t I2C0_DO_BUS_ERROR(void)
{
    I2C0_MasterResetBus();
    I2C0_status.busy  = false;
    I2C0_status.error = I2C_FAIL;
    return I2C_RESET; // park the FSM on reset
}



void I2C0_MasterIsr(void)
{
    I2C0_MasterClearIrq();

    // NOTE: We are ignoring the Write Collision flag.

    // Address phase received NACK from slave, override next state
    if (I2C0_status.addressNACKCheck && I2C0_MasterIsNack()) {
        I2C0_status.state = I2C_ADDRESS_NACK; // State Override
    }

    // Bus arbitration lost to another master, override next state
    if (I2C0_MasterArbitrationlostOverride()) {
        I2C0_status.state = I2C_BUS_COLLISION; // State Override
    }

    // Bus error, override next state
    if (I2C0_MasterBusErrorOverride()) {
        I2C0_status.state = I2C_BUS_ERROR; // State Override
    }

    I2C0_status.state = I2C0_fsmStateTable[I2C0_status.state]();
}

/************************************************************************/
/* Helper Functions                                                     */
/************************************************************************/
static twi0_operations_t I2C0_RETURN_STOP(void *p)
{
    return I2C_STOP;
}

static twi0_operations_t I2C0_RETURN_RESET(void *p)
{
    return I2C_RESET_LINK;
}

static void I2C0_set_callback(I2C0_callbackIndex_t idx, twi0_callback_t cb, void *funPtr)
{
    if (cb) {
        I2C0_status.callbackTable[idx]   = cb;
        I2C0_status.callbackPayload[idx] = funPtr;
    } else {
        I2C0_status.callbackTable[idx]   = I2C0_RETURN_STOP;
        I2C0_status.callbackPayload[idx] = NULL;
    }
}

/* Master Definitions */

void I2C0_MasterOpen(void)
{
    TWI0.MCTRLA = 1 << TWI_ENABLE_bp;
}

void I2C0_MasterClose(void)
{
    TWI0.MCTRLA = 0 << TWI_ENABLE_bp;
}

/* Interrupt Control */
void I2C0_MasterEnableIrq(void)
{
    TWI0.MCTRLA |= (TWI_RIEN_bm | TWI_WIEN_bm);
}

bool I2C0_MasterIsIrqEnabled(void)
{
    return ((TWI0.MCTRLA & TWI_WIEN_bm) && (TWI0.MCTRLA & TWI_RIEN_bm));
}

void I2C0_MasterDisableIrq(void)
{
    TWI0.MCTRLA &= ~(TWI_RIEN_bm | TWI_WIEN_bm);
}

void I2C0_MasterClearIrq(void)
{
    TWI0.MSTATUS |= (TWI_RIF_bm | TWI_WIF_bm);
}

bool I2C0_MasterBusErrorOverride(void)
{
    return TWI0.MSTATUS & TWI_BUSERR_bm;
}

bool I2C0_MasterArbitrationlostOverride(void)
{
    return TWI0.MSTATUS & TWI_ARBLOST_bm;
}

void I2C0_MasterResetBus(void)
{
    TWI0.MCTRLB |= TWI_FLUSH_bm;
    TWI0.MSTATUS |= TWI_BUSSTATE_IDLE_gc;
}

void I2C0_MasterIsRxOrTx(void)
{
    TWI0.MCTRLB |= TWI_MCMD_RECVTRANS_gc;
}

void I2C0_MasterClearBusCollision(void)
{
    TWI0.MSTATUS |= TWI_ARBLOST_bm;
}

void I2C0_MasterWaitForEvent(void)
{
   while (!(TWI0.MSTATUS & TWI_RIF_bm) && !(TWI0.MSTATUS & TWI_WIF_bm)) 
   {
   };
}

void I2C0_MasterStop(void)
{
    TWI0.MCTRLB |= TWI_MCMD_STOP_gc;
}

bool I2C0_MasterIsNack(void)
{
    return TWI0.MSTATUS & TWI_RXACK_bm;
}

char I2C0_MasterGetRxData(void)
{
    return TWI0.MDATA;
}

void I2C0_MasterTxData(char d)
{
    TWI0.MDATA = d;
}

void I2C0_MasterTxAddr(char d)
{
    TWI0.MADDR = d;
}

void I2C0_MasterSendAck(void)
{
    TWI0.MCTRLB &= ~(1 << TWI_ACKACT_bp);
}

void I2C0_MasterSendNack(void)
{
    TWI0.MCTRLB |= TWI_ACKACT_NACK_gc;
}

twi0_operations_t I2C0_SetReturnStopCallback(void *funPtr)
{
    return I2C_STOP;
}

twi0_operations_t I2C0_SetReturnResetCallback(void *funPtr)
{
    return I2C_RESET_LINK;
}

twi0_operations_t I2C0_SetRestartWriteCallback(void *funPtr)
{
    return I2C_RESTART_WRITE;
}

twi0_operations_t I2C0_SetRestartReadCallback(void *funPtr)
{
    return I2C_RESTART_READ;
}