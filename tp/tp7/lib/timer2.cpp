#include "timer2.h"

Timer2::Timer2(TimerMode mode)
{
    setTimerMode(mode);
    setPrescaler(Prescaler::PRESCALER_1);
    setCompareOutputModeA(CompareOutputMode::NORMAL);
    setCompareOutputModeB(CompareOutputMode::NORMAL);
    allowInterrupts(OutputComparePin::NONE);
}

void Timer2::setPrescaler(Prescaler value)
{
    cli();

    switch (value)
    {
    case Prescaler::NONE:
        TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20));
        break;

    case Prescaler::PRESCALER_1:
        TCCR2B &= ~((1 << CS22) | (1 << CS21));
        TCCR2B |= (1 << CS20);
        break;

    case Prescaler::PRESCALER_8:
        TCCR2B &= ~((1 << CS20) | (1 << CS22));
        TCCR2B |= (1 << CS21);
        break;

    case Prescaler::PRESCALER_64:
        TCCR2B &= ~(1 << CS22);
        TCCR2B |= (1 << CS20) | (1 << CS21);
        break;

    case Prescaler::PRESCALER_256:
        TCCR2B &= ~((1 << CS20) | (1 << CS21));
        TCCR2B |= (1 << CS22);
        break;

    case Prescaler::PRESCALER_1024:
        TCCR2B &= ~(1 << CS21);
        TCCR2B |= (1 << CS20) | (1 << CS22);
        break;
    }

    sei();
}

void Timer2::setTimerMode(TimerMode mode)
{
    cli();

    switch (mode)
    {
    case TimerMode::NORMAL:
        TCCR2A &= ~((1 << WGM21) | (1 << WGM20));
        TCCR2B &= ~(1 << WGM22);
        TCCR2B &= ~((1 << FOC2A) | (1 << FOC2B));
        break;

    case TimerMode::CTC:
        TCCR2A &= ~((1 << WGM21) | (1 << WGM20));
        TCCR2B |= (1 << WGM22);
        TCCR2B &= ~((1 << FOC2A) | (1 << FOC2B));
        break;

    case TimerMode::PWM:
        TCCR2A |= (1 << WGM20);
        TCCR2A &= ~(1 << WGM21);
        TCCR2B &= ~(1 << WGM22);
        TCCR2B &= ~((1 << FOC2A) | (1 << FOC2B));
        break;
    }

    sei();
}

void Timer2::setCompareOutputModeA(CompareOutputMode mode)
{
    cli();

    switch (mode)
    {
    case CompareOutputMode::CLEAR:
        TCCR2A &= ~(1 << COM2A0);
        TCCR2A |= (1 << COM2A1);
        break;

    case CompareOutputMode::NORMAL:
        TCCR2A &= ~((1 << COM2A0) | (1 << COM2A1));
        break;

    case CompareOutputMode::TOGGLE:
        TCCR2A &= ~(1 << COM2A1);
        TCCR2A |= (1 << COM2A0);
        break;

    case CompareOutputMode::SET:
        TCCR2A |= (1 << COM2A0) | (1 << COM2A1);
        break;
    }

    sei();
}

void Timer2::setCompareOutputModeB(CompareOutputMode mode)
{
    cli();

    switch (mode)
    {
    case CompareOutputMode::CLEAR:
        TCCR2A &= ~(1 << COM2B0);
        TCCR2A |= (1 << COM2B1);
        break;

    case CompareOutputMode::NORMAL:
        TCCR2A &= ~((1 << COM2B0) | (1 << COM2B1));
        break;

    case CompareOutputMode::TOGGLE:
        TCCR2A &= ~(1 << COM2B1);
        TCCR2A |= (1 << COM2B0);
        break;

    case CompareOutputMode::SET:
        TCCR2A |= (1 << COM2B0) | (1 << COM2B1);
        break;
    }

    sei();
}

void Timer2::setCompareValue(OutputComparePin pin, uint8_t value)
{
    cli();

    switch (pin)
    {
    case OutputComparePin::A:
        OCR2A = value;
        break;

    case OutputComparePin::B:
        OCR2B = value;
        break;

    case OutputComparePin::BOTH:
        OCR2A = value;
        OCR2B = value;
        break;

    case OutputComparePin::NONE:
        break;
    }

    sei();
}

void Timer2::setTimerValue(uint8_t value)
{
    cli();

    TCNT2 = value;

    sei();
}

void Timer2::allowInterrupts(OutputComparePin pin)
{
    cli();

    switch (pin)
    {
    case OutputComparePin::A:
        TIMSK2 &= ~(1 << OCIE2B);
        TIMSK2 |= (1 << OCIE2A);
        break;

    case OutputComparePin::B:
        TIMSK2 &= ~(1 << OCIE2A);
        TIMSK2 |= (1 << OCIE2B);
        break;

    case OutputComparePin::BOTH:
        TIMSK2 |= (1 << OCIE2A | 1 << OCIE2B);
        break;

    case OutputComparePin::NONE:
        TIMSK2 &= ~(1 << OCIE2A | 1 << OCIE2B);
        break;
    }

    sei();
}
