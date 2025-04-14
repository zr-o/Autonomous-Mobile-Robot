#include "path.h"

#define MAXIMUM_DIRECTION_SELECTION 2

Path::Path() : robot_(Robot::createRobot())
{
}

void Path::continueAfterTurn()
{

    robot_.wheels().goForward(100, 1000);
}

void Path::selectBCDirection()
{
    for (uint8_t i = 0; i < MAXIMUM_DIRECTION_SELECTION; i++)
    {
        while (true)
        {
            if (robot_.externButton().isPressed())
            {
                buttonPressMemory_[i] = 1; // 0 pour droite, 1 pour gauche

                while (robot_.externButton().isPressed())
                {
                    robot_.led().lightUp(Color::RED);
                }

                break;
            }

            if (robot_.motherboardButton().isPressed())
            {
                buttonPressMemory_[i] = 0; // 0 pour droite, 1 pour gauche

                while (robot_.motherboardButton().isPressed())
                {
                    robot_.led().lightUp(Color::GREEN);
                }

                break;
            }
        }

        robot_.led().lightUp(Color::OFF);
    }
}

Position Path::findStartingPosition()
{
    StopCondition lineUnderRobot = robot_.lineFollower().followLine(StopCondition::CROSS, StopCondition::NO_LINE);

    if (lineUnderRobot == StopCondition::CROSS)
    {
        return Position::J;
    }
    else
    {
        return Position::A;
    }
}

void Path::doPathFromBToD()
{

    robot_.tone().playNote(46);
    _delay_ms(1000);
    robot_.tone().turnOffNote();
    robot_.wheels().goForward(100, 500);

    if (buttonPressMemory_[0] == 0)
    {
        robot_.lineFollower().smartTurnRight(TurnType::ON_PLACE);
    }

    else
    {
        robot_.lineFollower().smartTurnLeft(TurnType::ON_PLACE);
    }

    robot_.lineFollower().followLine(StopCondition::NO_LINE);

    robot_.tone().playNote(46);
    _delay_ms(1000);
    robot_.tone().turnOffNote();
    robot_.wheels().goForward(100, 500);

    if (buttonPressMemory_[1] == 0)
    {
        robot_.lineFollower().smartTurnRight(TurnType::ON_PLACE);
    }

    else
    {
        robot_.lineFollower().smartTurnLeft(TurnType::ON_PLACE);
    }

    robot_.lineFollower().followLine(StopCondition::LEFT_TURN, StopCondition::RIGHT_TURN);

    if (buttonPressMemory_[1] == 0)
    {
        robot_.wheels().goForward(100, 1000);
        robot_.lineFollower().smartTurnLeft(TurnType::ON_PLACE);
    }

    else
    {
        robot_.wheels().goForward(100, 1000);
        robot_.lineFollower().smartTurnRight(TurnType::ON_PLACE);
    }

    robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
    robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);
}

void Path::doPathFromDToJ()
{

    robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);

    continueAfterTurn();

    robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
    robot_.lineFollower().smartTurnRight(TurnType::CROSSROAD);
    robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
    robot_.lineFollower().followLine(3000);
    robot_.wheels().goRight(90, 100);
    robot_.wheels().stop(1000);

    if (robot_.distanceSensor().readDistance() > 120)
    {

        robot_.lineFollower().smartTurnRight(TurnType::ON_PLACE);
        robot_.lineFollower().followLine(StopCondition::PICKAXE_TURN);
        robot_.lineFollower().smartTurnRight(TurnType::SMALL_TURN);

        robot_.lineFollower().followLine(StopCondition::CROSS);
        robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);
    }

    else
    {
        robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
        robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);
        robot_.lineFollower().followLine(StopCondition::CROSS);
        robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);
    }

    robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
    continueAfterTurn();
    robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
    robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);
}

void Path::doPathFromAToB()
{

    robot_.lineFollower().followLine(StopCondition::NO_LINE);
}

void Path::doPathFromJtoGrill()
{

    robot_.lineFollower().followLine(StopCondition::CROSS);
}
/*
void Path::doHalfGrill() {

    robot_.wheels().goForward(90,500);
    if (robot_.distanceSensor().readDistance() > 120)

}
*/

void Path::doPathFromGrillToA()
{

    robot_.wheels().goForward(90, 500);
    robot_.lineFollower().followLine(3000);
    robot_.wheels().stop(1000);

    if (robot_.distanceSensor().readDistance() > 120)
    {
        robot_.lineFollower().smartTurnRight(TurnType::ON_PLACE);
        robot_.lineFollower().followLine(StopCondition::LEFT_TURN);
        robot_.lineFollower().smartTurnLeft(TurnType::SHARP_TURN);
        robot_.lineFollower().followLine(2000);
        robot_.wheels().stop(1000);

        if (robot_.distanceSensor().readDistance() > 120)
        {
            robot_.lineFollower().followLineBackwards(2000);
            robot_.lineFollower().smartTurnLeft(TurnType::ON_PLACE);
            robot_.lineFollower().followLine(StopCondition::CROSS);
            continueAfterTurn();
            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);
            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            continueAfterTurn();
            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            robot_.lineFollower().smartTurnRight(TurnType::CROSSROAD);
            robot_.lineFollower().followLine(StopCondition::CROSS);
            robot_.lineFollower().smartTurnLeft(TurnType::CROSSROAD);
            robot_.wheels().stop(1000);
        }

        else
        {
            robot_.lineFollower().followLine(StopCondition::LEFT_TURN);
            continueAfterTurn();
            robot_.lineFollower().followLine(StopCondition::LEFT_TURN);
            robot_.lineFollower().smartTurnLeft(TurnType::CROSSROAD);
            robot_.lineFollower().followLine(StopCondition::CROSS);
            robot_.lineFollower().smartTurnRight(TurnType::CROSSROAD);
            robot_.wheels().stop(1000);
        }
    }

    else
    {
        robot_.lineFollower().followLine(StopCondition::CROSS);
        continueAfterTurn();
        robot_.lineFollower().followLine(StopCondition::CROSS);
        continueAfterTurn();
        robot_.lineFollower().followLine(2300);
        robot_.wheels().stop(1000);
    }

    if (robot_.distanceSensor().readDistance() > 120)
    {
        robot_.lineFollower().smartTurnRight(TurnType::ON_PLACE);
        robot_.lineFollower().followLine(StopCondition::CROSS);
        robot_.lineFollower().smartTurnLeft(TurnType::SHARP_TURN);
        robot_.lineFollower().followLine(2000);
        robot_.wheels().stop(1000);

        if (robot_.distanceSensor().readDistance() > 120)
        {
            robot_.lineFollower().followLineBackwards(2000);
            robot_.lineFollower().smartTurnLeft(TurnType::ON_PLACE);
            robot_.lineFollower().followLine(StopCondition::CROSS);
            continueAfterTurn();
            robot_.lineFollower().followLine(StopCondition::CROSS);
            robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);
            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            continueAfterTurn();
            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);
            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            continueAfterTurn();
            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            continueAfterTurn();
        }

        else
        {
            robot_.lineFollower().followLine(StopCondition::LEFT_TURN);
            continueAfterTurn();
            robot_.lineFollower().followLine(StopCondition::CROSS);
            robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);
        }
    }

    else
    {
        robot_.lineFollower().followLine(StopCondition::CROSS);
        continueAfterTurn();
        robot_.lineFollower().followLine(StopCondition::CROSS);
        robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);
        robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
        continueAfterTurn();
    }
    robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
    robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);
}

void Path::doPath()
{
    selectBCDirection();

    _delay_ms(2000);

    Position startingPosition = findStartingPosition();

    if (startingPosition == Position::A)
    {
        currentPosition_ = Position::B;
        finishPathFromB();
    }
    else
    {
        currentPosition_ = Position::START_OF_GRILL;
        finishPathFromGrill();
    }
}

void Path::finishPathFromB()
{
    doPathFromBToD();
    doPathFromDToJ();
    doPathFromJtoGrill();
    doPathFromGrillToA();
}
void Path::finishPathFromGrill()
{
    doPathFromGrillToA();
    doPathFromAToB();
    doPathFromBToD();
    doPathFromDToJ();
}
