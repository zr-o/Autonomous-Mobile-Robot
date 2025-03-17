#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "../lib/button.h"
#include "../lib/can.h"
#include "../lib/led.h"
#include "../lib/memoire_24.h"
#include "../lib/rs232.h"
#include "../lib/timer0.h"
#include "../lib/timer1.h"
#include "../lib/timer2.h"

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
    Timer1 timer1(TimerMode::CTC);
    timer1.initializeTimerForDelays(gExpiredTimer);

    Ports portsUtility;

    Led led(&portsUtility, Port::A, Pin::N1, Pin::N2);

    Button button = Button(ButtonType::MOTHERBOARD, &gBouton);

    if (button.isPressed())
    {
        led.lightUp(Color::RED);
    }
    else
    {
        led.lightUp(Color::GREEN);
    }
}