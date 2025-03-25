#include "global_functions.h"

#ifndef DELAY_MS_10
#define DELAY_MS_10 10
#endif

void variableDelayMs(uint16_t delay)
{
    for (uint8_t i = 0; i < (delay / 10); i++)
    {
        _delay_ms(DELAY_MS_10);
    }
}