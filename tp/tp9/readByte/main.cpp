#include "readByteCode.h"
#include <util/delay.h>
#include "tone.h"
#include "ports.h"
#include "led.h"
#define DELAY_BYTECODE_MS 5

int main() {

Memoire24CXXX mem;
Led led(Port::B, Pin::N1, Pin::N2);
uint8_t temp = 0x00;

    // Lire le premier octet
    uint8_t byteShift = 8;
    uint8_t tempSize1 = RS232::receiveData();
    mem.ecriture(temp, tempSize1);
    _delay_ms(DELAY_BYTECODE_MS);
    uint16_t realSize_ = tempSize1 << byteShift; // Decalage pour préparer la taille
    _delay_ms(DELAY_BYTECODE_MS);
    
    // Lire le deuxième octet 
    temp++;
    tempSize1 = RS232::receiveData();
    _delay_ms(DELAY_BYTECODE_MS);
    mem.ecriture(temp, tempSize1);
    _delay_ms(DELAY_BYTECODE_MS);
    realSize_ |= tempSize1; 
    
     DEBUG_PRINT(realSize_);
    // Lire les instructions et les stocker en memoire
    for (uint16_t j = 2; j < realSize_; j++) {
        uint8_t buffer = RS232::receiveData();
        _delay_ms(DELAY_BYTECODE_MS);
        mem.ecriture(j, buffer);
    }

    led.lightUp(Color::GREEN);
/*
Memoire24CXXX mem;

    readByteCode readByte = readByteCode();

    uint16_t realSize = readByte.getSize();
    // Lire les instructions et les stocker en memoire
    for (uint16_t j = 2; j < realSize; j++) {
        uint8_t buffer = RS232::receiveData();
        _delay_ms(DELAY_BYTECODE_MS);
        mem.ecriture(j, buffer);
        _delay_ms(DELAY_BYTECODE_MS);

}
*/
/*
char phrase[5] = {'A', 'L', 'L', 'O', '\0'}; // ce que l'on veut inscrire dans la memoire
for (uint8_t i = 0; i < 5; i++) {

    RS232::receiveData(phrase,4);
}

*/

/*
Ports::setPinMode(PortMode::WRITE,Port::B,Pin::N4);
Ports::setPinMode(PortMode::READ,Port::B,Pin::N3);

Tone tone = Tone();

while (true) {
tone.playNote(45);

*/


}