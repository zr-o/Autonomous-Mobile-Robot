#include "line_follower.h"

#define SCALE_FACTOR 10
#define MAX_CORRECTION 127
#define INTEGRAL_LIMIT 10000

static inline int16_t clamp(int16_t value, int16_t minVal, int16_t maxVal)
{
    return (value < minVal) ? minVal : (value > maxVal ? maxVal : value);
}

LineFollower::LineFollower(Wheels &wheels, LineSensor &lineSensor)
    : wheels_(wheels), lineSensor_(lineSensor)
{   
}

int8_t LineFollower::calculateCorrection(int8_t error)
{
    errorIntegral_ += error;


    if (errorIntegral_ > INTEGRAL_LIMIT || errorIntegral_ < -INTEGRAL_LIMIT)
    {
        errorIntegral_ = 0;
    }

    int32_t correction = ((int32_t)kp_ * error +
                          (int32_t)ki_ * errorIntegral_ +
                          (int32_t)kd_ * (error - previousError_)) >> SCALE_FACTOR; 

    previousError_ = error;

    correction = clamp(correction, -MAX_CORRECTION, MAX_CORRECTION);

    return (int8_t)correction;
}

void LineFollower::followLine()
{
    int8_t error = lineSensor_.readPosition() - 127;
    int8_t correction = calculateCorrection(error);

    int16_t adjustedRightWheelSpeed = rightWheelBaseSpeed + correction;
    int16_t adjustedLeftWheelSpeed = leftWheelBaseSpeed - correction;

    wheels_.setSpeedRight((uint8_t)clamp(adjustedRightWheelSpeed, 0, 255), Direction::FORWARD);
    wheels_.setSpeedLeft((uint8_t)clamp(adjustedLeftWheelSpeed, 0, 255), Direction::FORWARD);
}
