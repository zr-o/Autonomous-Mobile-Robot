#include "distance_sensor.h"

DistanceSensor *sensorAdress = nullptr; // variable globale pour ISR

ISR(TIMER1_COMPA_vect)
{
    if (sensorAdress)
    {
        sensorAdress->readDistance();
    }
}

DistanceSensor::DistanceSensor(Timer1 &sensorTimer, can &converter) : sensorTimer_(sensorTimer), converter_(converter)
{
    sensorTimer_.setPrescaler(Prescaler::PRESCALER_64);
    sensorTimer_.setTimerMode(TimerMode::CTC);

    Ports::setPinMode(PortMode::READ, Port::A, Pin::N8);

    // ISR appelee a chaque 100 ms pour calculer la moyenne
    sensorTimer_.setCompareValue(OutputComparePin::A, COMPARE_VALUE_100_MS_DELAY);
    sensorTimer_.allowInterrupts(OutputComparePin::A);

    sensorAdress = this;
}

uint8_t DistanceSensor::readDistance()
{
    uint16_t tempDistance = converter_.lecture(PA7);
    uint8_t distance = tempDistance >> 2;
    return DistanceSensor::updateDistance(distance);
}

uint8_t DistanceSensor::updateDistance(uint8_t newDistance)
{

    static uint8_t distanceList[MAX_ARRAY_SIZE_SENSOR_DATA];
    static uint8_t indexPtr = 0;

    distanceList[indexPtr] = newDistance;

    if (indexPtr >= MAX_ARRAY_SIZE_SENSOR_DATA - 1)
    {
        indexPtr = 0;
    }
    else
    {
        indexPtr++;
    }

    uint16_t sum = 0;
    for (uint8_t value : distanceList)
    {
        sum += value;
    }

    return sum / MAX_ARRAY_SIZE_SENSOR_DATA; // Retourner la moyenne
}
