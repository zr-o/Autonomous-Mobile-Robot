#include "general_functions.h"

void variableDelayMs(uint16_t delay)
{
    for (uint8_t i = 0; i < (delay / 10); i++)
    {
        _delay_ms(DELAY_MS_10);
    }
}