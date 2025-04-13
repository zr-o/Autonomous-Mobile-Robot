#include "timer1.h"

Timer1::Timer1()
{    
}

void Timer1::setPrescaler(Prescaler value)
{
    cli();

    switch (value)
    {
    case Prescaler::NONE:
        TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
        break;

    case Prescaler::PRESCALER_1:
        TCCR1B &= ~((1 << CS12) | (1 << CS11));
        TCCR1B |= (1 << CS10);
        break;

    case Prescaler::PRESCALER_8:
        TCCR1B &= ~((1 << CS10) | (1 << CS12));
        TCCR1B |= (1 << CS11);
        break;

    case Prescaler::PRESCALER_64:
        TCCR1B &= ~(1 << CS12);
        TCCR1B |= (1 << CS10) | (1 << CS11);
        break;

    case Prescaler::PRESCALER_256:
        TCCR1B &= ~((1 << CS10) | (1 << CS11));
        TCCR1B |= (1 << CS12);
        break;

    case Prescaler::PRESCALER_1024:
        TCCR1B &= ~(1 << CS11);
        TCCR1B |= (1 << CS10) | (1 << CS12);
        break;
    }

    sei();
}

void Timer1::setTimerMode(TimerMode mode)
{
    cli();

    switch (mode)
    {
    case TimerMode::NORMAL:
        TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
        TCCR1B &= ~(1 << WGM12);
        TCCR1C = 0;
        break;

    case TimerMode::CTC:
        TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
        TCCR1B |= (1 << WGM12);
        TCCR1C = 0;
        break;

    case TimerMode::PWM:
        TCCR1A |= (1 << WGM10);
        TCCR1A &= ~(1 << WGM11);
        TCCR1B &= ~(1 << WGM12);
        TCCR1C = 0;
        break;
    }

    sei();
}

void Timer1::setCompareOutputModeA(CompareOutputMode mode)
{
    cli();

    switch (mode)
    {
    case CompareOutputMode::CLEAR:
        TCCR1A &= ~(1 << COM1A0);
        TCCR1A |= (1 << COM1A1);
        break;

    case CompareOutputMode::NORMAL:
        TCCR1A &= ~((1 << COM1A0) | (1 << COM1A1));
        break;

    case CompareOutputMode::TOGGLE:
        TCCR1A &= ~(1 << COM1A1);
        TCCR1A |= (1 << COM1A0);
        break;

    case CompareOutputMode::SET:
        TCCR1A |= (1 << COM1A0) | (1 << COM1A1);
        break;
    }

    sei();
}

void Timer1::setCompareOutputModeB(CompareOutputMode mode)
{
    cli();

    switch (mode)
    {
    case CompareOutputMode::CLEAR:
        TCCR1A &= ~(1 << COM1B0);
        TCCR1A |= (1 << COM1B1);
        break;

    case CompareOutputMode::NORMAL:
        TCCR1A &= ~((1 << COM1B0) | (1 << COM1B1));
        break;

    case CompareOutputMode::TOGGLE:
        TCCR1A &= ~(1 << COM1B1);
        TCCR1A |= (1 << COM1B0);
        break;

    case CompareOutputMode::SET:
        TCCR1A |= (1 << COM1B0) | (1 << COM1B1);
        break;
    }

    sei();
}

void Timer1::setCompareValue(OutputComparePin pin, uint16_t value)
{
    cli();

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

    case OutputComparePin::NONE:
        break;
    }

    sei();
}

void Timer1::setTimerValue(uint16_t value)
{
    cli();

    TCNT1 = value;

    sei();
}

void Timer1::allowInterrupts(OutputComparePin pin)
{
    cli();

    switch (pin)
    {
    case OutputComparePin::A:
        TIMSK1 |= (1 << OCIE1A);
        break;

    case OutputComparePin::B:
        TIMSK1 |= (1 << OCIE1B);
        break;

    case OutputComparePin::BOTH:
        TIMSK1 |= (1 << OCIE1A | 1 << OCIE1B);
        break;

    case OutputComparePin::NONE:
        TIMSK1 &= ~(1 << OCIE1A | 1 << OCIE1B);
        break;
    }

    sei();
}

void Timer1::disallowInterrupts(OutputComparePin pin)
{
    cli();

    switch (pin)
    {
    case OutputComparePin::A:
        TIMSK1 &= ~(1 << OCIE1A);
        break;

    case OutputComparePin::B:
        TIMSK1 &= ~(1 << OCIE1B);
        break;

    case OutputComparePin::BOTH:
        TIMSK1 &= ~((1 << OCIE1A) | (1 << OCIE1B));
        break;

    default:
        break;
    }

    sei();
}

void Timer1::initializeTimerForDelays()
{
    cli();

    setPrescaler(Prescaler::PRESCALER_1024);
    setTimerMode(TimerMode::CTC);

    sei();
}
void Timer1::startTimer(OutputComparePin pin, uint16_t calculatedDelay)
{
    switch (pin)
    {
    case OutputComparePin::A:
        setTimerValue(0);
        setCompareValue(OutputComparePin::A, calculatedDelay);
        TIFR1 |= (1 << OCF1A);
        allowInterrupts(OutputComparePin::A);
        break;

    case OutputComparePin::B:
        setTimerValue(0);
        setCompareValue(OutputComparePin::B, calculatedDelay);
        TIFR1 |= (1 << OCF1B);
        allowInterrupts(OutputComparePin::B);
        break;

    case OutputComparePin::BOTH:
        setTimerValue(0);
        setCompareValue(OutputComparePin::BOTH, calculatedDelay);
        TIFR1 |= (1 << OCF1A) | (1 << OCF1B)
        allowInterrupts(OutputComparePin::BOTH);
        break;

    default:
        break;
    }
}