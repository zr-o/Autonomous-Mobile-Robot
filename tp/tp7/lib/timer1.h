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
    void allowInterrupts(OutputComparePin pin);
    void initializeTimerForDelays(volatile bool& gIsExpired);
    void startTimer(uint16_t calculatedDelay);
    bool isExpired();
    Timer1();

private:
    volatile bool* isExpired_;
};

#endif