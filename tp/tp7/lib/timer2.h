#ifndef TIMER_2_H
#define TIMER_2_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer_definitions.h"

class Timer2
{
public:
    void setPrescaler(Prescaler value);
    void setTimerMode(TimerMode mode);
    void setCompareOutputModeA(CompareOutputMode mode);
    void setCompareOutputModeB(CompareOutputMode mode);
    void setCompareValue(OutputComparePin pin, uint8_t value);
    void setTimerValue(uint8_t value);
    void allowInterrupts(OutputComparePin pin);
    Timer2();
};

#endif