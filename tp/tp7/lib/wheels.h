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
    Wheels(Timer1 *delayTimer, Timer2 *pwmTimer);
    void rotateLeftWheel(uint8_t percentage, Direction direction);
    void rotateRightWheel(uint8_t percentage, Direction direction);
    void goForward(uint8_t percentage, uint16_t calculatedDelay);
    void goForward(uint8_t percentage);
    void goBackwards(uint8_t percentage, uint16_t calculatedDelay);
    void goBackwards(uint8_t percentage);
    void goLeft(uint8_t percentage, uint16_t calculatedDelay);
    void goLeft(uint8_t percentage);
    void goRight(uint8_t percentage, uint16_t calculatedDelay);
    void goRight(uint8_t percentage);
    void stop();

private:
    Timer1 *delayTimer_;
    Timer2 *pwmTimer_;
};

#endif