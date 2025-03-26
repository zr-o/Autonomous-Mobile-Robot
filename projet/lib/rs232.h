#ifndef RS232_H
#define RS232_H

#include <avr/io.h>

class RS232
{
public:
    static void sendData(const uint8_t data);
    static void sendData(const uint8_t *data, uint16_t length);
    static uint8_t receiveData();
    static void receiveData(uint8_t *data, uint16_t length);

    RS232(RS232 &other) = delete;
    void operator=(const RS232 &other) = delete;

private:
    RS232();
    static RS232 RS232_;
};

#endif