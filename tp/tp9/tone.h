#ifndef TONE_H
#define TONE_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "debug.h"
#include "timer0.h"
#include "wheels.h"


class Tone {

    public: 
    
    
    Tone();
    void playNote(uint8_t note);
    void turnOffMusic();

    private :
    Timer0 timer_;
    volatile bool isExpired_;
    double frequency;
    double activeTime;
    double periode;
    void setNote(uint8_t note);
};

#endif