/*==============================================================================================================*
 
    @file     TinyWire.h
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

#ifndef _TinyWire_h
#define _TineWire_h

#if !defined(ARDUINO_ARCH_AVR)
#error “The MCP9802 library only supports AVR processors.”
#endif

#include <Arduino.h>
#include <inttypes.h>
#include <avr/io.h>
#include <Stream.h>
//#include "TinyWire_Config.h"

namespace Tinywire {

    const byte BUFFER_LENGTH = 32;
    const byte DEFAULT_SDA_PORT = PORTA;
    const byte DEFAULT_SDA_PIN  = 7;
    const byte DEFAULT_SCL_PORT = PORTB;
    const byte DEFAULT_SCL_PIN  = 2;

    class TinyWire : public Stream {
        private:
            byte devAddr;
            byte sdaPort;
            byte sdaPin;
            byte sclPort;
            byte sclPin;
            byte rxBuffer[BUFFER_LENGTH];
            byte rxBufferIndex;
            byte rxBufferLength;
            byte transmitting;
            byte error;
        public:
            TinyWire(                                                               // MASTER
                     byte sda_port = DEFAULT_SDA_PORT,
                     byte sda_pin  = DEFAULT_SDA_PIN,
                     byte scl_port = DEFAULT_SCL_PORT,
                     byte scl_pin  = DEFAULT_SCL_PIN
                    );
            TinyWire(const byte deviceAddr);                                        // SLAVE
            ~TinyWire();                                                            // MASTER / SLAVE
            void   begin();                                                         // MASTER
//          void   begin();                                                         // SLAVE
            void   end();                                                           // MASTER
//          void   end();                                                           // SLAVE
            void   beginTransmission(byte address);
            byte   endTransmission();
            byte   endTransmission(byte sendStop);
            int    available();
            int    peek();
            int    read();
            size_t write(byte data);
            size_t write(const byte *data, size_t quantity);
            void   flush();
            byte   requestFrom(byte address, byte quantity);
            byte   requestFrom(int address, int quantity);
            byte   requestFrom(byte address, byte quantity, byte sendStop);
            byte   requestFrom(int address, int quantity, int sendStop);
            byte   requestFrom(byte address, byte quantity, unsigned long iaddress, byte isize, byte sendStop);
            inline size_t write(unsigned long n) { return write((byte)n); }
            inline size_t write(long n) { return write((byte)n); }
            inline size_t write(unsigned int n) { return write((byte)n); }
            inline size_t write(int n) { return write((byte)n); }
            using Print::write;
     };
}

using namespace Tinywire;

#endif
