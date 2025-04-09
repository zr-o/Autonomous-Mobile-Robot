#include "path.h"

#define MAXIMUM_DIRECTION_SELECTION 2

Path::Path() : robot_(Robot::createRobot())
{
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

void Path::doPath()
{
    selectBCDirection();

    _delay_ms(2000);

    Position startingPosition = findStartingPosition();

    if (startingPosition == Position::A)
    {
        currentPosition_ = Position::B;
        //doPathFromB();
    }
    else
    {
        currentPosition_ = Position::START_OF_GRILL;
        //doPathFromGrill()
    }
}