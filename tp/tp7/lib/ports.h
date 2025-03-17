#ifndef PORTS_H
#define PORTS_H

#include <avr/io.h>

enum class Port
{
    A,
    B,
    C,
    D
};

enum class Pin
{
    N1 = 0,
    N2,
    N3,
    N4,
    N5,
    N6,
    N7,
    N8
};

enum class PortMode
{
    WRITE,
    READ
};

class Ports
{
public:
    void setPinMode(PortMode mode, Port port, Pin pin);
    uint8_t readPort(Port port);
    void writePort(Port port, uint8_t value);
    bool readPin(Port port, Pin pin);
    void writePin(Port port, Pin pin, bool value);
};

#endif