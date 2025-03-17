#ifndef LED_H
#define LED_H

#include <avr/io.h>
#include <ports.h>

enum class Color
{
    OFF,
    GREEN,
    RED
};

class Led
{
public:
    Led(Ports *portsUtility, Port port, Pin a, Pin b);
    ~Led();
    void lightUp(Color color);

private:
    Port port_;
    Pin a_;
    Pin b_;
    Ports *portsUtility_;
};

#endif