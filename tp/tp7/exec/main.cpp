#define F_CPU 8000000UL

#include <util/delay.h>
#include "timer1.h"
#include "button.h"
#include "led.h"
#include "ports.h"
#include "debug.h"
#include "wheels.h"

#define DELAI_REBOND_MS 10
#define DELAI_5_SECONDES_CALCUL 39062

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
Timer1 delayTimer;
delayTimer.initializeTimerForDelays(gExpiredTimer);

Timer2 pwmTimer;



Wheels wheels = Wheels(&delayTimer, &pwmTimer);

wheels.goForward(75, DELAI_5_SECONDES_CALCUL);
wheels.goLeft(75, DELAI_5_SECONDES_CALCUL);
wheels.goRight(75, DELAI_5_SECONDES_CALCUL);
wheels.goBackwards(75, DELAI_5_SECONDES_CALCUL);
}