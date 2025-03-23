#define F_CPU 8000000UL

#include <util/delay.h>
#include "timer1.h"
#include "button.h"
#include "led.h"
#include "ports.h"
#include "memoire_24.h"
#include "debug.h"
#include "wheels.h"
#include "tone.h"

#define DELAI_5_MS 5
#define DELAI_25_MS 25

volatile bool gExpired = false;
Memoire24CXXX mem;

void getNextInstruction(uint16_t &address, uint8_t &instruction, uint8_t &operande)
{

    uint8_t temp = 0x00;
    mem.lecture(address, &temp);
    instruction = temp;
    address++;
    _delay_ms(DELAI_5_MS);
    mem.lecture(address, &temp);
    operande = temp;
    address++;
}

int main()
{

    uint8_t startingAddress = 0x02;
    uint16_t address = startingAddress;

    uint8_t instruction = 0x00; // valeur de l'instruction
    uint8_t operande = 0x00;    // valeur de l'operande

    uint8_t savedAddress = 0x00; // position actuelle dans la memoire
    uint8_t loopCounter = 0x00;  // compteur pour la boucle

    bool codeActif = false;

    // Construction des class
    Led led(Port::A, Pin::N1, Pin::N2);
    Timer1 timer = Timer1();
    Timer1 delayTimer;
    Timer2 pwmTimer;
    Tone tone = Tone();
    Wheels wheels = Wheels(&delayTimer, &pwmTimer);

    // Lecture de la taille du programme

    uint8_t highByte = 0x00;
    uint8_t lowByte = 0x00;
    mem.lecture(0x00, &highByte);
    mem.lecture(0x01, &lowByte);

    uint8_t byteShift = 8;
    uint16_t programSize = (highByte << byteShift) | lowByte;

    DEBUG_PRINT(programSize);

    while (programSize)
    {

        getNextInstruction(address, instruction, operande);

        if (instruction == 0x01)
        {
            codeActif = true;
        }

        programSize--;
        if (programSize == 0)
            codeActif = false;

        if (codeActif)
        {
            uint8_t speed = (operande * 100 / 255);

            switch (instruction)
            {
            case 0x01:
                // commande de debut de programme (rien a faire, deja dans le programme car codeActif == true)
                break;

            case 0x02:

                for (uint8_t i = 0; i < operande; i++)
                {
                    timer.initializeTimerForDelays(gExpired);
                    timer.startTimer(196); // valeur calculer 25 ms ou utiliser un delay_ms
                }
                break;

            case 0x44:
                switch (operande)
                {
                case 0x01:
                    led.lightUp(Color::GREEN);
                    break;
                case 0x02:
                    led.lightUp(Color::RED);
                    break;
                default:
                    DEBUG_PRINT("operande LED non valide");
                    break;
                }
                break;

            case 0x45:
                led.lightUp(Color::OFF);
                break;

            case 0x48:

                tone.playNote(operande);
                // jouer une sonorité
                break;

            case 0x09:

                tone.turnOffMusic();
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
            {

                uint8_t speedPercentageFixRight = 50; // a calculer experimentalement
                uint16_t fixDelayRight = 1000;        // a calculer experimentalement
                wheels.goRight(speedPercentageFixRight, fixDelayRight);
                // tourner a droite
                break;
            }

            case 0x65:
            {

                uint8_t speedPercentageFixLeft = 50; // a calculer experimentalement
                uint16_t fixDelayLeft = 1000;        // a calculer experimentalement
                wheels.goLeft(speedPercentageFixLeft, fixDelayLeft);
                // tourner a gauche
                break;
            }
            case 0xc0:
                savedAddress = address;
                loopCounter = operande;
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
                led.lightUp(Color::OFF);
                tone.turnOffMusic();
                break;

            default:
                DEBUG_PRINT("instruction non valide");
                break;
            }
        }
    }
}
