#define F_CPU 8000000UL

#include <util/delay.h>
#include "debug.h"
#include "memoire_24.h"
#define DELAY_BYTECODE_MS 5

int main() {

Memoire24CXXX mem;
uint8_t temp = 0x00;

    // Lire le premier octet
    uint8_t byteShift = 8;
    uint8_t tempSize1 = RS232::receiveData();
    mem.ecriture(temp, tempSize1);
    _delay_ms(DELAY_BYTECODE_MS);
    uint16_t realSize_ = tempSize1 << byteShift; // Decalage pour préparer la taille

    
    // Lire le deuxième octet 
    temp++;
    tempSize1 = RS232::receiveData();
    mem.ecriture(temp, tempSize1);
    _delay_ms(DELAY_BYTECODE_MS);
    realSize_ |= tempSize1; 
    
    // Lire les instructions et les stocker en memoire
    for (uint16_t j = 2; j < realSize_; j++) {
        uint8_t buffer = RS232::receiveData();
        mem.ecriture(j, buffer);
        _delay_ms(DELAY_BYTECODE_MS);
    }
}