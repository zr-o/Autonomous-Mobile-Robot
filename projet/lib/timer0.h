/*
Giovanni Marven Alcena
Adam Azrou
Elliot Gareau
Anis Feteh Benabderrahmane

Permet de mettre une minuterie sur le pin de son choix dans le port de son choix.
La possibilite entre le mode CTC,PWM et NORMAL, et de choisir le pré-échelonneur voulu.
Permet de choisir le mode de comparaison voulu, minuterie allant jusqu'a 8 bits.
16 avril 2025

Composantes : Minuterie 8 bits du microcontrolleur.
*/

#ifndef TIMER_0_H
#define TIMER_0_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer_definitions.h"

class Timer0
{
public:
    void setPrescaler(Prescaler value);
    void setTimerMode(TimerMode mode);
    void setCompareOutputModeA(CompareOutputMode mode);
    void setCompareOutputModeB(CompareOutputMode mode);
    void setCompareValue(OutputComparePin pin, uint8_t value);
    void setTimerValue(uint8_t value);
    void allowInterrupts(OutputComparePin pin);
    Timer0();
};

#endif