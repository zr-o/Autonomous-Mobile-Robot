#define F_CPU 8000000UL

#include "timer1.h"
#include "button.h"
#include "led.h"
#include "tone.h"
#include "timer0.h"
#include "memoire_24.h"
#include "util/delay.h"

#define DELAY_5_MS 5
#define DELAY_25_MS 25
#define DELAY_MUSIC_MS 200

volatile bool gExpired = false;
Memoire24CXXX mem;

void getNextInstruction(uint16_t &address, uint8_t &instruction, uint8_t &operand)
{

    uint8_t tempAddress = 0x00;
    mem.lecture(address, &tempAddress);
    instruction = tempAddress;
    address++;
    _delay_ms(DELAY_5_MS);
    mem.lecture(address, &tempAddress);
    operand = tempAddress;
    address++;
}

ISR(TIMER1_COMPA_vect)
{
    gExpired = true;
    TIMSK1 &= ~(1 << OCIE1A);
}

int main()
{

    uint8_t startingAddress = 0x02;
    uint16_t address = startingAddress;

    uint8_t instruction = 0x00; // valeur de l'instruction
    uint8_t operand = 0x00;     // valeur de l'operande

    uint8_t savedAddress = 0x00; // position actuelle dans la memoire
    uint8_t loopCounter = 0x00;  // compteur pour la boucle

    bool codeActif = false;

    // Construction des class
    Led led(Port::B, Pin::N1, Pin::N2);
    Timer1 delayTimer;
    Timer2 pwmTimer;
    Timer0 timer0;
    Tone tone = Tone(&timer0);
    Wheels wheels = Wheels(&delayTimer, &pwmTimer);


    delayTimer.initializeTimerForDelays(gExpired);
    // Lecture de la taille du programme
    uint8_t tempSize = 0x00;
    mem.lecture(0x00, &tempSize);
    _delay_ms(DELAY_5_MS);
    uint8_t byteShift = 8;
    uint16_t programSize = tempSize << byteShift;
    mem.lecture(0x01, &tempSize);
    _delay_ms(DELAY_5_MS);
    programSize |= tempSize;

    while (!codeActif)
    {
        getNextInstruction(address, instruction, operand);

        if (instruction == 0x01)
        {

            codeActif = true;
        }
    }
    while (codeActif)
    {

        getNextInstruction(address, instruction, operand);

        uint8_t speed = (operand * 100 / 255);
        uint8_t speedPercentageFixRight = 50; // calculer experimentalement
        uint16_t fixDelayRight = 20650;       // calculer experimentalement
        uint8_t speedPercentageFixLeft = 50;  // calculer experimentalement
        uint16_t fixDelayLeft = 17000;        // calculer experimentalement#
        
        switch (instruction)
        {
        case 0x01:
            // commande de debut de programme (rien a faire, deja dans le programme car codeActif == true)
            break;

        case 0x02:
            for (uint8_t i = 0; i < operand; i++)
            {
                _delay_ms(DELAY_25_MS);
            }
            break;

        case 0x44:

            switch (operand)
            {
            case 0x01:
                led.lightUp(Color::GREEN);
                break;
            case 0x02:
                led.lightUp(Color::RED);
                break;
            default:
                DEBUG_PRINT("operand LED non valide");
                break;
            }
            break;

        case 0x45:
            led.lightUp(Color::OFF);
            break;

        case 0x48:

            tone.playNote(operand);
            _delay_ms(DELAY_MUSIC_MS);
            // jouer une sonorité
            break;

        case 0x09:

            tone.turnOffNote();
            // arreter de jouer la sonorité
            break;

        case 0x60:

            wheels.stop();
            // arreter moteurs
            break;

        case 0x61:

            wheels.stop();
            // arreter moteurs
            break;

        case 0x62:

            wheels.goForward(speed);
            // avancer
            break;

        case 0x63:

            wheels.goBackwards(speed);
            // reculer
            break;

        case 0x64:

            wheels.goRight(speedPercentageFixRight, fixDelayRight);
            // tourner a droite
            break;

        case 0x65:

            wheels.goLeft(speedPercentageFixLeft, fixDelayLeft);
            // tourner a gauche
            break;
        case 0xc0:
            savedAddress = address;
            loopCounter = operand + 1;
            break;

        case 0xc1:
            loopCounter--;
            if (loopCounter > 0)
            {
                address = savedAddress;
            }
            break;

        case 0xff:
            codeActif = false;
            wheels.stop();
            tone.turnOffNote();
            led.lightUp(Color::OFF);
            break;

        default:
            DEBUG_PRINT("instruction non valide");
            break;
        }
    }
}
