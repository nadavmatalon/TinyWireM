/*==============================================================================================================*
 
    @file     TinyWire_Config.h
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

#ifndef _TinyWire_Config_h
#define _TineWire_Config_h

namespace Tinywire {

//    const byte BUFFER_LENGTH = 32;

//    byte sdaPortDefault = PORTA;
//    byte sdaPinDefault  = 7;
//    byte sclPortDefault = PORTB;
//    byte sclPinDefault = 2;
    
}

#define SDA_PORT PORTA
#define SDA_PIN 7
#define SCL_PORT PORTB
#define SCL_PIN 2







#endif
