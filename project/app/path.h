/*
Giovanni Marven Alcena
Adam Azrou
Elliot Gareau
Anis Feteh Benabderrahmane

Une classe qui regroupe chaque partie du parcours, c'est à dire de B à D, D à J, A à B, J à Grille, première partie de la grille, 
deuxieme moitié de la grille (3 fonctions car 3 emplacements possibles après la première moitié de la grille), grille à A 
et effectue chaque parties en ordre en fonction du point de départ (A ou J).
16 avril 2025

Composantes :
Le robot (voir le robot.h si vous voulez les composantes du robot)
*/

#ifndef PATH_H
#define PATH_H

#include "robot.h"

enum class Position
{
    START,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    START_TOP_OF_GRILL,
    START_MIDDLE_OF_GRILL,
    START_BOTTOM_OF_GRILL,
    MIDDLE_TOP_OF_GRILL,
    MIDDLE_OF_GRILL,
    MIDDLE_BOTTOM_OF_GRILL,
    END_TOP_OF_GRILL,
    END_MIDDLE_OF_GRILL,
    END_BOTTOM_OF_GRILL
};

class Path
{
public:
    Path();
    void doPath();

private:
    Robot &robot_;
    Position currentPosition_ = Position::START;
    uint8_t buttonPressMemory_[2] = {0};

    void finishPathFromB();
    void finishPathFromGrill();

    void doPathFromBToD();
    void doPathFromDToJ();
    void doPathFromAToB();
    void doPathFromJtoGrill();
    void doPathFromGrillToA();
    void doFirstHalfGrill();
    void doSecondHalfGrill();
    void doSecondHalfGrillFromTop();
    void doSecondHalfGrillFromMiddle();
    void doSecondHalfGrillFromBottom();

    void continueAfterTurn();
    void continueAfterTurnLong();

    void selectBCDirection();
    Position findStartingPosition();

    void showPathIsFinished();
    void ShowIfObstacleDetected(bool obstacleWasDetected);
};
#endif