#include "led.h"

Led::Led(Ports *portsUtility, Port port, Pin pinA, Pin pinB)
{
    pinA_ = pinA;
    pinB_ = pinB;
    port_ = port;
    portsUtility_ = portsUtility;

    portsUtility_->setPinMode(PortMode::WRITE, port_, pinA_);
    portsUtility_->setPinMode(PortMode::WRITE, port_, pinB);
}

void Led::lightUp(Color color)
{
    switch (color)
    {
    case Color::GREEN:
        portsUtility_->writePin(port_, pinA_, true);
        portsUtility_->writePin(port_, pinB_, false);

    case Color::RED:
        portsUtility_->writePin(port_, pinA_, false);
        portsUtility_->writePin(port_, pinB_, true);

    case Color::OFF:
        portsUtility_->writePin(port_, pinA_, false);
        portsUtility_->writePin(port_, pinA_, false);
    }
}

Led::~Led()
{
    portsUtility_->setPinMode(PortMode::READ, port_, pinA_);
    portsUtility_->setPinMode(PortMode::READ, port_, pinB_);
}
