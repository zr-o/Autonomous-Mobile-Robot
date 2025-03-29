#ifndef WHEELS_H
#define WHEELS_H

#include <global_functions.h>

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
    Wheels(Timer2& pwmTimer);
    void rotateLeftWheel(uint8_t percentage, Direction direction);
    void rotateRightWheel(uint8_t percentage, Direction direction);
    void goForward(uint8_t percentage, uint16_t delay);
    void goForward(uint8_t percentage);
    void goBackwards(uint8_t percentage, uint16_t delay);
    void goBackwards(uint8_t percentage);
    void goLeft(uint8_t percentage, uint16_t delay);
    void goLeft(uint8_t percentage);
    void goRight(uint8_t percentage, uint16_t delay);
    void goRight(uint8_t percentage);
    void stop();

private:
    Timer2& pwmTimer_;
};

#endif