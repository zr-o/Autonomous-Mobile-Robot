#ifndef WHEELS_H
#define WHEELS_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer1.h"
#include "timer2.h"
#include "ports.h"

enum class Direction
{
    FORWARD,
    BACKWARDS
};

class Wheels
{
public:
    Wheels(Timer1 *delayTimer, Timer2 *pwmTimer, Ports *portsUtility);
    void rotateLeftWheel(uint8_t percentage, Direction direction);
    void rotateRightWheel(uint8_t percentage, Direction direction);

private:
    Timer1 *delayTimer_;
    Timer2 *pwmTimer_;
    Ports *portsUtility_;
};

#endif