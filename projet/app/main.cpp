#include "robot.h"

int main()
{
    Robot& robot = Robot::createRobot();

    robot.led().lightUp(Color::GREEN);
}