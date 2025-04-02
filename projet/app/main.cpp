#include "robot.h"
#include "debug.h"

int main()
{
    Robot& robot = Robot::createRobot();

    robot.led().lightUp(Color::GREEN);

    DEBUG_PRINT(distance);
}