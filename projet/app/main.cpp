#include "robot.h"
#include "distanceSensor.h"
#include "debug.h"

Timer1 sensorTimer = Timer1();

int main()
{
    Robot& robot = Robot::createRobot();

    robot.led().lightUp(Color::GREEN);

    DistanceSensor sensor(sensorTimer);

    uint8_t distance = sensor.readDistance();

    DEBUG_PRINT(distance);
}