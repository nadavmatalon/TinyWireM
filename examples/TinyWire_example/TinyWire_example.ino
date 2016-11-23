/*
  TINYWIRE LIBRARY
  ----------------

  INTRODUCTION
  ------------ 



  ATTINY84A PINOUT
  ----------------

   ACTUAL PIN       PIN NAME       ARDUINO NAME       FUNCTION
   ----------       --------       ------------       --------
       1              VCC              -                VCC
       2              PB0              0                XTAL1
       3              PB1              1                XTAL2
       4              PB3              -                RESET
       5              PB2              2                I/O  -  SCL2 (MASTER)
       6              PA7              3                I/O  -  SDA2 (MASTER)
       7              PA6              4                I/O | MOSI
       8              PA5              5                I/O | MISO
       9              PA4              6                I/O | SCK
      10              PA3              7                I/O
      11              PA2              8                I/O
      12              PA1              9                I/O  - SCL1 (SLAVE)
      13              PA0             10                I/O  - SDA1 (SLAVE)
      14              GND              -                GND


  BUG REPORTS
  -----------
  Please report any bugs/issues/suggestions at the GITHUB Repository of this library at: https://github.com/nadavmatalon/TinyWire

  LICENSE
  -------
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
*/

#include <Arduino.h>

#define F_CPU   20000000UL

#define __AVR_ATtiny84__

#define SDA_PORT PORTA
#define SDA_PIN 7
#define SCL_PORT PORTB
#define SCL_PIN 2

#define I2C_TIMEOUT 100
#define I2C_FASTMODE 1

const byte I2C_SLAVE_ADDR = 38;

#include "TinyWireS.h"
#include "TinyWire.h"

TinyWire TinyWireM = TinyWire();

void setup() {
    TinyWireS.begin(I2C_SLAVE_ADDR);
    TinyWireM.begin();
    pinMode(7, OUTPUT);
    TinyWireS.onReceive (receiveEvent);
    TinyWireS.onRequest (requestEvent);
}

void loop() {
//     for (byte i=0; i<6; i++) {
//        digitalWrite(7, HIGH);
//        delay(250);
//        digitalWrite(7, LOW);
//        delay(250);
//    }
//    delay(750);
//    TinyWireM.beginTransmission(100);
//    TinyWireM.write(50);
//    blinkLed(TinyWireM.endTransmission());
//    delay(1000);
//    for (byte i=0; i<6; i++) {
//        digitalWrite(7, HIGH);
//        delay(250);
//        digitalWrite(7, LOW);
//        delay(250);
//    }
//    delay(750);
    }

    void blinkLed(byte blinks) {
    if (blinks == 0) {
        digitalWrite(7, HIGH);
        return;
    } else {
        for (byte i=0; i<blinks; i++) {
            digitalWrite(7, HIGH);
            delay(250);
            digitalWrite(7, LOW);
            delay(250);
        }
    }
}

void receiveEvent (uint8_t howMany) {

}

void requestEvent () {
    byte msg1 = 50;
    TinyWireS.send(msg1);
} 

