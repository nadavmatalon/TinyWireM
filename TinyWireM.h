/*==============================================================================================================*
 
    @file     TinyWireM.h
    @license  MIT (c) 2016 Nadav Matalon

    ATtiny I2C Master Library

    Ver. 1.0.0 - First release (1.12.16)
 
 *===============================================================================================================*
    INTRODUCTION
 *===============================================================================================================*
 
    This library enables members of the ATtiny family to become an I2C Bus Master. The library is based on a
    software implementation of I2C which is slower than the hardware one, but nevertheless allows the user to set 
    any of the ATtiny pins as SDA & SCL.
 
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

#if 1
__asm volatile ("nop");
#endif

#ifndef TinyWireM_h
#define TinyWireM_h

#if !defined(ARDUINO_ARCH_AVR)
#error “The TinyWireM library only supports AVR processors.”
#endif

#include <Arduino.h>
#include <inttypes.h>
#include <Stream.h>

#define BUFFER_LENGTH 32

#define WIRE_HAS_END 1

class USI_TWI_M {
    private:
      static uint8_t rxBuffer[BUFFER_LENGTH];
      static uint8_t rxBufferIndex;
      static uint8_t rxBufferLength;
      static uint8_t transmitting;
      static uint8_t error;
    public:
        USI_TWI_M();
        void begin();
        void end();
        void beginTransmission(uint8_t address);
        void beginTransmission(int address);
        uint8_t endTransmission(uint8_t sendStop);
        uint8_t endTransmission(void);
        virtual size_t write(uint8_t data);
        virtual size_t write(const uint8_t *data, size_t quantity);
        uint8_t requestFrom(uint8_t address, uint8_t quantity, uint32_t iaddress, uint8_t isize, uint8_t sendStop);
        uint8_t requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop);
        uint8_t requestFrom(int address, int quantity, int sendStop);
        uint8_t requestFrom(uint8_t address, uint8_t quantity);
        uint8_t requestFrom(int address, int quantity);
        virtual int available();
        virtual int read();
        virtual int peek();
        virtual void flush();
    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }

};

extern USI_TWI_M TinyWireM;

#endif
