/*
Giovanni Marven Alcena
Adam Azrou
Elliot Gareau
Anis Feteh Benabderrahmane

Definitions communes pour le mode d'utilisation des timer0, timer1 et timer2.
16 mars 2025
*/

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