#include "tone.h"

Tone::Tone() {

    timer_.setCompareOutputModeA(CompareOutputMode::TOGGLE);
    timer_.setTimerMode(TimerMode::PWM);
}

void Tone::setNote(uint8_t note) {
    
    switch(note) {
        case 45:
            frequency = 110.00;
            break;
        case 46:
            frequency = 116.54;
            break;
        case 47:
            frequency = 123.47;
            break;
        case 48:
            frequency = 130.81;
            break;
        case 49:
            frequency = 138.59;
            break;
        case 50:
            frequency = 146.83;
            break;
        case 51:
            frequency = 155.56;
            break;
        case 52:
            frequency = 164.81;
            break;
        case 53:
            frequency = 174.61;
            break;
        case 54:
            frequency = 185.00;
            break;
        case 55:
            frequency = 196.00;
            break;
        case 56:
            frequency = 207.65;
            break;
        case 57:
            frequency = 220.00;
            break;
        case 58:
            frequency = 233.08;
            break;
        case 59:
            frequency = 246.94;
            break;
        case 60:
            frequency = 261.63;
            break;
        case 61:
            frequency = 277.18;
            break;
        case 62:
            frequency = 293.66;
            break;
        case 63:
            frequency = 311.13;
            break;
        case 64:
            frequency = 329.63;
            break;
        case 65:
            frequency = 349.23;
            break;
        case 66:
            frequency = 369.99;
            break;
        case 67:
            frequency = 392.00;
            break;
        case 68:
            frequency = 415.30;
            break;
        case 69:
            frequency = 440.00;
            break;
        case 70:
            frequency = 466.16;
            break;
        case 71:
            frequency = 493.88;
            break;
        case 72:
            frequency = 523.25;
            break;
        case 73:
            frequency = 554.37;
            break;
        case 74:
            frequency = 587.33;
            break;
        case 75:
            frequency = 622.25;
            break;
        case 76:
            frequency = 659.26;
            break;
        case 77:
            frequency = 698.46;
            break;
        case 78:
            frequency = 739.99;
            break;
        case 79:
            frequency = 783.99;
            break;
        case 80:
            frequency = 830.61;
            break;
        case 81:
            frequency = 880.00;
            break;
        default:
            DEBUG_PRINT("Note non valide!");
            frequency = 0;
    }

    if (frequency > 0) {
    uint16_t converterToMs = 1000;
    periode = (1.0 / frequency) * converterToMs;
    uint8_t activeTimeDivider = 2;
    activeTime = periode / activeTimeDivider;
    }
    else {
        periode = 0;
        activeTime = 0;
    }
}

void Tone::playNote(uint8_t note) {
    
    setNote(note);
    Ports::setPinMode(PortMode::WRITE, Port::B, Pin::N1);
    uint16_t msToSeconde = 1000;
    uint16_t prescaler   = 1024;
    uint16_t cyclePeriode= static_cast<uint16_t>(F_CPU * activeTime) / (prescaler * msToSeconde);

    timer_.setCompareValue(OutputComparePin::A, cyclePeriode);


}

void Tone::turnOffMusic() {
    timer_.setPrescaler(Prescaler::NONE);
    timer_.setCompareOutputModeA(CompareOutputMode::NORMAL);
    Ports::setPinMode(PortMode::READ, Port::B, Pin::N1);
    
}