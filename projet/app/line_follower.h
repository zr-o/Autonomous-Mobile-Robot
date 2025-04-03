#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H

#include "line_sensor.h"
#include "wheels.h"

class LineFollower
{
public:
    LineFollower(Wheels& wheels, LineSensor& lineSensor);
    int16_t calculateCorrection(int8_t error);
    void followLine();

private:
    Wheels &wheels_;
    LineSensor& lineSensor_;

    // Valeur calcules experimentalement
    const uint16_t kp_ = 100;
    const uint16_t kd_ = 10;
    const uint16_t ki_ = 0;

    // Valeur de base des roues
    const uint8_t leftWheelBaseSpeed = 110;
    const uint8_t rightWheelBaseSpeed = 110;

    int16_t errorIntegral_ = 0;
    uint8_t previousError_ = 0;
};

#endif