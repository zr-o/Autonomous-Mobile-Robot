#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

#include "lib_defines.h"
#include <avr/io.h>
#include "can.h"
#include "ports.h"
#include <util/delay.h>


class DistanceSensor
{
public:
    DistanceSensor(can &converter);
    uint16_t readDistance();

private:
    can &converter_;
};

#endif
