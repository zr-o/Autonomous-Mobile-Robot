#include "wheels.h"

Wheels::Wheels(Timer1 *delayTimer, Timer2 *pwmTimer, Ports *portsUtility)
{
    pwmTimer_ = pwmTimer;
    delayTimer_ = delayTimer;
    portsUtility_ = portsUtility;

    portsUtility_->setPinMode(PortMode::WRITE, Port::D, Pin::N8);
    portsUtility_->setPinMode(PortMode::WRITE, Port::D, Pin::N7);
    portsUtility_->setPinMode(PortMode::WRITE, Port::D, Pin::N6);
    portsUtility_->setPinMode(PortMode::WRITE, Port::D, Pin::N5);

    pwmTimer_->setTimerMode(TimerMode::PWM);
    pwmTimer_->setCompareOutputModeA(CompareOutputMode::CLEAR);
    pwmTimer_->setCompareOutputModeB(CompareOutputMode::CLEAR);
    pwmTimer_->setTimerValue(0);
    pwmTimer_->setPrescaler(Prescaler::PRESCALER_8);
}

void Wheels::rotateLeftWheel(uint8_t pourcentage, Direction direction)
{
    const uint8_t valeurMax8Bits = 255;
    const uint8_t divisionPourcentage = 100;

    uint16_t resultatCalcul = ((pourcentage * valeurMax8Bits) / divisionPourcentage);
    pwmTimer_->setCompareValue(OutputComparePin::A, uint8_t(resultatCalcul));

    switch (direction)
    {
    case Direction::FORWARD:
        portsUtility_->writePin(Port::D, Pin::N6, false);

    case Direction::BACKWARDS:
        portsUtility_->writePin(Port::D, Pin::N6, true);
    }
}

void Wheels::rotateRightWheel(uint8_t pourcentage, Direction direction)
{
    const uint8_t valeurMax8Bits = 255;
    const uint8_t divisionPourcentage = 100;
    uint16_t resultatCalcul = ((pourcentage * valeurMax8Bits) / divisionPourcentage);

    pwmTimer_->setCompareValue(OutputComparePin::B, uint8_t(resultatCalcul));

    switch (direction)
    {
    case Direction::FORWARD:
        portsUtility_->writePin(Port::D, Pin::N5, false);

    case Direction::BACKWARDS:
        portsUtility_->writePin(Port::D, Pin::N5, true);
    }
}
