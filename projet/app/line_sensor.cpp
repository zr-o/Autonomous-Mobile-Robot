#include "line_sensor.h"

LineSensor::LineSensor()
{
    // Vcc et Gnd
    Ports::setPinMode(PortMode::WRITE, Port::A, Pin::N1);
    Ports::setPinMode(PortMode::WRITE, Port::A, Pin::N2);
    Ports::writePin(Port::A, Pin::N1, true);
    Ports::writePin(Port::A, Pin::N2, false);

    Ports::setPinMode(PortMode::READ, Port::A, Pin::N3);
    Ports::setPinMode(PortMode::READ, Port::A, Pin::N4);
    Ports::setPinMode(PortMode::READ, Port::A, Pin::N5);
    Ports::setPinMode(PortMode::READ, Port::A, Pin::N6);
    Ports::setPinMode(PortMode::READ, Port::A, Pin::N7);
}

bool LineSensor::leftDetected()
{
    return Ports::readPin(Port::A, Pin::N3);
}

bool LineSensor::rightDetected()
{
    return Ports::readPin(Port::A, Pin::N7);
}

bool LineSensor::leftMiddleDetected()
{
    return Ports::readPin(Port::A, Pin::N4);
}

bool LineSensor::rightMiddleDetected()
{
    return Ports::readPin(Port::A, Pin::N6);
}

bool LineSensor::middleDetected()
{
    return Ports::readPin(Port::A, Pin::N5);
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