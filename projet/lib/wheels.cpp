#include "wheels.h"

Wheels::Wheels(Timer2 &pwmTimer) : pwmTimer_(pwmTimer)
{

    Ports::setPinMode(PortMode::WRITE, Port::D, Pin::N8);
    Ports::setPinMode(PortMode::WRITE, Port::D, Pin::N7);
    Ports::setPinMode(PortMode::WRITE, Port::D, Pin::N6);
    Ports::setPinMode(PortMode::WRITE, Port::D, Pin::N5);

    pwmTimer_.setTimerMode(TimerMode::PWM);
    pwmTimer_.setCompareOutputModeA(CompareOutputMode::CLEAR);
    pwmTimer_.setCompareOutputModeB(CompareOutputMode::CLEAR);
    pwmTimer_.setTimerValue(0);
    pwmTimer_.setCompareValue(OutputComparePin::A, 0);
    pwmTimer_.setCompareValue(OutputComparePin::B, 0);
    pwmTimer_.setPrescaler(Prescaler::PRESCALER_8);
}

void Wheels::setSpeedLeft(uint8_t percentage, Direction direction)
{
    pwmTimer_.setCompareValue(OutputComparePin::A, percentage);

    switch (direction)
    {
    case Direction::FORWARD:
        Ports::writePin(Port::D, Pin::N6, false);
        break;

    case Direction::BACKWARDS:
        Ports::writePin(Port::D, Pin::N6, true);
        break;
    }
}

void Wheels::setSpeedRight(uint8_t percentage, Direction direction)
{
    pwmTimer_.setCompareValue(OutputComparePin::B, percentage);

    switch (direction)
    {
    case Direction::FORWARD:
        Ports::writePin(Port::D, Pin::N5, false);
        break;

    case Direction::BACKWARDS:
        Ports::writePin(Port::D, Pin::N5, true);
        break;
    }
}

void Wheels::stop()
{
    setSpeedLeft(0, Direction::FORWARD);
    setSpeedRight(0, Direction::FORWARD);
}

void Wheels::goForward(uint8_t percentage, uint16_t delay)
{
    //Boost
    setSpeedLeft(255, Direction::FORWARD);
    setSpeedRight(255, Direction::FORWARD);
    _delay_ms(50);

    setSpeedLeft(percentage, Direction::FORWARD);
    setSpeedRight(percentage, Direction::FORWARD);

    variableDelayMs(delay);

    stop();
}

void Wheels::goForward(uint8_t percentage)
{
    setSpeedLeft(percentage, Direction::FORWARD);
    setSpeedRight(percentage, Direction::FORWARD);
}

void Wheels::goBackwards(uint8_t percentage, uint16_t delay)
{
    //Boost
     setSpeedLeft(255, Direction::BACKWARDS);
    setSpeedRight(255, Direction::BACKWARDS);
    _delay_ms(50);

    setSpeedLeft(percentage, Direction::BACKWARDS);
    setSpeedRight(percentage, Direction::BACKWARDS);

    variableDelayMs(delay);

    stop();
}

void Wheels::goBackwards(uint8_t percentage)
{
    setSpeedLeft(percentage, Direction::BACKWARDS);
    setSpeedRight(percentage, Direction::BACKWARDS);
}

void Wheels::goLeft(uint8_t percentage, uint16_t delay)
{
    //Boost
    setSpeedLeft(0, Direction::FORWARD);
    setSpeedRight(255, Direction::FORWARD);
    _delay_ms(50);

    setSpeedLeft(0, Direction::FORWARD);
    setSpeedRight(percentage, Direction::FORWARD);

    variableDelayMs(delay);

    stop();
}

void Wheels::goLeft(uint8_t percentage)
{
    setSpeedLeft(0, Direction::FORWARD);
    setSpeedRight(percentage, Direction::FORWARD);
}

void Wheels::goRight(uint8_t percentage, uint16_t delay)
{
    setSpeedLeft(255, Direction::FORWARD);
    setSpeedRight(0, Direction::FORWARD);
    _delay_ms(50);

    setSpeedLeft(percentage, Direction::FORWARD);
    setSpeedRight(0, Direction::FORWARD);

    variableDelayMs(delay);

    stop();
}

void Wheels::goRight(uint8_t percentage)
{
    setSpeedLeft(percentage, Direction::FORWARD);
    setSpeedRight(0, Direction::FORWARD);
}

void Wheels::stop(uint16_t delay)
{
    stop();

    variableDelayMs(delay);

    stop();
}
