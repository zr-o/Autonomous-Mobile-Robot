#include "timer0.h"

Timer0::Timer0()
{
    setTimerMode(TimerMode::NORMAL);
    setPrescaler(Prescaler::PRESCALER_1);
    setCompareOutputModeA(CompareOutputMode::NORMAL);
    setCompareOutputModeB(CompareOutputMode::NORMAL);
    allowInterrupts(OutputComparePin::NONE);
}

void Timer0::setPrescaler(Prescaler value)
{
    cli();

    switch (value)
    {
    case Prescaler::NONE:
        TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00));
        break;

    case Prescaler::PRESCALER_1:
        TCCR0B &= ~((1 << CS02) | (1 << CS01));
        TCCR0B |= (1 << CS00);
        break;

    case Prescaler::PRESCALER_8:
        TCCR0B &= ~((1 << CS00) | (1 << CS02));
        TCCR0B |= (1 << CS01);
        break;

    case Prescaler::PRESCALER_64:
        TCCR0B &= ~(1 << CS02);
        TCCR0B |= (1 << CS00) | (1 << CS01);
        break;

    case Prescaler::PRESCALER_256:
        TCCR0B &= ~((1 << CS00) | (1 << CS11));
        TCCR0B |= (1 << CS02);
        break;

    case Prescaler::PRESCALER_1024:
        TCCR0B &= ~(1 << CS01);
        TCCR0B |= (1 << CS00) | (1 << CS02);
        break;
    }

    sei();
}

void Timer0::setTimerMode(TimerMode mode)
{
    cli();

    switch (mode)
    {
    case TimerMode::NORMAL:
        TCCR0A &= ~((1 << WGM01) | (1 << WGM00));
        TCCR0B &= ~(1 << WGM02);
        TCCR0B &= ~((1 << FOC0A) | (1 << FOC0B));
        break;

    case TimerMode::CTC:
        TCCR0A &= ~(1 << WGM00);
        TCCR0A |= (1 << WGM01);
        TCCR0B &= ~(1 << WGM02);
        TCCR0B &= ~((1 << FOC0A) | (1 << FOC0B));
        break;

    case TimerMode::PWM:
        TCCR0A |= (1 << WGM00);
        TCCR0A &= ~(1 << WGM01);
        TCCR0B &= ~(1 << WGM02);
        TCCR0B &= ~((1 << FOC0A) | (1 << FOC0B));
        break;
    }

    sei();
}

void Timer0::setCompareOutputModeA(CompareOutputMode mode)
{
    cli();

    switch (mode)
    {
    case CompareOutputMode::CLEAR:
        TCCR0A &= ~(1 << COM0A0);
        TCCR0A |= (1 << COM0A1);
        break;

    case CompareOutputMode::NORMAL:
        TCCR0A &= ~((1 << COM0A0) | (1 << COM0A1));
        break;

    case CompareOutputMode::TOGGLE:
        TCCR0A &= ~(1 << COM0A1);
        TCCR0A |= (1 << COM0A0);
        break;

    case CompareOutputMode::SET:
        TCCR0A |= (1 << COM0A0) | (1 << COM0A1);
        break;
    }

    sei();
}

void Timer0::setCompareOutputModeB(CompareOutputMode mode)
{
    cli();

    switch (mode)
    {
    case CompareOutputMode::CLEAR:
        TCCR0A &= ~(1 << COM0B0);
        TCCR0A |= (1 << COM0B1);
        break;

    case CompareOutputMode::NORMAL:
        TCCR0A &= ~((1 << COM0B0) | (1 << COM0B1));
        break;

    case CompareOutputMode::TOGGLE:
        TCCR0A &= ~(1 << COM0B1);
        TCCR0A |= (1 << COM0B0);
        break;

    case CompareOutputMode::SET:
        TCCR0A |= (1 << COM0B0) | (1 << COM0B1);
        break;
    }

    sei();
}

void Timer0::setCompareValue(OutputComparePin pin, uint8_t value)
{
    cli();

    switch (pin)
    {
    case OutputComparePin::A:
        OCR0A = value;
        break;

    case OutputComparePin::B:
        OCR0B = value;
        break;

    case OutputComparePin::BOTH:
        OCR0A = value;
        OCR0B = value;
        break;

    case OutputComparePin::NONE:
        break;
    }

    sei();
}

void Timer0::setTimerValue(uint8_t value)
{
    cli();

    TCNT0 = value;

    sei();
}

void Timer0::allowInterrupts(OutputComparePin pin)
{
    cli();

    switch (pin)
    {
    case OutputComparePin::A:
        TIMSK0 &= ~(1 << OCIE0B);
        TIMSK0 |= (1 << OCIE0A);
        break;

    case OutputComparePin::B:
        TIMSK0 &= ~(1 << OCIE0A);
        TIMSK0 |= (1 << OCIE0B);
        break;

    case OutputComparePin::BOTH:
        TIMSK0 |= (1 << OCIE0A | 1 << OCIE0B);
        break;

    case OutputComparePin::NONE:
        TIMSK0 &= ~((1 << OCIE0A) | (1 << OCIE0B));
        break;
    }

    sei();
}

