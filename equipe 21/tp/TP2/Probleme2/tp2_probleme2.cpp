/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme
 * Version: 1.1
 *
 * Version 1.2 par Jérôme Collin, août 2023
 *
 */



/*Elliot Gareau (2398724), Anis Feteh Benabderrahmane (2304821)
Description: "Quand la carte mère démarre, la DEL libre doit s'allumer en rouge. Si le bouton-poussoir libre pour usage général est pesé, la DEL affiche la couleur ambre. Quand le bouton-poussoir est relâché, la DEL devient verte. Si le bouton est de nouveau pesé, la DEL prend la couleur rouge encore. Quand il est relâché, la DEL s'éteint. Si le bouton est de nouveau pesé, la DEL affiche la couleur verte. Quand il est relâché, la DEL tourne au rouge ce qui fait que la carte mère est de retour à son état initial et tout peut recommencer." Source: https://cours.polymtl.ca/inf1900/tp/tp2/
Composantes utilisées: DEL bicolore, Bouton Poussoir
sortie: DEL bicolore, PORTA, PA0 et PA1
entrées: Bouton poussoir, PIND & (1 << PD2) 
/*
+----------------+-----------------+----------------+-------------+--+
| ÉTAT PRÉSENT   | ENTRÉE          | ÉTAT SUIVANT   | SORTIE Z    |  |
+----------------+-----------------+----------------+-------------+--+
| STATE_INITIAL  | BOUTTON PESÉ    | STATE_PUSH     | LED ROUGE   |  |
| STATE_PUSH1    | BOUTTON RELACHÉ | STATE_RELEASE1 | LED AMBRE   |  |
| STATE_RELEASE1 | BOUTTON PESÉ    | STATE_PUSH2    | LED VERTE   |  |
| STATE_PUSH2    | BOUTTON RELACHÉ | STATE_RELEASE2 | LED ROUGE   |  |
| STATE_RELEASE2 | BOUTTON PESÉ    | STATE_PUSH3    | LED ÉTEINTE |  |
| STATE_PUSH3    | BOUTTON RELACHÉ | STATE_INITIAL  | LED VERTE   |  |
|                |                 |                |             |  |
+----------------+-----------------+----------------+-------------+--+
*/
#define F_CPU 800000UL
#include <util/delay.h>
#include <avr/io.h>

const uint8_t DELAY_RED_TO_GREEN = 3;
const uint8_t DELAY_GREEN_TO_RED = 5;
const uint8_t DELAY_DEBOUNCE_BUTTON = 10;

void initialize()
{

  DDRA |=  (1 << PA0) | (1 << PA1);
  DDRD &= ~(1 << PD2);
}

void delRed()
{
  PORTA |= (1 << PA0);
  PORTA &= ~(1 << PA1);
}

void delGreen()
{
  PORTA |= (1 << PA1);
  PORTA &= ~(1 << PA0);
}
void delOff() {
    PORTA &= ~(1 << PA0);
}

void delYellow()
{
    delRed();
    _delay_ms(DELAY_RED_TO_GREEN);
    delGreen();
    _delay_ms(DELAY_GREEN_TO_RED);
}



bool buttonPressed() {
    if (PIND & (1 << PD2)) {
        _delay_ms(DELAY_DEBOUNCE_BUTTON);
        if (PIND & (1 << PD2)) {
            return true;
        }
    }
    return false;
}



enum class State{
    STATE_INITIAL,
    STATE_PUSH1,
    STATE_RELEASE1,
    STATE_PUSH2,
    STATE_RELEASE2,
    STATE_PUSH3

};

int main() {
    initialize();
    State currentState = State::STATE_INITIAL;

    while (1) {
        switch (currentState) {
            case State::STATE_INITIAL:
                delRed();
                if (buttonPressed()) {
                    currentState = State::STATE_PUSH1;
                }
                break;

            case State::STATE_PUSH1:
                delYellow();
                if (!buttonPressed()) {
                    currentState = State::STATE_RELEASE1;
                }
                break;

            case State::STATE_RELEASE1:
                delGreen();
                if (buttonPressed()) {
                    currentState = State::STATE_PUSH2;
                }
                break;

            case State::STATE_PUSH2:
                delRed();
                if (!buttonPressed()) {
                    currentState = State::STATE_RELEASE2;
                }
                break;

            case State::STATE_RELEASE2:
                delOff();
                if (buttonPressed()) {
                    currentState = State::STATE_PUSH3;
                }
                break;

            case State::STATE_PUSH3:
                delGreen();
                if (!buttonPressed()) {
                currentState = State::STATE_INITIAL;
                }
                break;

            default:
                currentState = State::STATE_INITIAL;
                break;
        }
    }

    return 0;
}


