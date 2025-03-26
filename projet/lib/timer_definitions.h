#ifndef TIMER_DEFINITIONS_H
#define TIMER_DEFINITIONS_H

enum class TimerMode
{
    NORMAL,
    CTC,
    PWM
};

enum class Prescaler
{
    NONE,
    PRESCALER_1,
    PRESCALER_8,
    PRESCALER_64,
    PRESCALER_256,
    PRESCALER_1024
};

enum class CompareOutputMode
{
    NORMAL,
    SET,
    CLEAR,
    TOGGLE
};

enum class OutputComparePin
{
    A,
    B,
    BOTH,
    NONE
};



#endif