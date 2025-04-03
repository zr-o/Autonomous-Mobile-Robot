#include "line_follower.h"

LineFollower::LineFollower(Wheels &wheels, LineSensor &lineSensor) : wheels_(wheels), lineSensor_(lineSensor)
{
}

int16_t LineFollower::calculateCorrection(int8_t error)
{
    int8_t errorProportional = error;

    errorIntegral_ += error;

    if (errorIntegral_ > 10000 || errorIntegral_ < -10000)
    {
        errorIntegral_ = 0;
    }

    int8_t errorDerivative = error - previousError_;
    previousError_ = error;

    return ((int32_t)kp_ * errorProportional +
            (int32_t)ki_ * errorIntegral_ +
            (int32_t)kd_ * errorDerivative) /
           100;
}

void LineFollower::followLine()
{
    uint8_t position = lineSensor_.readPosition();
    int8_t error = position - 127;

    int16_t correction = calculateCorrection(error);

    int16_t adjustedRightWheelSpeed = rightWheelBaseSpeed + correction;
    int16_t adjustedLeftWheelSpeed = leftWheelBaseSpeed - correction;

    if (adjustedRightWheelSpeed > 255)
    {

        adjustedRightWheelSpeed = 255;
    }
    if (adjustedRightWheelSpeed < 0)
    {
        adjustedRightWheelSpeed = 0;
    }
    if (adjustedLeftWheelSpeed > 255)
    {
        adjustedLeftWheelSpeed = 255;
    }
    if (adjustedLeftWheelSpeed < 0)
    {
        adjustedLeftWheelSpeed = 0;
    }

    wheels_.setSpeedRight(uint8_t(adjustedRightWheelSpeed), Direction::FORWARD);
    wheels_.setSpeedLeft(uint8_t(adjustedLeftWheelSpeed), Direction::FORWARD);
}