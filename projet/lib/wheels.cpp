#include "wheels.h"

Wheels::Wheels(Timer2 *pwmTimer) : pwmTimer_(pwmTimer)
{

    Ports::setPinMode(PortMode::WRITE, Port::D, Pin::N8);
    Ports::setPinMode(PortMode::WRITE, Port::D, Pin::N7);
    Ports::setPinMode(PortMode::WRITE, Port::D, Pin::N6);
    Ports::setPinMode(PortMode::WRITE, Port::D, Pin::N5);

    pwmTimer_->setTimerMode(TimerMode::PWM);
    pwmTimer_->setCompareOutputModeA(CompareOutputMode::CLEAR);
    pwmTimer_->setCompareOutputModeB(CompareOutputMode::CLEAR);
    pwmTimer_->setTimerValue(0);
    pwmTimer_->setCompareValue(OutputComparePin::A, 0);
    pwmTimer_->setCompareValue(OutputComparePin::B, 0);
    pwmTimer_->setPrescaler(Prescaler::PRESCALER_8);
}

void Wheels::rotateLeftWheel(uint8_t percentage, Direction direction)
{

    uint16_t result = ((percentage * BITS_8_MAX_VALUE) / PERCENTAGE_DIVIDOR);
    pwmTimer_->setCompareValue(OutputComparePin::A, uint8_t(result));

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

void Wheels::rotateRightWheel(uint8_t percentage, Direction direction)
{

    uint16_t result = ((percentage * BITS_8_MAX_VALUE) / PERCENTAGE_DIVIDOR);
    pwmTimer_->setCompareValue(OutputComparePin::B, uint8_t(result));

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
    rotateLeftWheel(0, Direction::FORWARD);
    rotateRightWheel(0, Direction::FORWARD);
}

void Wheels::goForward(uint8_t percentage, uint16_t delay)
{
    rotateLeftWheel(percentage, Direction::FORWARD);
    rotateRightWheel(percentage, Direction::FORWARD);

    variableDelayMs(delay);

    stop();
}

void Wheels::goForward(uint8_t percentage)
{
    rotateLeftWheel(percentage, Direction::FORWARD);
    rotateRightWheel(percentage, Direction::FORWARD);
}

void Wheels::goBackwards(uint8_t percentage, uint16_t delay)
{
    rotateLeftWheel(percentage, Direction::BACKWARDS);
    rotateRightWheel(percentage, Direction::BACKWARDS);

    variableDelayMs(delay);

    stop();
}

void Wheels::goBackwards(uint8_t percentage)
{
    rotateLeftWheel(percentage, Direction::BACKWARDS);
    rotateRightWheel(percentage, Direction::BACKWARDS);
}

void Wheels::goLeft(uint8_t percentage, uint16_t delay)
{
    rotateLeftWheel(0, Direction::FORWARD);
    rotateRightWheel(percentage, Direction::FORWARD);

    variableDelayMs(delay);

    stop();
}

void Wheels::goLeft(uint8_t percentage)
{
    rotateLeftWheel(0, Direction::FORWARD);
    rotateRightWheel(percentage, Direction::FORWARD);
}

void Wheels::goRight(uint8_t percentage, uint16_t delay)
{
    rotateLeftWheel(percentage, Direction::FORWARD);
    rotateRightWheel(0, Direction::FORWARD);

    variableDelayMs(delay);

    stop();
}

void Wheels::goRight(uint8_t percentage)
{
    rotateLeftWheel(percentage, Direction::FORWARD);
    rotateRightWheel(0, Direction::FORWARD);
}
