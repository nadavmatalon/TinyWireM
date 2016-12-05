/*
    TinyWireM Library: ATtiny841-Side (Master)
    ------------------------------------------

    INTRODUCTION
    ------------
    The following sketch provides a simple example of setting up an ATtiny841 as an I2C Bus Master
    and an Arduino Uno as a Slave device located at I2C address 100.

    At runtime, the ATtiny841 Master will send successive bytes to the Arduino Slave which will then
    print them out using the Serial Monitor.

    HW SETUP
    --------
    - Connect Arduino Pin A4 (HW SDA) to ATtiny841 Pin PA0 (SW SDA) with a 2K2 pull-up resistor to 5V
    - Connect Arduino Pin A5 (HW SCL) to ATtiny841 Pin PA5 (SW SCL) with a 2K2 pull-up resistor to 5V
    - Follow the basic hookup for Arduino & ATtiny841 (Common ground for both ICs, 100nF decoupling capacitors,
      10K pullup resistors for RESET pins, and if needed, external crystals)


    RUNNING THE SKETCH
    ------------------
    Upload this sketch to the ATtiny841 and the other example sketch (Arduino_Uno_Slave.ino) to the
    Arduino. Then open the Serial Monitor (make sure the Baud Rate is set to 9600).

    BUG REPORTS
    -----------
    Please report any bugs/issues/suggestions at the GITHUB Repository of this library at:
    https://github.com/nadavmatalon/TinyWireM

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

#define __AVR_ATtiny841__

#include <Arduino.h>
#include "TinyWireM.h"

const byte SLAVE_ADDR = 100;

unsigned long timeNow;

boolean slavePresent = false;

byte data = 0;

void setup() {
    TinyWireM.begin();
    timeNow = millis();
}

void loop() {
    if (millis() - timeNow >= 500) {
        if (!slavePresent) {                                            // determine if slave joined the I2C bus
            TinyWireM.beginTransmission(SLAVE_ADDR);                    // begin call to slave
            if (TinyWireM.endTransmission() == 0) slavePresent = true;  // if responds - mark slave as present
        } else {                                                        // slave found on I2C bus
            TinyWireM.beginTransmission(SLAVE_ADDR);                    // begin call to slave
            TinyWireM.write(data);                                      // send a single byte to slave
            TinyWireM.endTransmission();                                // end call to slave
            data += 1;                                                  // increment data to send
        }
        timeNow = millis();                                             // mark current time (in mS)
    }
}
