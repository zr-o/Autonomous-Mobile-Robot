#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>
#include "debug.h"
#include "memoire_24.h"

#define DELAY_BYTECODE_MS 5
#define BYTE_SHIFT 8

int main()
{
    Memoire24CXXX mem;
    uint8_t address = 0x00;
    uint8_t addressSize1 = RS232::receiveData();
    uint16_t realSize = 0;

    // Écritude du premier byte
    mem.ecriture(address, addressSize1);
    _delay_ms(DELAY_BYTECODE_MS);
    realSize = addressSize1 << BYTE_SHIFT;
    address++;

    // Lecture du second byte
    addressSize1 = RS232::receiveData();
    mem.ecriture(address, addressSize1);
    _delay_ms(DELAY_BYTECODE_MS);
    realSize |= addressSize1;
    address++;

    uint8_t buffer = 0;

    // Lecture des instructions et stockage en mémoire
    for (; address < realSize; address++)
    {
        buffer = RS232::receiveData();
        mem.ecriture(address, buffer);
        _delay_ms(DELAY_BYTECODE_MS);
    }
}