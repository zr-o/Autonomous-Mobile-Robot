#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

#include <avr/io.h>
#include "can.h"
#include "timer1.h"
#include "global_defines.h"
#include "ports.h"

class DistanceSensor
{
public:
    DistanceSensor(Timer1 &sensorTimer, can &converter);
    uint8_t updateDistance(uint8_t newDistance);
    uint8_t readDistance();

private:
    Timer1 &sensorTimer_;
    can &converter_;
    uint8_t distance_;
};

#endif /* DISTANCE_SENSOR_H */
