#ifndef TIMER_1_H
#define TIMER_1_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer_definitions.h"

class Timer1
{
public:
    void setPrescaler(Prescaler value);
    void setTimerMode(TimerMode mode);
    void setCompareOutputModeA(CompareOutputMode mode);
    void setCompareOutputModeB(CompareOutputMode mode);
    void setCompareValue(OutputComparePin pin, uint16_t value);
    void setTimerValue(uint16_t value);
    static void allowInterrupts(OutputComparePin pin);
    static void disallowInterrupts(OutputComparePin pin);
    void initializeTimerForDelays();
    void startTimer(OutputComparePin pin, uint16_t calculatedDelay);
    Timer1();
};

#endif