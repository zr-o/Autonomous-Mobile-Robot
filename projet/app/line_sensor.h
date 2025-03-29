#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include "ports.h"

// Doit etre calibrer avant et doit etre en mode dark.
class LineSensor
{
public:
    LineSensor();
    bool middleDetected();
    bool leftMiddleDetected();
    bool rightMiddleDetected();
    bool leftDetected();
    bool rightDetected();
    uint8_t sensorsCount();

private:
};

#endif