/*
    TinyWireM Library: Arduino-Uno-Side (Slave)
    -------------------------------------------

    INTRODUCTION
    ------------
    The following sketch provides a simple example of setting up an ATtiny84A or ATtiny841 as
    an I2C Bus Master and an Arduino Uno as a Slave device located at I2C address 100.

    At runtime, the ATtiny Master will send successive bytes to the Arduino Slave which will then
    print them out using the Serial Monitor.

    HW SETUP
    --------
    - Connect Arduino Pin A4 (HW SDA) to ATtiny84A/841 Pin PA0 (SW SDA) with a 2K2 pull-up resistor to 5V
    - Connect Arduino Pin A5 (HW SCL) to ATtiny84A/841 Pin PA5 (SW SCL) with a 2K2 pull-up resistor to 5V
    - Follow the basic hookup for Arduino & ATtiny84A (Common Ground for both ICs, 100nF decoupling capacitors,
      10K pullup resistors for RESET pins, and if needed, external crystals)

    RUNNING THE SKETCH
    ------------------
    Upload this sketch to the Arduino Uno and the other example sketch (ATtiny84A_Master.ino) to the
    ATtiny84A. Then open the Serial Monitor (make sure the Baud Rate is set to 9600).

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

#include <Arduino.h>
#include <Wire.h>

volatile byte flag = 0;

volatile byte data = 0;

const byte SLAVE_ADDR = 100;

void setup() {
    Serial.begin(9600);
    Wire.begin(SLAVE_ADDR);
    Wire.onReceive(receiveData);
}

void loop() {
    if (flag) {
        flag = 0;
        Serial.println(data);
    }
}

void receiveData() {
    flag = 1;
    data = Wire.read();
}
