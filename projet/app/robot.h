/*
Giovanni Marven Alcena
Adam Azrou
Elliot Gareau
Anis Feteh Benabderrahmane

Description: un programme qui instancie tout les objets qui sont nécéssaires au robot pour le parcours c'est à dire 3 timers, 
un can, des roues, un buzzer, un bouton interne, un bouton externe, une led, un capteur de distance un capteur de ligne et 
un objet suiveur de ligne (voir line_follower.h)
16 avril 2025

Composantes :
Deux minuteries 8 bits et 1 minuterie 16 bits (voir timer1, 2, 3)
Un sensor de ligne (voir line_sensor.h)
Un sensor de distance (voir distance_sensor.h)
2 roues et moteurs (voir wheel.h)
Un convertisseur analogique (voir can.h)
2 boutons (voir button.h)
Suivi de ligne (voir line_sensor.h)
*/

#ifndef ROBOT_H
#define ROBOT_H

#include "tone.h"
#include "wheels.h"
#include "button.h"
#include "led.h"
#include "line_sensor.h"
#include "can.h"
#include "distance_sensor.h"
#include "line_follower.h"

class Robot
{
public:
    static Robot& createRobot();
    Wheels& wheels();
    Tone& tone();
    Button& externButton();
    Button& motherboardButton();
    Led& led();
    LineSensor& lineSensor();
    DistanceSensor& distanceSensor();
    LineFollower& lineFollower();


private:
   Robot();

    Timer0 tonePwmTimer_;
    Timer1 delayTimer_;
    Timer2 wheelPwmTimer_;
    can converter_;
    Wheels wheels_;
    Tone tone_;
    Button externButton_;
    Button motherboardButton_;
    Led led_;
    LineSensor lineSensor_;
    DistanceSensor distanceSensor_;
    LineFollower lineFollower_;
    
    static Robot robot_;
};

#endif