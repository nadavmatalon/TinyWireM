/*==============================================================================================================*
 
    @file     TinyWireM.h

 *==============================================================================================================*/

#ifndef TinyWireM_h
#define TinyWireM_h

#include <inttypes.h>
#include "Stream.h"

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
        void setClock(uint32_t);
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
