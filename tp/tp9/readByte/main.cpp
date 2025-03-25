#define F_CPU 8000000UL

#include <util/delay.h>
#include "debug.h"
#include "memoire_24.h"
#define DELAY_BYTECODE_MS 5

const uint8_t BYTE_SHIFT = 8;


int main()
{
    Memoire24CXXX mem;
    uint8_t address = 0x00;
    uint8_t addressSize1 = RS232::receiveData();

    // Écritude du premier byte
    mem.ecriture(address, addressSize1);
    _delay_ms(DELAY_BYTECODE_MS);

    uint16_t realSize = addressSize1 << BYTE_SHIFT;

    // Lecture du second byte
    address++;
    addressSize1 = RS232::receiveData();
    mem.ecriture(address, addressSize1);
    _delay_ms(DELAY_BYTECODE_MS);

    realSize |= addressSize1;

    // Lecture des instructions et stockage en mémoire
    for (uint16_t j = 2; j < realSize; j++)
    {
        uint8_t buffer = RS232::receiveData();
        mem.ecriture(j, buffer);
        _delay_ms(DELAY_BYTECODE_MS);
    }
}