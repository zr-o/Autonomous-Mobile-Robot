#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H

#include "line_sensor.h"
#include "wheels.h"

class LineFollower
{
public:
    LineFollower(Wheels& wheels, LineSensor& lineSensor);
    int8_t calculateCorrection(int8_t error);
    void followLine();

private:
    Wheels &wheels_;
    LineSensor& lineSensor_;
    
    // Pour pouvoir simuler des floats, nous utilisons une arithmetique a virgule fixe. Example : 1.0 vaut 1.0 * 1024 = 1024
    int16_t kp_ = 1000;
    int16_t ki_ = 0;
    int16_t kd_ = 1000;

    const uint8_t leftWheelBaseSpeed = 120;
    const uint8_t rightWheelBaseSpeed = 120;

    int16_t errorIntegral_;
    int8_t previousError_;
};

#endif