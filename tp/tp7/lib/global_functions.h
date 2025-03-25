#ifndef GLOBALFUNCTIONS_H
#define GLOBALFUNCTIONS_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>

void variableDelayMs(uint16_t delay);

#endif