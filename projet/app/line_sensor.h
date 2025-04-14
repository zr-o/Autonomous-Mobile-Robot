#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

#include "ports.h"
#include "can.h"

// Doit etre calibrer avant et doit etre en mode dark.
class LineSensor
{
public:
    LineSensor(can &converter);
    bool middleDetected();
    bool leftMiddleDetected();
    bool rightMiddleDetected();
    bool leftDetected();
    bool rightDetected();
    bool leftTurnDetected();
    bool pickaxeTurnDetected();
    bool rightTurnDetected();
    bool crossDetected();
    bool noLineDetected();

    uint8_t sensorsCount();
    uint8_t readPosition();

private:
    can &converter_;
};

#endif