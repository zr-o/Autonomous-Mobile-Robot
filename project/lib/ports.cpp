#include "ports.h"

void Ports::setPinMode(PortMode mode, Port port, Pin pin)
{
    if (mode == PortMode::WRITE)
    {
        switch (port)
        {
        case Port::A:
            DDRA |= (1 << uint8_t(pin));
            break;

        case Port::B:
            DDRB |= (1 << uint8_t(pin));
            break;

        case Port::C:
            DDRC |= (1 << uint8_t(pin));
            break;

        case Port::D:
            DDRD |= (1 << uint8_t(pin));
            break;
        }
    }
    else
    {
        switch (port)
        {
        case Port::A:
            DDRA &= ~(1 << uint8_t(pin));
            break;

        case Port::B:
            DDRB &= ~(1 << uint8_t(pin));
            break;

        case Port::C:
            DDRC &= ~(1 << uint8_t(pin));
            break;

        case Port::D:
            DDRD &= ~(1 << uint8_t(pin));
            break;
        }
    }
}

uint8_t Ports::readPort(Port port)
{
    uint8_t value = 0;

    switch (port)
    {
    case Port::A:
        value = PINA;
        return value;

    case Port::B:
        value = PINB;
        return value;

    case Port::C:
        value = PINC;
        return value;

    case Port::D:
        value = PIND;
        return value;
    }

    return 0;
}

void Ports::writePort(Port port, uint8_t value)
{
    switch (port)
    {
    case Port::A:
        PORTA = value;

    case Port::B:
        PORTB = value;

    case Port::C:
        PORTC = value;

    case Port::D:
        PORTD = value;
    }
}

bool Ports::readPin(Port port, Pin pin)
{
    switch (port)
    {
    case Port::A:
        return (PINA & (1 << uint8_t(pin)));

    case Port::B:
        return (PINB & (1 << uint8_t(pin)));

    case Port::C:
        return (PINC & (1 << uint8_t(pin)));

    case Port::D:
        return (PIND & (1 << uint8_t(pin)));
    }

    return 0;
}

void Ports::writePin(Port port, Pin pin, bool value)
{
    switch (port)
    {
    case Port::A:
        if (value)
            PORTA |= (1 << uint8_t(pin));
        else
            PORTA &= ~(1 << uint8_t(pin));
        break;

    case Port::B:
        if (value)
            PORTB |= (1 << uint8_t(pin));
        else
            PORTB &= ~(1 << uint8_t(pin));
        break;

    case Port::C:
        if (value)
            PORTC |= (1 << uint8_t(pin));
        else
            PORTC &= ~(1 << uint8_t(pin));
        break;

    case Port::D:
        if (value)
            PORTD |= (1 << uint8_t(pin));
        else
            PORTD &= ~(1 << uint8_t(pin));
        break;
    }
}
