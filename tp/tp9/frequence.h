#ifndef FREQUENCE_H
#define FREQUENCE_H

#define F_CPU 8000000
#include "debug.h"
#include "timer1.h"
#include "wheels.h"

struct Sonorite {   

    double frequence;
    double periode;
    double tempsActif;

};

Sonorite getNote(uint8_t note) {
    Sonorite sonorite;

    switch(note) {
        case 45:
            sonorite.frequence = 110.00;
            sonorite.periode= 9.09;
            sonorite.tempsActif = 4.545;
            break;
        case 46:
            sonorite.frequence = 116.54;
            sonorite.periode= 8.58;
            sonorite.tempsActif = 4.290;
            break;
        case 47:
            sonorite.frequence = 123.47;
            sonorite.periode= 8.10;
            sonorite.tempsActif = 4.050;
            break;
        case 48:
            sonorite.frequence = 130.81;
            sonorite.periode= 7.64;
            sonorite.tempsActif = 3.822;
            break;
        case 49:
            sonorite.frequence = 138.59;
            sonorite.periode= 7.22;
            sonorite.tempsActif = 3.608;
            break;
        case 50:
            sonorite.frequence = 146.83;
            sonorite.periode= 6.81;
            sonorite.tempsActif = 3.405;
            break;
        case 51:
            sonorite.frequence = 155.56;
            sonorite.periode= 6.43;
            sonorite.tempsActif = 3.214;
            break;
        case 52:
            sonorite.frequence = 164.81;
            sonorite.periode= 6.07;
            sonorite.tempsActif = 3.034;
            break;
        case 53:
            sonorite.frequence = 174.61;
            sonorite.periode= 5.73;
            sonorite.tempsActif = 2.863;
            break;
        case 54:
            sonorite.frequence = 185.00;
            sonorite.periode= 5.41;
            sonorite.tempsActif = 2.703;
            break;
        case 55:
            sonorite.frequence = 196.00;
            sonorite.periode= 5.10;
            sonorite.tempsActif = 2.551;
            break;
        case 56:
            sonorite.frequence = 207.65;
            sonorite.periode= 4.82;
            sonorite.tempsActif = 2.408;
            break;
        case 57:
            sonorite.frequence = 220.00;
            sonorite.periode= 4.55;
            sonorite.tempsActif = 2.273;
            break;
        case 58:
            sonorite.frequence = 233.08;
            sonorite.periode= 4.29;
            sonorite.tempsActif = 2.145;
            break;
        case 59:
            sonorite.frequence = 246.94;
            sonorite.periode= 4.06;
            sonorite.tempsActif = 2.025;
            break;
        case 60:
            sonorite.frequence = 261.63;
            sonorite.periode= 3.82;
            sonorite.tempsActif = 1.911;
            break;
        case 61:
            sonorite.frequence = 277.18;
            sonorite.periode= 3.61;
            sonorite.tempsActif = 1.804;
            break;
        case 62:
            sonorite.frequence = 293.66;
            sonorite.periode= 3.41;
            sonorite.tempsActif = 1.703;
            break;
        case 63:
            sonorite.frequence = 311.13;
            sonorite.periode= 3.21;
            sonorite.tempsActif = 1.607;
            break;
        case 64:
            sonorite.frequence = 329.63;
            sonorite.periode= 3.03;
            sonorite.tempsActif = 1.517;
            break;
        case 65:
            sonorite.frequence = 349.23;
            sonorite.periode= 2.86;
            sonorite.tempsActif = 1.432;
            break;
        case 66:
            sonorite.frequence = 369.99;
            sonorite.periode= 2.70;
            sonorite.tempsActif = 1.351;
            break;
        case 67:
            sonorite.frequence = 392.00;
            sonorite.periode= 2.55;
            sonorite.tempsActif = 1.276;
            break;
        case 68:
            sonorite.frequence = 415.30;
            sonorite.periode= 2.41;
            sonorite.tempsActif = 1.204;
            break;
        case 69:
            sonorite.frequence = 440.00;
            sonorite.periode= 2.27;
            sonorite.tempsActif = 1.136;
            break;
        case 70:
            sonorite.frequence = 466.16;
            sonorite.periode= 2.15;
            sonorite.tempsActif = 1.073;
            break;
        case 71:
            sonorite.frequence = 493.88;
            sonorite.periode= 2.02;
            sonorite.tempsActif = 1.012;
            break;
        case 72:
            sonorite.frequence = 523.25;
            sonorite.periode= 1.91;
            sonorite.tempsActif = 0.956;
            break;
        case 73:
            sonorite.frequence = 554.37;
            sonorite.periode= 1.80;
            sonorite.tempsActif = 0.902;
            break;
        case 74:
            sonorite.frequence = 587.33;
            sonorite.periode= 1.70;
            sonorite.tempsActif = 0.851;
            break;
        case 75:
            sonorite.frequence = 622.25;
            sonorite.periode= 1.61;
            sonorite.tempsActif = 0.804;
            break;
        case 76:
            sonorite.frequence = 659.26;
            sonorite.periode= 1.52;
            sonorite.tempsActif = 0.758;
            break;
        case 77:
            sonorite.frequence = 698.46;
            sonorite.periode= 1.43;
            sonorite.tempsActif = 0.716;
            break;
        case 78:
            sonorite.frequence = 739.99;
            sonorite.periode= 1.35;
            sonorite.tempsActif = 0.676;
            break;
        case 79:
            sonorite.frequence = 783.99;
            sonorite.periode= 1.28;
            sonorite.tempsActif = 0.638;
            break;
        case 80:
            sonorite.frequence = 830.61;
            sonorite.periode= 1.20;
            sonorite.tempsActif = 0.602;
            break;
        case 81:
            sonorite.frequence = 880.00;
            sonorite.periode= 1.14;
            sonorite.tempsActif = 0.568;
            break;
        default:
            DEBUG_PRINT("Note non valide!");
            sonorite.frequence = 0;
            sonorite.periode= 0;
            sonorite.tempsActif = 0;
    }

    return sonorite;
}

Timer1 Timer(TimerMode::PWM);
volatile bool isExpired = false;

void playNote(uint8_t note) {
Sonorite sonorite = getNote(note);


Timer.initializeTimerForDelays(isExpired);
Timer.setCompareOutputModeA(CompareOutputMode::TOGGLE);

uint16_t msToSeconde = 1000;
uint16_t prescaler = 1024;
uint16_t cyclePeriode = (F_CPU * sonorite.tempsActif)/(prescaler * msToSeconde);
Timer.startTimer(cyclePeriode);

}

void turnOffMusic() {

Timer.setPrescaler(Prescaler::NONE);
Timer.setCompareOutputModeA(CompareOutputMode::CLEAR);
}

#endif