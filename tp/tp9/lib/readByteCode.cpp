#include "readByteCode.h"
#define DELAY_BYTECODE_MS 5

readByteCode::readByteCode() {
    realSize_= 0;
}

void readByteCode::readByte () {

uint8_t temp = 0x00;

    // Lire le premier octet
    uint8_t byteShift = 8;
    uint8_t tempSize1 = RS232::receiveData();
    mem.ecriture(temp, tempSize1);
    _delay_ms(DELAY_BYTECODE_MS);
    realSize_ = tempSize1 << byteShift; // Decalage pour préparer la taille
    _delay_ms(DELAY_BYTECODE_MS);
    
    // Lire le deuxième octet 
    temp++;
    tempSize1 = RS232::receiveData();
    _delay_ms(DELAY_BYTECODE_MS);
    mem.ecriture(temp, tempSize1);
    _delay_ms(DELAY_BYTECODE_MS);
    
    realSize_ |= tempSize1; 

    // Lire les instructions et les stocker en memoire
    for (uint16_t j = 2; j < realSize_; j++) {
        uint8_t buffer = RS232::receiveData();
        _delay_ms(DELAY_BYTECODE_MS);
        mem.ecriture(j, buffer);
        _delay_ms(DELAY_BYTECODE_MS);
    }
}

uint16_t readByteCode::getSize() const {

    return realSize_;
}