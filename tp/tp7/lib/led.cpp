#include "led.h"

Led::Led(Port port, Pin pinA, Pin pinB) : port_(port), pinA_(pinA), pinB_(pinB)
{
    Ports::setPinMode(PortMode::WRITE, port_, pinA_);
    Ports::setPinMode(PortMode::WRITE, port_, pinB_);
}

void Led::lightUp(Color color)
{
    switch (color)
    {
    case Color::GREEN:
        Ports::writePin(port_, pinA_, true);
        Ports::writePin(port_, pinB_, false);
        break;

    case Color::RED:
        Ports::writePin(port_, pinA_, false);
        Ports::writePin(port_, pinB_, true);
        break;

    case Color::OFF:
        Ports::writePin(port_, pinA_, false);
        Ports::writePin(port_, pinB_, false);
        break;
    }
}
