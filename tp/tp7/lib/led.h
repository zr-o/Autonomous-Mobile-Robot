#ifndef LED_H
#define LED_H

#include <avr/io.h>
#include "ports.h"

enum class Color
{
    OFF,
    GREEN,
    RED
};

class Led
{
public:
    Led(Ports *portsUtility, Port port, Pin pinA, Pin pinB);
    void lightUp(Color color);

private:
    Port port_;
    Pin pinA_;
    Pin pinB_;
    Ports *portsUtility_;
};

#endif