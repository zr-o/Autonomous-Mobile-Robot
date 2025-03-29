#include "tone.h"
#include "debug.h"

Tone::Tone(Timer0& toneTimer) : toneTimer_(toneTimer)
{
    toneTimer_.setPrescaler(Prescaler::NONE);
    toneTimer_.setTimerMode(TimerMode::CTC);
    toneTimer_.setCompareOutputModeA(CompareOutputMode::TOGGLE);

    Ports::setPinMode(PortMode::WRITE, Port::B, Pin::N4);
    Ports::setPinMode(PortMode::WRITE, Port::B, Pin::N3);
    Ports::writePin(Port::B, Pin::N3, false);
}

void Tone::playNote(uint8_t note)
{
    uint8_t compareValue = 0;

    switch (note)
    {
    case 45:
        compareValue = 141;
        break;

    case 46:
        compareValue = 133;
        break;

    case 47:
        compareValue = 126;
        break;

    case 48:
        compareValue = 118;
        break;

    case 49:
        compareValue = 112;
        break;

    case 50:
        compareValue = 105;
        break;

    case 51:
        compareValue = 99;
        break;

    case 52:
        compareValue = 94;
        break;

    case 53:
        compareValue = 88;
        break;

    case 54:
        compareValue = 83;
        break;

    case 55:
        compareValue = 79;
        break;

    case 56:
        compareValue = 74;
        break;

    case 57:
        compareValue = 70;
        break;

    case 58:
        compareValue = 66;
        break;

    case 59:
        compareValue = 62;
        break;

    case 60:
        compareValue = 59;
        break;

    case 61:
        compareValue = 55;
        break;

    case 62:
        compareValue = 52;
        break;

    case 63:
        compareValue = 49;
        break;

    case 64:
        compareValue = 46;
        break;

    case 65:
        compareValue = 44;
        break;

    case 66:
        compareValue = 41;
        break;

    case 67:
        compareValue = 39;
        break;

    case 68:
        compareValue = 37;
        break;

    case 69:
        compareValue = 35;
        break;

    case 70:
        compareValue = 33;
        break;

    case 71:
        compareValue = 31;
        break;

    case 72:
        compareValue = 29;
        break;

    case 73:
        compareValue = 27;
        break;

    case 74:
        compareValue = 26;
        break;

    case 75:
        compareValue = 24;
        break;

    case 76:
        compareValue = 23;
        break;

    case 77:
        compareValue = 21;
        break;

    case 78:
        compareValue = 20;
        break;

    case 79:
        compareValue = 19;
        break;

    case 80:
        compareValue = 18;
        break;

    case 81:
        compareValue = 17;
        break;
    }

 
toneTimer_.setTimerValue(0);
toneTimer_.setCompareValue(OutputComparePin::A, compareValue);
toneTimer_.setPrescaler(Prescaler::PRESCALER_256);
}

void Tone::turnOffNote()
{
    toneTimer_.setPrescaler(Prescaler::NONE);
}