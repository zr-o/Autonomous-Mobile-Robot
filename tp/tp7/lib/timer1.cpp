#include "timer1.h"

Timer1::setPrescaler(Prescaler value)
{
    switch (value)
    {
    case Prescaler::NONE:
        TCCR1B &= ~((CS12 << 1) | (CS11 << 1) | (CS10 << 1));
        break;
    case Prescaler::PRESCALER_1:
    

    
    }
}