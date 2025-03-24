#include "rs232.h"

RS232 RS232::RS232_;

RS232::RS232()
{
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0A = 0X00; // Register containing flags and configurations

    UCSR0B |= (1 << TXEN0) | (1 << RXEN0);   // Enable transmission
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // 8 bits, 1 stop bit, no parity
}

void RS232::sendData(const uint8_t data)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }
    UDR0 = data;
}

void RS232::sendData(const uint8_t *data, uint16_t length)
{
    for (uint16_t i = 0; i < length; i++)
    {
        sendData(data[i]);
    }
}

uint8_t RS232::receiveData()
{
    while (!(UCSR0A & (1 << RXC0)))
    {

    }
    return UDR0;
}

void RS232::receiveData(uint8_t *data, uint16_t length)
{
    for (uint16_t i = 0; i < length; i++)
    {
        data[i] = receiveData(); 
    }
}
