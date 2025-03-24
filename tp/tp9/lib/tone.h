#ifndef TONE_H
#define TONE_H

#include "debug.h"
#include "timer0.h"
#include "wheels.h"
#include "ports.h"

class Tone
{
public:
    Tone(Timer0* tomeTimer);
    void playNote(uint8_t note);
    void turnOffNote();

private:
Timer0* toneTimer_;
};

#endif