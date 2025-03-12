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
Description: "On veut ici simplement que la DEL soit éteinte au départ. On doit appuyer et relâcher 3 fois le bouton-poussoir avant que la DEL tourne au vert pendant exactement 2 secondes. Par la suite, on revient au départ pour pouvoir recommencer." Source: https://cours.polymtl.ca/inf1900/tp/tp2/
Composantes utilisées: DEL bicolore, Bouton Poussoir
sortie: DEL bicolore, PORTA, PA0 et PA1
entrées: Bouton poussoir, PIND & (1 << PD2)


*/

/*
+--------------+----------------------+--------------+----------------+--+
| ÉTAT PRÉSENT | ENTRÉE               | ÉTAT SUIVANT | SORTIE Z       |  |
+--------------+----------------------+--------------+----------------+--+
| STATE_OFF    | BOUTON NON-APPUYÉ    | STATE_OFF    | LED ÉTEINTE    |  |
| STATE_OFF    | BOUTON PESÉ-RELACHÉ  | PUSHRELEASE1 | LED ÉTEINTE    |  |
| PUSHRELEASE1 | BOUTON NON-APPUYÉ    | PUSHRELEASE1 | LED ÉTEINTE    |  |
| PUSHRELEASE1 | BOUTON PESÉ-RELACHÉ  | PUSHRELEASE2 | LED ÉTEINTE    |  |
| PUSHRELEASE2 | BOUTON NON-APPUYÉ    | PUSHRELEASE2 | LED ÉTEINTE    |  |
| PUSHRELEASE2 | BOUTON PESÉ-RELACHÉ  | STATE_ON     | LED ÉTEINTE    |  |
| STATE_ON     | BOUTON NON-APPUYÉ    | STATE_OFF    | LED VERTE (2s) |  |
|              |                      |              |                |  |
+--------------+----------------------+--------------+----------------+--+
*/

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>


const uint8_t DELAY_DEBOUNCE_BUTTON = 10;
const uint16_t LED_ON_DURATION = 2000;
bool released = true;

void initialize()
{

  DDRA |=  (1 << PA0) | (1 << PA1);
  DDRD &= ~(1 << PD2);
}

void delGreen()
{
  PORTA |= (1 << PA1);
  PORTA &= ~(1 << PA0);
}

void delOff() 
{
    PORTA &= ~(1 << PA0);
    PORTA &= ~(1 << PA1);
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
    STATE_OFF,
    STATE_PUSHRELEASE1,
    STATE_PUSHRELEASE2,
    STATE_ON
};

int main() {
    initialize();
    State currentState = State::STATE_OFF;


    while (1) {
        switch (currentState) {
            case State::STATE_OFF:
              
               delOff();
                
                if (buttonPressed() && released) {
                  released = false;
                    currentState = State::STATE_PUSHRELEASE1;
                  
                }
              break;

            case State::STATE_PUSHRELEASE1:
                if (!buttonPressed()){
                  released = true;}
                
                delOff();
                if (buttonPressed() && released) {
                  released = false;
                  currentState = State::STATE_PUSHRELEASE2;   
                }
                break;

            case State::STATE_PUSHRELEASE2:
                if (!buttonPressed()){
                  released = true;}
                
                
                delOff();
                if (buttonPressed() && released) {
                    released = false;
                    currentState = State::STATE_ON;
                }
              break;

            case State::STATE_ON:
                
                if (!buttonPressed()){
                  released = true;
                  delGreen();
                  _delay_ms(LED_ON_DURATION);
                  currentState = State::STATE_OFF;
                }
                

              break;

            default:
                currentState = State::STATE_OFF;
                break;
        }
    }

    return 0;
}

