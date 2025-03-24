/*#define F_CPU 8000000UL

#include <util/delay.h>
#include "tone.h"

#define NOTE 250
#define LONG 500
#define REST 150

void delayMsVariable(uint16_t delay)
{
    for (uint16_t i = 0; i < (delay / 10); i++)
    {
        _delay_ms(10);
    }
}

int main()
{
    Timer0 toneTimer;
    Tone tone(&toneTimer);

    uint8_t melody[] = {
        // Intro
        76,
        75,
        76,
        75,
        76,
        71,
        74,
        72,
        70,
        255,
        60,
        64,
        69,
        71,
        255,
        64,
        68,
        71,
        72,
        255,
        64,
        76,
        75,
        76,
        75,
        76,
        71,
        74,
        72,
        70,
        255,

        // Section A

        60,
        64,
        69,
        71,
        255,
        60,
        64,
        67,
        69, // C5 E5 G5 A5
        255,

    };

    uint16_t durations[] = {
        // Intro
        NOTE,
        NOTE,
        NOTE,
        NOTE,
        NOTE,
        NOTE,
        NOTE,
        NOTE,
        LONG,
        REST,
        NOTE,
        NOTE,
        NOTE,
        NOTE,
        REST,
        NOTE,
        NOTE,
        NOTE,
        NOTE,
        REST,
        NOTE,
        NOTE,
        NOTE,
        NOTE,
        NOTE,
        NOTE,
        NOTE,
        NOTE,
        NOTE,
        LONG,
        REST,

        // Section A

        NOTE,
        NOTE,
        NOTE,
        NOTE,
        REST,
        NOTE,
        NOTE,
        NOTE,
        NOTE,
        REST,
    };

    uint8_t nNotes = sizeof(melody) / sizeof(uint8_t);

    for (uint8_t i = 0; i < nNotes; i++)
    {
        if (melody[i] == 255)
        {
            tone.turnOffNote();
            delayMsVariable(durations[i]);
        }
        else
        {
            tone.playNote(melody[i]);
            delayMsVariable(durations[i]);
            tone.turnOffNote();
            delayMsVariable(30);
        }
    }
}*/
