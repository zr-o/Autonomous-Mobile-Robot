#include "line_sensor.h"

#define BYTE_SHIFT_2 2

LineSensor::LineSensor(can &converter) : converter_(converter)
{
    Ports::setPinMode(PortMode::READ, Port::A, Pin::N1);
    Ports::setPinMode(PortMode::READ, Port::A, Pin::N2);
    Ports::setPinMode(PortMode::READ, Port::A, Pin::N3);
    Ports::setPinMode(PortMode::READ, Port::A, Pin::N4);
    Ports::setPinMode(PortMode::READ, Port::A, Pin::N5);

    // Utilisation du mode analogique du sensor
    Ports::setPinMode(PortMode::READ, Port::A, Pin::N6);
}

bool LineSensor::leftDetected()
{
    return Ports::readPin(Port::A, Pin::N1);
}

bool LineSensor::rightDetected()
{
    return Ports::readPin(Port::A, Pin::N5);
}

bool LineSensor::leftMiddleDetected()
{
    return Ports::readPin(Port::A, Pin::N2);
}

bool LineSensor::rightMiddleDetected()
{
    return Ports::readPin(Port::A, Pin::N4);
}

bool LineSensor::middleDetected()
{
    return Ports::readPin(Port::A, Pin::N3);
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
    uint16_t sensorPosition = converter_.lecture(PA5);
    sensorPosition >>= BYTE_SHIFT_2;

    return uint8_t(sensorPosition);
}