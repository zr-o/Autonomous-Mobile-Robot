#define F_CPU 8000000UL

#include <util/delay.h>
#include "timer1.h"
#include "button.h"
#include "led.h"
#include "ports.h"
#include "memoire_24.h"
#include "debug.h"

#define DELAI_5_MS 5

void getNextInstruction(uint16_t& address, uint8_t& instruction, uint8_t& operande) {

Memoire24CXXX mem;

uint8_t temp = 0x00;
mem.lecture(address, &temp);
instruction = temp;
address++;
_delay_ms(DELAI_5_MS);
mem.lecture(address, &temp);
operande = temp;
address++;

}

int main() {

uint16_t address = 0x00;

uint8_t instruction = 0x00; // valeur de l'instruction
uint8_t operande = 0x00; // valeur de l'operande
bool codeActif = false;

while(true) {

getNextInstruction(address, instruction, operande);

if (instruction == 0x01) {
    codeActif = true;
}

if (codeActif) {

switch (instruction) {
    case 0x01:
        //commande de debut de programme (rien a faire ca deja dans le programme)
        break;

    case 0x02:
       //delai
        break;

    case 0x44:
        switch (operande) {
            case 0x01:
            //led verte
            break;
            case 0x02:
            //led rouge
            break;
            default:
                DEBUG_PRINT("operande LED non valide");
            break; }
        break;
    
    case 0x45:
        //eteindre la led
        break;
    
    case 0x48:
        // jouer une sonorité
        break;

    case 0x09:
        //arreter de jouer la sonorité
        break;

    case 0x60:
        //arreter moteurs
        break;
    
    case 0x61:
        //arreter moteurs
        break;
    
    case 0x62:
        //avancer
        break;

    case 0x63:
        //reculer
        break;

    case 0x64:
        //tourner a droite
        break;

    case 0x65:
        //tourner a gauche
        break;
    
    case 0xc1:
        //boucle
        break;
    
    case 0xff:
        codeActif = false;
        break;
    
    default:
        //non valide
        break;
    }
}
}
}


