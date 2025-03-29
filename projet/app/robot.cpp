#include "robot.h"

Robot Robot::robot_;

Robot::Robot()
    : wheels_(wheelPwmTimer_),
      tone_(tonePwmTimer_),
      externButton_(ButtonType::EXTERN, Port::D, Pin::N4),
      motherboardButton_(ButtonType::MOTHERBOARD, Port::D, Pin::N3),
      led_(Port::B, Pin::N1, Pin::N2)
{
}

Robot &Robot::createRobot()
{
    return robot_;
}

Wheels &Robot::wheels()
{
    return wheels_;
}

Tone &Robot::tone()
{
    return tone_;
}

Button &Robot::externButton()
{
    return externButton_;
}

Button &Robot::motherboardButton()
{
    return motherboardButton_;
}

Led &Robot::led()
{
    return led_;
}

LineSensor& Robot::lineSensor(){
    return lineSensor_;
}