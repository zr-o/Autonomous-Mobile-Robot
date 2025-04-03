#ifndef ROBOT_H
#define ROBOT_H

#include "tone.h"
#include "wheels.h"
#include "button.h"
#include "led.h"
#include "line_sensor.h"
#include "can.h"
#include "distance_sensor.h"
#include "line_follower.h"

class Robot
{
public:
    static Robot& createRobot();
    Wheels& wheels();
    Tone& tone();
    Button& externButton();
    Button& motherboardButton();
    Led& led();
    LineSensor& lineSensor();
    //DistanceSensor& distanceSensor();
    LineFollower& lineFollower();


private:
   Robot();

    Timer0 tonePwmTimer_;
    //Timer1 sensorTimer_;
    Timer2 wheelPwmTimer_;
    can converter_;
    Wheels wheels_;
    Tone tone_;
    Button externButton_;
    Button motherboardButton_;
    Led led_;
    LineSensor lineSensor_;
    //DistanceSensor distanceSensor_;
    LineFollower lineFollower_;
    
    static Robot robot_;
};

#endif