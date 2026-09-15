/*
Giovanni Marven Alcena
Adam Azrou
Elliot Gareau
Anis Feteh Benabderrahmane

16 avril 2025

Permet de suivre une ligne en ajustant la vitesse des roues à l’aide d’un algorithme PID.
Détection des virages intelligents (gauche, droite) selon différents contextes d'arrêt, intersections ou absence de ligne.
Utilise un délai (configurable par timer1) pour suivre la ligne pendant une durée précise. Peut aussi suivre ligne jusqu’à une condition donnée ou double condition.

Composantes :
Capteur makerLine (voir line_sensor.h)
Moteurs et roues (voir wheels.h)
Minuterie 16 bits pour les delais (voir timer1.h)
*/

#ifndef LINE_FOLLOWER_H
#define LINE_FOLLOWER_H

#include "line_sensor.h"
#include "wheels.h"
#include "timer1.h"

enum class StopCondition
{
    LEFT_TURN,
    RIGHT_TURN,
    CROSS,
    NO_LINE,
    PICKAXE_TURN
};

enum class TurnType
{
    SHARP_TURN,
    CROSSROAD,
    ON_PLACE,
    SMALL_TURN
};

class LineFollower
{
public:
    LineFollower(Timer1 &delayTimer, Wheels &wheels, LineSensor &lineSensor);
    void followLine(StopCondition condition);
    StopCondition followLine(StopCondition firstCondition, StopCondition secondCondition);
    void followLine(uint16_t delayMs);
    void followLine();
    void followLineBackwards(uint16_t delayMs);
    void smartTurnLeft(TurnType lineType);
    void smartTurnRight(TurnType lineType);

private:
    Timer1 &delayTimer_;
    Wheels &wheels_;
    LineSensor &lineSensor_;

    // Pour pouvoir simuler des floats, nous utilisons une arithmetique a virgule fixe. Example : 1.0 vaut 1.0 * 1024 = 1024
    // Valeurs calcules experimentalement
    int16_t kp_ = 1024;
    int16_t ki_ = 0;
    int16_t kd_ = 10240;

    const uint8_t leftWheelBaseSpeed = 88;
    const uint8_t rightWheelBaseSpeed = 90;

    int16_t errorIntegral_;
    int8_t previousError_;

    int8_t calculateCorrection(int8_t error);
    void applyCorrection(Direction direction);
};

#endif