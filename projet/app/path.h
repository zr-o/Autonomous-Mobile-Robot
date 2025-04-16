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