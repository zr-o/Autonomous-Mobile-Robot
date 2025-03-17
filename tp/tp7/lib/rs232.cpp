#include "rs232.h"

RS232::RS232()
{

    UBRR0H = 0;

    UBRR0L = 0xCF;

    UCSR0A = 0X00; // Registre qui contient seuleument des flags et des configurations qui nous interesse pas

    UCSR0B |= (1 << TXEN0); // Active la transmission

    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Format des trames: 8 bits, 1 stop bits, sans parité
}

void RS232::write(const char *message)
{
    uint8_t length = 0;

    while (message[length] != '\0')
    {
        length++;
    }

    for (uint8_t i = 0; i < length; i++)
    {
        while (!(UCSR0A & (1 << UDRE0)))
        { 
        }
        UDR0 = message[i]; 
    }
}
