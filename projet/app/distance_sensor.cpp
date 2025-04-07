#include "distance_sensor.h"

#define BYTE_SHIFT_2 2
#define AMOUNT_OF_DISTANCES_5 5
#define MINIMUM_DELAY_BETWEEN_MEASURES 50
#define MEDIAN 3

DistanceSensor::DistanceSensor(can &converter) : converter_(converter)
{
    Ports::setPinMode(PortMode::READ, Port::A, Pin::N8);
}

uint16_t DistanceSensor::readDistance()
{
    uint16_t distances[AMOUNT_OF_DISTANCES_5] = {0};

    for (uint8_t i = 0; i < AMOUNT_OF_DISTANCES_5; i++)
    {
        distances[i] = converter_.lecture(PA7);
        _delay_ms(MINIMUM_DELAY_BETWEEN_MEASURES);
    }

    // Sort using bubble sort (ascending order)
    for (uint8_t i = 0; i < AMOUNT_OF_DISTANCES_5 - 1; i++)
    {
        for (uint8_t j = 0; j < AMOUNT_OF_DISTANCES_5 - i - 1; j++)
        {
            if (distances[j] > distances[j + 1])
            {
                uint16_t temp = distances[j];
                distances[j] = distances[j + 1];
                distances[j + 1] = temp;
            }
        }
    }

    // Return the median (middle value in sorted array)
    return distances[MEDIAN];
}

