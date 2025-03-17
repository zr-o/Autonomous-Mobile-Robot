#include "led.h"

Led::Led(Ports *portsUtility, Port port, Pin a, Pin b) : port_(port), a_(a), b_(b), portsUtility_(portsUtility)
{
    portsUtility_->setPinMode(PortMode::WRITE, port, a);
    portsUtility_->setPinMode(PortMode::WRITE, port, b);
}

void Led::lightUp(Color color)
{
    switch (color)
    {
    case Color::GREEN:
        portsUtility_->writePin(port_, a_, true);
        portsUtility_->writePin(port_, b_, false);

    case Color::RED:
        portsUtility_->writePin(port_, a_, false);
        portsUtility_->writePin(port_, b_, true);

    case Color::OFF:
        portsUtility_->writePin(port_, a_, false);
        portsUtility_->writePin(port_, b_, false);
    }
}

Led::~Led()
{
    portsUtility_->setPinMode(PortMode::READ, port_, a_);
    portsUtility_->setPinMode(PortMode::READ, port_, b_);
}