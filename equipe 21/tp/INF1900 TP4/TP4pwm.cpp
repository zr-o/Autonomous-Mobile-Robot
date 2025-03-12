#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

const uint8_t DELAY_RED_TO_GREEN = 3;
const uint8_t DELAY_GREEN_TO_RED = 5;
const uint8_t DELAY_DEBOUNCE_BUTTON = 30;
const uint16_t DUREE = 7812;


void initialize()
{
    DDRD |= (1 << PD4) | (1 << PD5);
}

/*void moteurOn()
{
  PORTD |= (1 << PD4);
  PORTD &= ~(1 << PD2);
  PORTD |= (1 << PD5);
  PORTD &= ~(1 << PD3);
}

void moteurOff()
{
    PORTA &= ~(1 << PA0);
    PORTA &= ~(1 << PA1);
}*/


void ajustementPwm (uint8_t valA, uint8_t valB) {

    // mise à un des sorties OC1A et OC1B sur comparaison
    
    // réussie en mode PWM 8 bits, phase correcte
    
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5
    
    // page 130 de la description technique du ATmega324PA)
    
    OCR1A = valA;
    
    OCR1B = valB;
    
    
    
    // division d'horloge par 8 - implique une fréquence de PWM fixe
    
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B = (1 << CS11);  // Division d'horloge par 8 (CS11 = 1)
    
    TCCR1C = 0;
    
    }
    
    
int main() {
    initialize();  // Initialisation des interruptions et ports

    while(1) {
        ajustementPwm(0x00, 0x00);
        _delay_ms(2000);
        ajustementPwm(0x40, 0x40);
        _delay_ms(2000);
        ajustementPwm(0x80, 0x80);
        _delay_ms(2000);
        ajustementPwm(0xC0, 0xC0);
        _delay_ms(2000);
        ajustementPwm(0xFF, 0xFF);
        _delay_ms(2000);
    }
}