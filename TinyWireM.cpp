/*==============================================================================================================*
 
    @file     TinyWireM.cpp
    @license  MIT (c) 2016 Nadav Matalon

    ATtiny I2C Master Library

    Ver. 1.0.0 - First release (1.12.16)
 
 *===============================================================================================================*
    LICENSE
 *===============================================================================================================*
 
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

#include <stdlib.h>
#include <inttypes.h>
#include "utility/TinyWireM_USI.h"
#include "TinyWireM.h"

uint8_t USI_TWI_M::rxBuffer[BUFFER_LENGTH];
uint8_t USI_TWI_M::rxBufferIndex = 0;
uint8_t USI_TWI_M::rxBufferLength = 0;
uint8_t USI_TWI_M::transmitting = 0;
uint8_t USI_TWI_M::error = 0;

USI_TWI_M::USI_TWI_M() {}

void USI_TWI_M::begin() {
    rxBufferIndex = 0;
    rxBufferLength = 0;
    error = 0;
    i2c_init();
}

void USI_TWI_M::end() {}

void USI_TWI_M::beginTransmission(uint8_t address) {
    if (transmitting) error = (i2c_rep_start((address<<1)|I2C_WRITE) ? 0 : 2);
    else {
        i2c_start_wait((address<<1)|I2C_WRITE);
        error = 0;
    }
    transmitting = 1;
}

void USI_TWI_M::beginTransmission(int address) {
    beginTransmission((uint8_t)address);
}

uint8_t USI_TWI_M::endTransmission(uint8_t sendStop) {
    uint8_t transError = error;
    if (sendStop) {
        i2c_stop();
        transmitting = 0;
    }
    error = 0;
    return transError;
}

uint8_t USI_TWI_M::endTransmission() {
    return endTransmission(true);
}

size_t USI_TWI_M::write(uint8_t data) {
    if (i2c_write(data)) return 1;
    else {
        if (error == 0) error = 3;
        return 0;
    }
}

size_t USI_TWI_M::write(const uint8_t *data, size_t quantity) {
    size_t trans = 0;
    for(size_t i = 0; i < quantity; ++i) trans += write(data[i]);
    return trans;
}

uint8_t USI_TWI_M::requestFrom(uint8_t address, uint8_t quantity, uint32_t iaddress, uint8_t isize, uint8_t sendStop) {
    uint8_t localerror = 0;
    if (isize > 0) {
        beginTransmission(address);
        if (isize > 3) isize = 3;
        while (isize-- > 0) write((uint8_t)(iaddress >> (isize*8)));
        endTransmission(false);
    }
    if (quantity > BUFFER_LENGTH) quantity = BUFFER_LENGTH;
    localerror = !i2c_rep_start((address << 1) | I2C_READ);
    if (error == 0 && localerror) error = 2;
    for (uint8_t cnt=0; cnt < quantity; cnt++) rxBuffer[cnt] = i2c_read(cnt == quantity-1);
    rxBufferIndex = 0;
    rxBufferLength = quantity;
    if (sendStop) {
        transmitting = 0;
        i2c_stop();
    }
    return quantity;
}

uint8_t USI_TWI_M::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop) {
    return requestFrom((uint8_t)address, (uint8_t)quantity, (uint32_t)0, (uint8_t)0, (uint8_t)sendStop);
}

uint8_t USI_TWI_M::requestFrom(int address, int quantity, int sendStop) {
    return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)sendStop);
}


uint8_t USI_TWI_M::requestFrom(uint8_t address, uint8_t quantity) {
    return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

uint8_t USI_TWI_M::requestFrom(int address, int quantity) {
    return requestFrom((uint8_t)address, (uint8_t)quantity, (uint8_t)true);
}

int USI_TWI_M::available() {
    return rxBufferLength - rxBufferIndex;
}

int USI_TWI_M::read() {
    int value = -1;
    if(rxBufferIndex < rxBufferLength) {
        value = rxBuffer[rxBufferIndex];
        ++rxBufferIndex;
    }
    return value;
}

int USI_TWI_M::peek() {
    int value = -1;
    if (rxBufferIndex < rxBufferLength) value = rxBuffer[rxBufferIndex];
    return value;
}

void USI_TWI_M::flush() {}

USI_TWI_M TinyWireM = USI_TWI_M();
