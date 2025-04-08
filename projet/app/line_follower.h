#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H

#include "line_sensor.h"
#include "wheels.h"
#include "timer1.h"

enum class StopCondition
{
    LEFT_TURN,
    RIGHT_TURN,
    CROSS,
    NO_LINE
};

class LineFollower
{
public:
    LineFollower(Timer1 &delayTimer, Wheels &wheels, LineSensor &lineSensor);
    int8_t calculateCorrection(int8_t error);
    void applyCorrection();
    void followLine(StopCondition condition);
    StopCondition followLine(StopCondition firstCondition, StopCondition secondCondition);
    void followLine(uint16_t delayMs);
    void followLine();

private:
    Timer1 &delayTimer_;
    Wheels &wheels_;
    LineSensor &lineSensor_;

    // Pour pouvoir simuler des floats, nous utilisons une arithmetique a virgule fixe. Example : 1.0 vaut 1.0 * 1024 = 1024
    int16_t kp_ = 1024;
    int16_t ki_ = 0;
    int16_t kd_ = 5000;

    const uint8_t leftWheelBaseSpeed = 88;
    const uint8_t rightWheelBaseSpeed = 90;

    int16_t errorIntegral_;
    int8_t previousError_;

    bool checkCondition();
};

#endif