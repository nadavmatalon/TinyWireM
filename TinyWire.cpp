/*==============================================================================================================*
 
    @file     TinyWire.cpp
    @author   Nadav Matalon
    @license  MIT (c) 2016 Nadav Matalon

    ATtiny I2C Master & Slave Library

    Ver. 1.0.0 - First release (23.11.16)

 *==============================================================================================================*
     LICENSE
 *==============================================================================================================*
 
    The MIT License (MIT)
    Copyright (c) 2016 Nadav Matalon

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
    documentation files (the "Software"), to deal in the Software without restriction, including without
    limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
    the Software, and to permit persons to whom the Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial
    portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
    LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
 *==============================================================================================================*/

#if 1
__asm volatile ("nop");
#endif

#include "TinyWire.h"
#include <TinyWire_USI.h>

/*==============================================================================================================*
    MASTER CONSTRUCTOR
 *==============================================================================================================*/

TinyWire::TinyWire() {}

/*==============================================================================================================*
    SLAVE CONSTRUCTOR
 *==============================================================================================================*/

TinyWire::TinyWire(byte deviceAddr) {
    devAddr = deviceAddr;
}

/*==============================================================================================================*
    DESTRUCTOR
 *==============================================================================================================*/

TinyWire::~TinyWire() {}

/*==============================================================================================================*
    MASTER BEGIN
 *==============================================================================================================*/

void TinyWire::begin() {
    rxBufferIndex  = 0;
    rxBufferLength = 0;
    error          = 0;
    transmitting   = false;
    i2c_init();
}

/*==============================================================================================================*
    SLAVE BEGIN
 *==============================================================================================================*/



/*==============================================================================================================*
    MASTER END
 *==============================================================================================================*/

void TinyWire::end() {}


/*==============================================================================================================*
    SLAVE END
 *==============================================================================================================*/


/*==============================================================================================================*
    BEGIN TRANSMISSION
 *==============================================================================================================*/

void TinyWire::beginTransmission(byte address) {
    if (transmitting) error = (i2c_rep_start((address << 1) | I2C_WRITE) ? 0 : 2);
    else {
        i2c_start_wait((address << 1) | I2C_WRITE);
        error = 0;
    }
    transmitting = 1;
}

/*==============================================================================================================*
    END TRANSMISSION
 *==============================================================================================================*/

byte TinyWire::endTransmission() {                      // This provides backwards compatibility with the original
    return endTransmission(true);                       // definition, and expected behaviour, of endTransmission
}

byte TinyWire::endTransmission(byte sendStop) {
    byte transError = error;
    if (sendStop) {
        i2c_stop();
        transmitting = 0;
    }
    error = 0;
    return transError;
}

/*==============================================================================================================*
    AVAILABLE
 *==============================================================================================================*/

int TinyWire::available() {
    return rxBufferLength - rxBufferIndex;
}

/*==============================================================================================================*
    PEEK
 *==============================================================================================================*/

int TinyWire::peek() {
    int value = -1;
    if (rxBufferIndex < rxBufferLength) value = rxBuffer[rxBufferIndex];
    return value;
}

/*==============================================================================================================*
    READ
 *==============================================================================================================*/

int TinyWire::read() {
    int value = -1;
    if(rxBufferIndex < rxBufferLength) {
        value = rxBuffer[rxBufferIndex];
        ++rxBufferIndex;
    }
    return value;
}

/*==============================================================================================================*
    WRITE
 *==============================================================================================================*/

size_t TinyWire::write(byte data) {
    if (i2c_write(data)) return 1;
    else {
        if (error == 0) error = 3;
        return 0;
    }
}

size_t TinyWire::write(const byte *data, size_t quantity) {
    size_t trans = 0;
    for (size_t i=0; i<quantity; ++i) trans += write(data[i]);
    return trans;
}

/*==============================================================================================================*
    FLUSH
 *==============================================================================================================*/

void TinyWire::flush() {}

/*==============================================================================================================*
    REQUEST FROM
 *==============================================================================================================*/

byte TinyWire::requestFrom(byte address, byte quantity) {
    return requestFrom((byte)address, (byte)quantity, (byte)true);
}

byte TinyWire::requestFrom(int address, int quantity) {
    return requestFrom((byte)address, (byte)quantity, (byte)true);
}

byte TinyWire::requestFrom(byte address, byte quantity, byte sendStop) {
    return requestFrom((byte)address, (byte)quantity, (unsigned long)0, (byte)0, (byte)sendStop);
}

byte TinyWire::requestFrom(int address, int quantity, int sendStop) {
    return requestFrom((byte)address, (byte)quantity, (byte)sendStop);
}

byte TinyWire::requestFrom(byte address, byte quantity, unsigned long iaddress, byte isize, byte sendStop) {
    byte localerror = 0;
    if (isize > 0) {
        // send internal address; this mode allows sending a repeated start to access
        // some devices' internal registers. This function is executed by the hardware
        // TWI module on other processors (for example Due's TWI_IADR and TWI_MMR registers)
        beginTransmission(address);
        // the maximum size of internal address is 3 bytes
        if (isize > 3) isize = 3;
        // write internal register address - most significant byte first
        while (isize-- > 0) write((byte)(iaddress >> (isize * 8)));
        endTransmission(false);
    }
    if (quantity > BUFFER_LENGTH) quantity = BUFFER_LENGTH;                               // clamp to buffer length
    localerror = !i2c_rep_start((address << 1) | I2C_READ);
    if (error == 0 && localerror) error = 2;
    for (byte cnt=0; cnt<quantity; cnt++) rxBuffer[cnt] = i2c_read(cnt == quantity - 1);  // perform blocking read into buffer
    rxBufferIndex = 0;                                                                    // set rx buffer iterator vars
    rxBufferLength = quantity;
    if (sendStop) {
        transmitting = 0;
        i2c_stop();
    }
    return quantity;
}
