#define F_CPU 8000000UL

#include "timer1.h"
#include "button.h"
#include "led.h"
#include "tone.h"
#include "readByteCode.h"

#define DELAI_5_MS 5
#define DELAI_25_MS 25
#define DELAY_500_MS 500

volatile bool gExpired = false;
Memoire24CXXX mem;

void getNextInstruction(uint16_t &address, uint8_t &instruction, uint8_t &operand)
{

    uint8_t temp = 0x00;
    mem.lecture(address, &temp);
    instruction = temp;
    address++;
    _delay_ms(DELAI_5_MS);
    mem.lecture(address, &temp);
    operand = temp;
    address++;
}

int main()
{

    uint8_t startingAddress = 0x02;
    uint16_t address = startingAddress;

    uint8_t instruction = 0x00; // valeur de l'instruction
    uint8_t operand = 0x00;    // valeur de l'operande

    uint8_t savedAddress = 0x00; // position actuelle dans la memoire
    uint8_t loopCounter = 0x00;  // compteur pour la boucle

    bool codeActif = false;

    // Construction des class
    Led led(Port::B, Pin::N1, Pin::N2);
    Timer1 timer = Timer1();
    Timer1 delayTimer;
    Timer2 pwmTimer;
    Tone tone = Tone();
    Wheels wheels = Wheels(&delayTimer, &pwmTimer);
    // Lecture de la taille du programme
    readByteCode readByte = readByteCode();
    uint16_t programSize = readByte.getSize();
    DEBUG_PRINT(programSize);


    while (programSize)
    {

        getNextInstruction(address, instruction, operand);

        if (instruction == 0x01)
        {
            
            codeActif = true;
        }

        programSize--;
        if (programSize == 0) {
            codeActif = false;
            wheels.stop();
            led.lightUp(Color::OFF);
            tone.turnOffMusic();;
        }
        if (codeActif)
        {
            uint8_t speed = (operand * 100 / 255);

            switch (instruction)
            {
            case 0x01:
                // Pour s'assurer que le robot fonctionne et qu'on est au debut :
                led.lightUp(Color::GREEN);
                _delay_ms(DELAY_500_MS);
                led.lightUp(Color::RED);
                _delay_ms(DELAY_500_MS);
                led.lightUp(Color::GREEN);
                _delay_ms(DELAY_500_MS);
                led.lightUp(Color::OFF);
                DEBUG_PRINT("test");
                // commande de debut de programme (rien a faire, deja dans le programme car codeActif == true)
                break;

            case 0x02:

                for (uint8_t i = 0; i < operand; i++)
                {
                    timer.initializeTimerForDelays(gExpired);
                    timer.startTimer(196); // valeur calculer 25 ms ou utiliser un delay_ms
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

                uint8_t speedPercentageFixRight = 50; // calculer experimentalement
                uint16_t fixDelayRight = 20650; // calculer experimentalement

                wheels.goRight(speedPercentageFixRight, fixDelayRight);
                _delay_ms(50);
                wheels.stop();
                // tourner a droite
                break;
            }

            case 0x65:
            {

                uint8_t speedPercentageFixLeft = 50; // calculer experimentalement
                uint16_t fixDelayLeft = 17000;        //calculer experimentalement
                wheels.goLeft(speedPercentageFixLeft, fixDelayLeft);
                _delay_ms(50);
                wheels.stop();
                // tourner a gauche
                break;
            }
            case 0xc0:
                savedAddress = address;
                loopCounter = operand;
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
