#define F_CPU 8000000UL

#include <util/delay.h>
#include "timer1.h"
#include "button.h"
#include "led.h"
#include "ports.h"
#include "memoire_24.h"
#include "debug.h"

#define DELAI_5_MS 5
#define DELAI_25_MS 25

volatile bool gExpired = false;
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

uint8_t savedAddress = 0x00; // position actuelle dans la memoire
uint8_t loopCounter = 0x00; // compteur pour la boucle

bool codeActif = false;

Led led(Port::A, Pin::N1, Pin:: N2); //creation de l'objet led
Timer1 Timer(TimerMode::NORMAL);
//Wheels wheels(Timer1 *delayTimer, Timer2 *pwmTimer, Ports *portsUtility); //creation de l'objet roues

while(true) {

getNextInstruction(address, instruction, operande);
 
// transformer les deux premiers octets 
if (instruction == 0x01) {
    codeActif = true;
}

if (codeActif) {

switch (instruction) {
    case 0x01:
        //commande de debut de programme (rien a faire, deja dans le programme car codeActif == true)
        break;

    case 0x02:
    
    for (uint8_t i = 0; i < operande; i++) 
    {
       Timer.initializeTimerForDelays(gExpired);
       Timer.startTimer(196); // valeur calculer 25 ms
        }
        break;

    case 0x44:
        switch (operande) {
            case 0x01:
            led.lightUp(Color::GREEN);
            break;
            case 0x02:
            led.lightUp(Color::RED);
            break;
            default:
                DEBUG_PRINT("operande LED non valide");
            break; }
        break;
    
    case 0x45:
        led.lightUp(Color::OFF);
        break;
    
    case 0x48:

        switch(operande) {

            case 

        }
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

    case 0xc0:
        savedAddress = address;
        loopCounter = operande;
        break;
    
    case 0xc1:
    loopCounter--;
        if (loopCounter > 0) {
            address = savedAddress;
        }
        break;
    
    case 0xff:
        codeActif = false;
        break;
    
    default:
        DEBUG_PRINT("instruction non valide");
        break;
    }
}
}
}


