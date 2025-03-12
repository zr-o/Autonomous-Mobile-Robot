#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer_definitions.h"

class Timer1
{
public:
    void setPrescaler(Prescaler value);
    void setCompareOutputMode(OutputComparePin pin, CompareOutputMode mode);
    void setCompareValue(OutputComparePin pin, uint16_t value);
    void setTimerValue(uint16_t value);
    void allowInterrupts(OutputComparePin pin, bool enable);
    void delayMs(uint16_t delay);
    Timer1(TimerMode mode);
    ~Timer1();

private:
    ModeMinuterie mode_;
};
