#include "timer1.h"

Timer1::Timer1(TimerMode mode) : mode_(mode) {

    setTimerMode(mode);
    setPrescaler(Prescaler::PRESCALER_1);
}


Timer1::~Timer1() {
    setPrescaler(Prescaler::NONE);
}

void Timer1::setPrescaler(Prescaler value)
{
    switch (value)
    {
    case Prescaler::NONE:
        TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
        break;
    case Prescaler::PRESCALER_1:
        TCCR1B &= ~((1 << CS12) | (1 << CS11));
        TCCR1B |=  (1 << CS10);
        break;
    
    case Prescaler::PRESCALER_8:
        TCCR1B &= ~(1 << CS10 | 1 << CS12);
        TCCR1B |= (1 << CS11);
        break;

    case Prescaler::PRESCALER_64:
        TCCR1B &= ~(1 << CS12);
        TCCR1B |= (1 << CS10 | 1 << CS11);
        break;

    case Prescaler::PRESCALER_256:
        TCCR1B &= ~(1 << CS10 | 1 << CS11);
        TCCR1B |= (1 << CS12);
        break;

    case Prescaler::PRESCALER_1024:
        TCCR1B &= ~(1 << CS11);
        TCCR1B |= (1 << CS10 | 1 << CS12);
        break;
    default:
        break;
    }
}

void Timer1::setTimerMode(TimerMode mode)
{
    switch (mode)
    {
        case TimerMode::NORMAL:
            TCCR1A &= ~((1 << WGM11) | (1 << WG10));
            TCCR1B &= ~(1 << WG12);
            break;

        case TimerMode::CTC:

            TCCR1A &= ~((1 << WGM11) | (1 << WG10));
            TCCR1B |= (1 << WGM12);
            break;

        case TimerMode::PWM:

            TCCR1A |= (1 << WGM10);
            TCCR1A &= ~(1 << WG11);
            TCCR1B &= ~(1 << WGM12);
            TCCR1C = 0;
            break;

        default:
            break;
    }
}

void Timer1::setCompareOutputMode(OutputComparePin pin, CompareOutputMode mode) {

    uint8_t compareOutput0 = ((pin == OutputComparePin::A) ? COM1A0 : COM1B0);
    uint8_t compareOutput1= ((pin == OutputComparePin::A) ? COM1A1 : COM1B1);

    switch (mode) {

        case CompareOutputMode::CLEAR:

            TCCR1A &= ~(1 << compareOutput0);
            TCCR1A |= (1 << compareOutput1);
            break;

        case CompareOutputMode::NORMAL:

            TCCR1A &= ~((1 << compareOutput0 ) | (1 << compareOutput1));
            break;

        case CompareOutputMode::TOGGLE:

            TCCR1A &= ~(1 << compareOutput1);
            TCCR1A |= (1 << compareOutput0);
            break;
        case CompareOutputMode::SET:

            TCCR1A |= (1 << compareOutput0) | (1 << compareOutput1);
        break;

        default:
            break;
    }   

}

void Timer1::setCompareValue(OutputComparePin pin, uint8_t value) {

    switch (pin)
    {
        case OutputComparePin::A:
            
            OCR1A = value;
            break;

        case OutputComparePin::B:
            
            OCR1B = value;
            break;

        case OutputComparePin::BOTH:
            
            OCR1A = value;
            OCR1B = value;
            break;
        
        default:
            break;
    }
}

void Timer1::setTimerValue(uint16_t value) {

    cli();
    TCNT1 = value;
    sei();

}

void Timer1::allowInterrupts(OutputComparePin pin, bool enable){

    cli();

    if(enable) {

        switch (pin) {

            case OutputComparePin::A:
                
                TIMSK1 &= ~(1 << OCIE1B);
                TIMSK1 |= (1 << OCIE1A);
                break;


            case OutputComparePin::B:
                
                TIMSK1 &= ~(1 << OCIE1A);
                TIMSK1 |= (1 << OCIE1B);
                break;

            case OutputComparePin::BOTH:
                
                TIMSK1 |= (1 << OCIE1A | 1 << OCIE1B);
                break;

            default:
                break;
        }

    }

    else {

        TIMSK1 &= ~(1 << OCIE1A | 1 << OCIE1B);

    }


    sei();


}

void Timer1::delayMs(uint16_t delay) {



    setTimerValue();
    setPrescaler();
    setCompareValue

}