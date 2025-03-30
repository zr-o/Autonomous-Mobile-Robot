#include "distanceSensor.h"
#include "timer1.h"

#define MAX_SIZE 5

DistanceSensor* sensorAdress = nullptr;  // variable globale pour ISR

ISR(TIMER1_COMPA_vect) {
    if (sensorAdress) {
        sensorAdress->updateDistance();
    }
}

DistanceSensor::DistanceSensor(Timer1& sensorTimer) : sensorTimer_(sensorTimer) {
    sensorTimer_.setPrescaler(Prescaler::PRESCALER_64);
    sensorTimer_.setTimerMode(TimerMode::CTC);
    sensorTimer_.setCompareValue(OutputComparePin::A, 12500);
    sensorTimer_.allowInterrupts(OutputComparePin::A);

    sensorAdress = this;
}

uint8_t DistanceSensor::readDistance() {
    uint16_t tempDistance = converter_.lecture(3);
    uint8_t distance = tempDistance >> 2;
    return distance;
}

uint8_t DistanceSensor::updateDistance() {

    static uint8_t distanceList[MAX_SIZE];
    static uint8_t indexPtr = 0;

    if (indexPtr >= 5) {
        indexPtr = 0;
    }
    else {indexPtr++;}

    distanceList[indexPtr] = DistanceSensor::readDistance();

    uint16_t sum = 0;
    for (uint8_t value : distanceList) {
        sum += value;
    }

    return sum / MAX_SIZE;  // Retourner la moyenne
}

