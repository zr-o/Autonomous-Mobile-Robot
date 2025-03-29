#ifndef ROBOT_H
#define ROBOT_H

#include "tone.h"
#include "wheels.h"
#include "button.h"
#include "led.h"

class Robot
{
public:
    static Robot& createRobot();
    Wheels& wheels();
    Tone& tone();
    Button& externButton();
    Button& motherboardButton();
    Led& led();


private:
   Robot();

    Timer0 tonePwmTimer_;
    Timer2 wheelPwmTimer_;
    Wheels wheels_;
    Tone tone_;
    Button externButton_;
    Button motherboardButton_;
    Led led_;
    static Robot robot_;
};

#endif