#include "led.h"

#define DELAY_250_MS 250
#define DELAY_125_MS 125

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

void Led::flashAt2Hz(Color color, uint8_t durationSeconds)
{
    for (uint8_t i = 0; i < 2 * durationSeconds; i++)
    {
        lightUp(color);
        _delay_ms(DELAY_250_MS);
        lightUp(Color::OFF);
        _delay_ms(DELAY_250_MS);
    }
}

void Led::flashAt4Hz(Color color, uint8_t durationSeconds)
{
    for (uint8_t i = 0; i < 2 * durationSeconds; i++)
    {
        lightUp(color);
        _delay_ms(DELAY_125_MS);
        lightUp(Color::OFF);
        _delay_ms(DELAY_125_MS);
    }
}

void Led::flashGreenRed2Hz()
{
    lightUp(Color::RED);
    _delay_ms(DELAY_250_MS);
    lightUp(Color::GREEN);
    _delay_ms(DELAY_250_MS);
}
