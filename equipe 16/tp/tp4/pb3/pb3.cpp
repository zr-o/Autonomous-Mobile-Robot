
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define DELAI_2_SECONDE_MS 2000


void ajustementPwm(uint8_t pourcentage)
{


    TCNT1 = 0x00;

    OCR1A = pourcentage;

    OCR1B = pourcentage;

    TCCR1A = (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1);

    TCCR1B = (1 << CS11);

    TCCR1C = 0;

    
}

int main()
{

    DDRD |= (1 << PD4) | (1 << PD5);


    ajustementPwm(255);
    _delay_ms(DELAI_2_SECONDE_MS);
    ajustementPwm(192);
    _delay_ms(DELAI_2_SECONDE_MS);
    ajustementPwm(128);
    _delay_ms(DELAI_2_SECONDE_MS);
    ajustementPwm(64);
    _delay_ms(DELAI_2_SECONDE_MS);
    ajustementPwm(0);

}



