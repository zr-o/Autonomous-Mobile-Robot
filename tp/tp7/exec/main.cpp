#define F_CPU 8000000UL

#include <util/delay.h>
#include "timer1.h"
#include "button.h"
#include "led.h"
#include "ports.h"


#define DELAI_REBOND_MS 10

volatile bool gBouton = false;
volatile bool gExpiredTimer = false;

ISR(INT0_vect)
{
    gBouton = true;

    _delay_ms(DELAI_REBOND_MS);

    if (!(PIND & (1 << PD2)))
    {
        gBouton = 0;
    }
}

ISR(TIMER1_COMPA_vect)
{

    gExpiredTimer = true;
    TIMSK1 &= ~(1 << OCIE1A);
}

int main()
{
 
    Ports portsUtility;
    //Ports* portsUtilityPtr = &portsUtility;

    Led led(&portsUtility, Port::C, Pin::N7, Pin::N8);

    led.lightUp(Color::GREEN);

    _delay_ms(2000);

    led.lightUp(Color::RED);

    _delay_ms(2000);

    led.lightUp(Color::OFF);



}