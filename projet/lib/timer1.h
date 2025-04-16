/*
Giovanni Marven Alcena
Adam Azrou
Elliot Gareau
Anis Feteh Benabderrahmane

Permet de mettre une minuterie sur le pin de son choix dans le port de son choix.
La possibilite entre le mode CTC,PWM et NORMAL, et de choisir le pré-échelonneur voulu.
Permet de choisir le mode de comparaison voulu, minuterie allant jusqu'a 16 bits.
Le programme peut faire des delais selon un temps calculé voulu. D'activer ou de désactiver
les interruptions.
16 avril 2025

Composantes : Minuterie 16 bits du microcontrolleur.
*/

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