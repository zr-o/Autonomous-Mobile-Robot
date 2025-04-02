#include "line_sensor.h"

#define BYTE_SHIFT_2 2

LineSensor::LineSensor(can &converter) : converter_(converter)
{
    // Faire attention aux pins utilise par la memoire et dbg c0, c1, d0, d1
    Ports::setPinMode(PortMode::READ, Port::C, Pin::N3);
    Ports::setPinMode(PortMode::READ, Port::C, Pin::N4);
    Ports::setPinMode(PortMode::READ, Port::C, Pin::N5);
    Ports::setPinMode(PortMode::READ, Port::C, Pin::N6);
    Ports::setPinMode(PortMode::READ, Port::C, Pin::N7);

    // Utilisation du mode analogique du sensor
    Ports::setPinMode(PortMode::READ, Port::A, Pin::N4);
}

bool LineSensor::leftDetected()
{
    return Ports::readPin(Port::C, Pin::N3);
}

bool LineSensor::rightDetected()
{
    return Ports::readPin(Port::C, Pin::N7);
}

bool LineSensor::leftMiddleDetected()
{
    return Ports::readPin(Port::C, Pin::N4);
}

bool LineSensor::rightMiddleDetected()
{
    return Ports::readPin(Port::C, Pin::N6);
}

bool LineSensor::middleDetected()
{
    return Ports::readPin(Port::C, Pin::N5);
}

uint8_t LineSensor::sensorsCount()
{
    uint8_t count = 0;

    if (leftDetected())
    {
        count++;
    }

    if (leftMiddleDetected())
    {
        count++;
    }

    if (rightDetected())
    {
        count++;
    }

    if (rightMiddleDetected())
    {
        count++;
    }

    if (middleDetected())
    {
        count++;
    }

    return count;
}

uint8_t LineSensor::readPosition()
{
    uint16_t sensorPosition = converter_.lecture(PA3);
    sensorPosition >>= BYTE_SHIFT_2;

    return uint8_t(sensorPosition);
}