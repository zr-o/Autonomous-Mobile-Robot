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
    START_OF_GRILL,
    MIDDLE_OF_GRILL,
    END_OF_GRILL,
    END
};

class Path
{
public:
    Path();
    void selectBCDirection();
    Position findStartingPosition();
    //void finishPathFromB();
    //void finishPathFromGrill();
    void doPath();

    //void doPathFromBToD();
    //void doPathFromDToJ();
    //void doPathFromJtoGrill();
    //void doPathFromGrillToA();
    //void doPathFromAtoB

private:
    Robot &robot_;
    Position currentPosition_ = Position::START;
    uint8_t buttonPressMemory_[2] = {0};
};
#endif