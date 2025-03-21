#define F_CPU 8000000UL

#include <util/delay.h>
#include "timer1.h"
#include "button.h"
#include "led.h"
#include "ports.h"
#include "debug.h"

#define DELAI_REBOND_MS 10

volatile bool gButton = false;
volatile bool gExpiredTimer = false;

ISR(INT0_vect)
{
    gButton = true;

    _delay_ms(DELAI_REBOND_MS);

    if (!(PIND & (1 << PD2)))
    {
        gButton = 0;
    }
}

ISR(TIMER1_COMPA_vect)
{

    gExpiredTimer = true;
    TIMSK1 &= ~(1 << OCIE1A);
}

int main()
{

    while (true)
    {
        uint16_t x = 50000;
        Debug::display(x);

        _delay_ms(1000);
    }
}