#include "global_functions.h"

#define DELAY_MS_10 10
void variableDelayMs(uint8_t delay)
{
    for (uint8_t i = 0; i < (delay / 10); i++)
    {
        _delay_ms(DELAY_MS_10);
    }
}