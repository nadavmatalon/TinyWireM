// TinyWire.h

#ifndef _TinyWire_h
#define _TineWire_h

#include <Arduino.h>
#include <TinyWire_USI.h>
#include <inttypes.h>
#include <avr/io.h>

#define BUFFER_LENGTH 32

class TinyWire : public Stream {

    private:
        byte rxBuffer[BUFFER_LENGTH];
        byte rxBufferIndex;
        byte rxBufferLength;
        byte transmitting;
        byte error;

    public:
        TinyWire() {}
    
    void begin() {
        rxBufferIndex  = 0;
        rxBufferLength = 0;
        error          = 0;
        transmitting   = false;
        i2c_init();
    }
  
    void end() {}

//    void setClock(unsigned long _) {}

    void beginTransmission(byte address) {
        if (transmitting) {
            error = (i2c_rep_start((address << 1) | I2C_WRITE) ? 0 : 2);
        } else {
            i2c_start_wait((address << 1) | I2C_WRITE);
            error = 0;
        }
        transmitting = 1;                   // indicate that we are transmitting
    }

    byte endTransmission(byte sendStop) {
        byte transError = error;
        if (sendStop) {
            i2c_stop();
            transmitting = 0;
        }
        error = 0;
        return transError;
    }

    byte endTransmission() {                    //	This provides backwards compatibility with the original
        return endTransmission(true);           //	definition, and expected behaviour, of endTransmission
    }

    size_t write(byte data) {
        if (i2c_write(data)) return 1;
        else {
            if (error == 0) error = 3;
            return 0;
        }
    }

    size_t write(const byte *data, size_t quantity) {
        size_t trans = 0;
        for (size_t i=0; i<quantity; ++i) trans += write(data[i]);
        return trans;
    }

    byte requestFrom(byte address, byte quantity, unsigned long iaddress, byte isize, byte sendStop) {
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

    byte requestFrom(byte address, byte quantity, byte sendStop) {
        return requestFrom((byte)address, (byte)quantity, (unsigned long)0, (byte)0, (byte)sendStop);
    }

    byte requestFrom(int address, int quantity, int sendStop) {
        return requestFrom((byte)address, (byte)quantity, (byte)sendStop);
    }


    byte requestFrom(byte address, byte quantity) {
        return requestFrom((byte)address, (byte)quantity, (byte)true);
    }

    byte requestFrom(int address, int quantity) {
        return requestFrom((byte)address, (byte)quantity, (byte)true);
    }

    int available() {
        return rxBufferLength - rxBufferIndex;
    }

    int read() {
        int value = -1;
        if(rxBufferIndex < rxBufferLength) {
            value = rxBuffer[rxBufferIndex];
            ++rxBufferIndex;
        }
        return value;
    }

    int peek() {
        int value = -1;
        if (rxBufferIndex < rxBufferLength) value = rxBuffer[rxBufferIndex];
        return value;
    }

    void flush() {}

    inline size_t write(unsigned long n) { return write((byte)n); }

    inline size_t write(long n) { return write((byte)n); }

    inline size_t write(unsigned int n) { return write((byte)n); }

    inline size_t write(int n) { return write((byte)n); }

    using Print::write;

};

#endif
