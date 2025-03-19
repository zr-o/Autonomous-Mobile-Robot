#include "led.h"

Led::Led(Ports *portsUtility, Port port, Pin pinA, Pin pinB) : port_(port), pinA_(pinA), pinB_(pinB), portsUtility_(portsUtility)
{
    portsUtility_->setPinMode(PortMode::WRITE, port_, pinA_);
    portsUtility_->setPinMode(PortMode::WRITE, port_, pinB_);
}

void Led::lightUp(Color color)
{
    switch (color)
    {
    case Color::GREEN:
        portsUtility_->writePin(port_, pinA_, true);
        portsUtility_->writePin(port_, pinB_, false);
        break;

    case Color::RED:
        portsUtility_->writePin(port_, pinA_, false);
        portsUtility_->writePin(port_, pinB_, true);
        break;

    case Color::OFF:
        portsUtility_->writePin(port_, pinA_, false);
        portsUtility_->writePin(port_, pinB_, false);
        break;
    }
}
