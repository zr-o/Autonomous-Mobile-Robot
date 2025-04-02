#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H

#include "line_sensor.h"

class LineFollower
{
public:
private:
    const uint8_t kp_;
    const uint8_t kd_;
    const uint8_t ki_;

    uint16_t integralSum_ = 0;
    uint8_t previousError_ = 0;
};

#endif