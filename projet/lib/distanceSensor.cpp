#include "distanceSensor.h"
#include "timer1.h"

#define MAX_SIZE 5
#define COMPARE_VALUE 12500

DistanceSensor* sensorAdress = nullptr;  // variable globale pour ISR

ISR(TIMER1_COMPA_vect) {
    if (sensorAdress) {
        sensorAdress->readDistance();
    }
}

DistanceSensor::DistanceSensor(Timer1& sensorTimer) : sensorTimer_(sensorTimer) {
    sensorTimer_.setPrescaler(Prescaler::PRESCALER_64);
    sensorTimer_.setTimerMode(TimerMode::CTC);
    sensorTimer_.setCompareValue(OutputComparePin::A, COMPARE_VALUE);
    sensorTimer_.allowInterrupts(OutputComparePin::A);

    sensorAdress = this;
}

uint8_t DistanceSensor::readDistance() {
    uint16_t tempDistance = converter_.lecture(3);
    uint8_t distance = tempDistance >> 2;
    return DistanceSensor::updateDistance(distance);
}

uint8_t DistanceSensor::updateDistance(uint8_t newDistance) {

    static uint8_t distanceList[MAX_SIZE];
    static uint8_t indexPtr = 0;

    distanceList[indexPtr] = newDistance;

    if (indexPtr >= MAX_SIZE - 1) {
        indexPtr = 0;
    }
    else {indexPtr++;}

    uint16_t sum = 0;
    for (uint8_t value : distanceList) {
        sum += value;
    }

    return sum / MAX_SIZE;  // Retourner la moyenne
}

