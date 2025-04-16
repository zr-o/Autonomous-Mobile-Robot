#include "path.h"

// Valeurs prise en respectant l'énoncé
#define MAXIMUM_DIRECTION_SELECTION 2
#define WAIT_BEFORE_START_PATH_DELAY_2000MS 2000
#define LED_LIGHT_UP_DURATION_SECONDS_2 2
#define PLAY_LOW_FREQUENCY_SOUND_DELAY_1000MS 1000

// Valeurs calcules experimentalement selon le contexte
#define SKIP_LINE_DELAY_500MS 500
#define SKIP_LINE_DELAY_1000MS 1000
#define ALIGN_WHEELS_DELAY_2000MS 2000
#define GET_CLOSER_TO_SCAN_DELAY_2000MS 2000
#define GO_BACK_BECAUSE_OBSTACLE_DELAY_2300MS 2300
#define WHEELS_BASE_SPEED_90 90
#define LED_LIGHT_UP_DURATION_SECONDS_2 2
#define LOW_FREQUENCY_SOUND 45
#define STOP_TO_STABILIZE_500MS 500
#define STOP_TO_DETECT_OBSTACLE_1000MS 1000
#define OBSTACLE_THRESHOLD_VALUE 120
#define ALIGN_WITH_H_DELAY_3000MS 3000
#define SMALL_TURN_DELAY_10MS 10


Path::Path() : robot_(Robot::createRobot())
{
}

void Path::continueAfterTurn()
{

    robot_.wheels().goForward(WHEELS_BASE_SPEED_90, SKIP_LINE_DELAY_500MS);
}

void Path::continueAfterTurnLong()
{
    robot_.wheels().goForward(WHEELS_BASE_SPEED_90, SKIP_LINE_DELAY_1000MS);
}

void Path::showPathIsFinished()
{

    while (true)
    {
        robot_.led().flashGreenRed2Hz();
    }
}

void Path::ShowIfObstacleDetected(bool obstacleWasDetected)
{
    if (obstacleWasDetected)
    {
        robot_.led().flashAt4Hz(Color::RED, LED_LIGHT_UP_DURATION_SECONDS_2);
    }

    else
    {
        robot_.led().flashAt4Hz(Color::GREEN, LED_LIGHT_UP_DURATION_SECONDS_2);
    }
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
    // Nous sommes a B
    currentPosition_ = Position::B;

    robot_.tone().playNote(LOW_FREQUENCY_SOUND);
    _delay_ms(PLAY_LOW_FREQUENCY_SOUND_DELAY_1000MS);
    robot_.tone().turnOffNote();

    continueAfterTurnLong();
    robot_.wheels().stop(STOP_TO_STABILIZE_500MS);

    if (buttonPressMemory_[0] == 0)
    {
        robot_.lineFollower().smartTurnRight(TurnType::ON_PLACE);
    }

    else
    {
        robot_.lineFollower().smartTurnLeft(TurnType::ON_PLACE);
    }

    robot_.lineFollower().followLine(StopCondition::NO_LINE);

    // Nous sommes a C
    currentPosition_ = Position::C;

    robot_.tone().playNote(LOW_FREQUENCY_SOUND);
    _delay_ms(PLAY_LOW_FREQUENCY_SOUND_DELAY_1000MS);
    robot_.tone().turnOffNote();

    continueAfterTurnLong();
    robot_.wheels().stop(STOP_TO_STABILIZE_500MS);

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
        continueAfterTurnLong();
        robot_.wheels().stop(STOP_TO_STABILIZE_500MS);
        robot_.lineFollower().smartTurnLeft(TurnType::ON_PLACE);
    }

    else
    {
        continueAfterTurnLong();
        robot_.wheels().stop(STOP_TO_STABILIZE_500MS);
        robot_.lineFollower().smartTurnRight(TurnType::ON_PLACE);
    }

    robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
    robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

    // Nous sommes a D
    currentPosition_ = Position::D;
}

void Path::doPathFromDToJ()
{

    robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
    continueAfterTurn();

    // Nous sommes a E
    currentPosition_ = Position::E;

    robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
    robot_.lineFollower().smartTurnRight(TurnType::CROSSROAD);

    // Nous sommes a F
    currentPosition_ = Position::F;

    robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);

    // Nous sommes a G
    currentPosition_ = Position::G;

    robot_.lineFollower().followLine(ALIGN_WITH_H_DELAY_3000MS);
    robot_.wheels().goRight(WHEELS_BASE_SPEED_90, SMALL_TURN_DELAY_10MS);
    robot_.wheels().stop(STOP_TO_DETECT_OBSTACLE_1000MS);

    // Nous detectons l'obstacle a H
    bool obstacleDetected = (robot_.distanceSensor().readDistance() > OBSTACLE_THRESHOLD_VALUE) ? true : false;
    ShowIfObstacleDetected(obstacleDetected);

    // Si nous detectons l'obstacle a H
    if (obstacleDetected)
    {
        robot_.lineFollower().smartTurnRight(TurnType::ON_PLACE);
        robot_.lineFollower().followLine(StopCondition::PICKAXE_TURN);
        robot_.lineFollower().smartTurnRight(TurnType::SMALL_TURN);

        // Nous sommes a I
        currentPosition_ = Position::I;

        robot_.lineFollower().followLine(StopCondition::CROSS);
        robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

        // Nous sommes a E
        currentPosition_ = Position::E;
    }

    // Si nous ne detectons pas l'obstacle
    else
    {
        robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
        robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

        // Nous sommes a H
        currentPosition_ = Position::H;

        robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
        continueAfterTurn();

        // Nous sommes a I
        currentPosition_ = Position::I;

        robot_.lineFollower().followLine(StopCondition::CROSS);
        robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

        // Nous sommes a E
        currentPosition_ = Position::E;
    }

    robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
    continueAfterTurn();

    // Nous sommes a F
    currentPosition_ = Position::F;

    robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
    robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

    // Nous sommes a J
    currentPosition_ = Position::J;
}

void Path::doPathFromAToB()
{
    robot_.lineFollower().followLine(StopCondition::NO_LINE);

    // Nous sommes a B
    currentPosition_ = Position::B;
}

void Path::doPathFromJtoGrill()
{
    robot_.lineFollower().followLine(StopCondition::CROSS);

    // Nous sommes au debut de la grille
    currentPosition_ = Position::START_MIDDLE_OF_GRILL;
}

void Path::doFirstHalfGrill()
{
    continueAfterTurn();
    robot_.lineFollower().followLine(   ALIGN_WHEELS_DELAY_2000MS);
    robot_.wheels().stop(STOP_TO_STABILIZE_500MS);

    robot_.lineFollower().followLine(GET_CLOSER_TO_SCAN_DELAY_2000MS);
    robot_.wheels().stop(STOP_TO_DETECT_OBSTACLE_1000MS);

    if (robot_.distanceSensor().readDistance() > OBSTACLE_THRESHOLD_VALUE)
    {
        robot_.lineFollower().followLineBackwards(GO_BACK_BECAUSE_OBSTACLE_DELAY_2300MS);
        robot_.wheels().stop(STOP_TO_STABILIZE_500MS);
        robot_.lineFollower().smartTurnRight(TurnType::ON_PLACE);
        robot_.lineFollower().followLine(StopCondition::LEFT_TURN);
        robot_.lineFollower().smartTurnLeft(TurnType::SHARP_TURN);

        // Nous sommes en haut a droite de la grille
        currentPosition_ = Position::START_TOP_OF_GRILL;

        robot_.lineFollower().followLine(GET_CLOSER_TO_SCAN_DELAY_2000MS);
        robot_.wheels().stop(STOP_TO_DETECT_OBSTACLE_1000MS);

        if (robot_.distanceSensor().readDistance() > OBSTACLE_THRESHOLD_VALUE)
        {

            robot_.lineFollower().followLineBackwards(GO_BACK_BECAUSE_OBSTACLE_DELAY_2300MS);
            robot_.wheels().stop(STOP_TO_STABILIZE_500MS);
            robot_.lineFollower().smartTurnLeft(TurnType::ON_PLACE);
            robot_.lineFollower().followLine(StopCondition::CROSS);
            continueAfterTurn();

            // Nous sommes au debut de la grille
            currentPosition_ = Position::START_MIDDLE_OF_GRILL;

            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

            // Nous sommes en bas a droite de la grille
            currentPosition_ = Position::START_BOTTOM_OF_GRILL;

            // On montre que on passe par M
            ShowIfObstacleDetected(false);

            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            continueAfterTurn();

            // Nous sommes a M
            currentPosition_ = Position::M;

            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            continueAfterTurn();
            robot_.lineFollower().followLine(   ALIGN_WHEELS_DELAY_2000MS);
            robot_.wheels().stop(STOP_TO_STABILIZE_500MS);

            // Nous somme au milieu en bas de la grille
            currentPosition_ = Position::MIDDLE_BOTTOM_OF_GRILL;
        }

        else
        {
            // Nous affichons que nous passons par K
            ShowIfObstacleDetected(false);

            robot_.lineFollower().followLine(StopCondition::LEFT_TURN);
            continueAfterTurn();

            // Nous sommes a K
            currentPosition_ = Position::K;

            robot_.lineFollower().followLine(StopCondition::LEFT_TURN);
            continueAfterTurn();
            robot_.lineFollower().followLine(   ALIGN_WHEELS_DELAY_2000MS);
            robot_.wheels().stop(STOP_TO_STABILIZE_500MS);

            // Nous sommes au top middle de la grille
            currentPosition_ = Position::MIDDLE_TOP_OF_GRILL;
        }
    }

    else
    {
        // Nous affichons que nous passons par L
        ShowIfObstacleDetected(false);

        robot_.lineFollower().followLine(StopCondition::CROSS);
        continueAfterTurn();

        // Nous sommes a L
        currentPosition_ = Position::L;

        robot_.lineFollower().followLine(StopCondition::CROSS);
        continueAfterTurn();
        robot_.lineFollower().followLine(   ALIGN_WHEELS_DELAY_2000MS);
        robot_.wheels().stop(STOP_TO_STABILIZE_500MS);

        // Nous sommes au milieu de la grille
        currentPosition_ = Position::MIDDLE_OF_GRILL;
    }
}

void Path::doSecondHalfGrill()
{
    switch (currentPosition_)
    {
    case Position::MIDDLE_TOP_OF_GRILL:
        doSecondHalfGrillFromTop();
        break;

    case Position::MIDDLE_OF_GRILL:
        doSecondHalfGrillFromMiddle();
        break;

    case Position::MIDDLE_BOTTOM_OF_GRILL:
        doSecondHalfGrillFromBottom();
        break;

    default:
        break;
    }
}

void Path::doSecondHalfGrillFromTop()
{
    robot_.lineFollower().followLine(GET_CLOSER_TO_SCAN_DELAY_2000MS);
    robot_.wheels().stop(STOP_TO_DETECT_OBSTACLE_1000MS);

    if (robot_.distanceSensor().readDistance() > OBSTACLE_THRESHOLD_VALUE)
    {
        robot_.lineFollower().followLineBackwards(GO_BACK_BECAUSE_OBSTACLE_DELAY_2300MS);
        robot_.wheels().stop(STOP_TO_STABILIZE_500MS);
        robot_.lineFollower().smartTurnLeft(TurnType::ON_PLACE);
        robot_.lineFollower().followLine(StopCondition::CROSS);
        robot_.lineFollower().smartTurnRight(TurnType::CROSSROAD);

        // Nous sommes au milieu milieu de la grille
        currentPosition_ = Position::MIDDLE_OF_GRILL;

        robot_.lineFollower().followLine(GET_CLOSER_TO_SCAN_DELAY_2000MS);
        robot_.wheels().stop(STOP_TO_STABILIZE_500MS);

        if (robot_.distanceSensor().readDistance() > OBSTACLE_THRESHOLD_VALUE)
        {
            robot_.lineFollower().followLineBackwards(GO_BACK_BECAUSE_OBSTACLE_DELAY_2300MS);
            robot_.wheels().stop(STOP_TO_STABILIZE_500MS);
            robot_.lineFollower().smartTurnLeft(TurnType::ON_PLACE);
            robot_.lineFollower().followLine(StopCondition::CROSS);
            robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

            // Nous sommes en bas au milieu de la grille
            currentPosition_ = Position::MIDDLE_BOTTOM_OF_GRILL;

            // On montre que on passe par P
            ShowIfObstacleDetected(false);

            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            continueAfterTurn();

            // Nous sommes a P
            currentPosition_ = Position::P;

            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

            // Nous sommes a la fin en bas de la grille
            currentPosition_ = Position::END_BOTTOM_OF_GRILL;

            robot_.lineFollower()
                .followLine(StopCondition::RIGHT_TURN);
            continueAfterTurn();

            // Nous somme a la fin au milieu de la grille
            currentPosition_ = Position::END_MIDDLE_OF_GRILL;

            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            continueAfterTurn();

            // Nous sommes a la fin en haut de la grille
            currentPosition_ = Position::END_TOP_OF_GRILL;
        }

        else
        {
            // On montre que on passe par O
            ShowIfObstacleDetected(false);

            robot_.lineFollower().followLine(StopCondition::CROSS);
            continueAfterTurn();

            // Nous sommes a O
            currentPosition_ = Position::O;

            robot_.lineFollower().followLine(StopCondition::CROSS);
            robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

            // Nous sommes a la fin au milieu de la grille
            currentPosition_ = Position::END_MIDDLE_OF_GRILL;

            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            continueAfterTurn();

            // Nous sommes a la fin en haut de la grille
            currentPosition_ = Position::END_TOP_OF_GRILL;
        }
    }

    else
    {
        // On montre que on passe par N
        ShowIfObstacleDetected(false);

        robot_.lineFollower().followLine(StopCondition::LEFT_TURN);
        continueAfterTurn();

        // Nous sommes a N
        currentPosition_ = Position::N;

        robot_.lineFollower().followLine(StopCondition::CROSS);
        robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

        // Nous sommes a la fin en haut de la grille
        currentPosition_ = Position::END_TOP_OF_GRILL;
    }
}
void Path::doSecondHalfGrillFromMiddle()
{
    robot_.lineFollower().followLine(GET_CLOSER_TO_SCAN_DELAY_2000MS);
    robot_.wheels().stop(STOP_TO_DETECT_OBSTACLE_1000MS);

    if (robot_.distanceSensor().readDistance() > OBSTACLE_THRESHOLD_VALUE)
    {
        robot_.lineFollower().followLineBackwards(GO_BACK_BECAUSE_OBSTACLE_DELAY_2300MS);
        robot_.wheels().stop(STOP_TO_STABILIZE_500MS);
        robot_.lineFollower().smartTurnRight(TurnType::ON_PLACE);
        robot_.lineFollower().followLine(StopCondition::CROSS);
        robot_.lineFollower().smartTurnLeft(TurnType::SHARP_TURN);

        // Nous sommes au milieu en haut de la grille
        currentPosition_ = Position::MIDDLE_TOP_OF_GRILL;

        robot_.lineFollower().followLine(GET_CLOSER_TO_SCAN_DELAY_2000MS);
        robot_.wheels().stop(STOP_TO_DETECT_OBSTACLE_1000MS);

        if (robot_.distanceSensor().readDistance() > OBSTACLE_THRESHOLD_VALUE)
        {
            robot_.lineFollower().followLineBackwards(GO_BACK_BECAUSE_OBSTACLE_DELAY_2300MS);
            robot_.wheels().stop(STOP_TO_STABILIZE_500MS);
            robot_.lineFollower().smartTurnLeft(TurnType::ON_PLACE);
            robot_.lineFollower().followLine(StopCondition::CROSS);
            continueAfterTurn();

            // Nous sommes au milieu de la grille
            currentPosition_ = Position::MIDDLE_OF_GRILL;

            robot_.lineFollower().followLine(StopCondition::CROSS);
            robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

            // Nous sommes au milieu en bas de la grille
            currentPosition_ = Position::MIDDLE_BOTTOM_OF_GRILL;

            // On montre qu'on passe par P
            ShowIfObstacleDetected(false);

            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            continueAfterTurn();

            // Nous sommes a P
            currentPosition_ = Position::P;

            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

            // Nous sommes a la fin en bas de la grille
            currentPosition_ = Position::END_BOTTOM_OF_GRILL;

            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            continueAfterTurn();

            // Nous sommes a la fin au milieu de la grille
            currentPosition_ = Position::END_MIDDLE_OF_GRILL;

            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            continueAfterTurn();

            // Nous sommes a la fin en haut de la grille
            currentPosition_ = Position::END_TOP_OF_GRILL;
        }

        else
        {
            // On montre qu'on passe par N
            ShowIfObstacleDetected(false);

            robot_.lineFollower().followLine(StopCondition::LEFT_TURN);
            continueAfterTurn();

            // Nous sommes a P
            currentPosition_ = Position::P;

            robot_.lineFollower().followLine(StopCondition::CROSS);
            robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

            // Nous somme a la fin en haut de la grille
            currentPosition_ = Position::END_TOP_OF_GRILL;
        }
    }

    else
    {
        // On montre qu'on passe par O
        ShowIfObstacleDetected(false);

        robot_.lineFollower().followLine(StopCondition::CROSS);
        continueAfterTurn();

        // Nous sommes a O
        currentPosition_ = Position::O;

        robot_.lineFollower().followLine(StopCondition::CROSS);
        robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

        // Nous sommes a la fin au milieu de la grille
        currentPosition_ = Position::END_MIDDLE_OF_GRILL;

        robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
        continueAfterTurn();

        // Nous sommes a la fin en haut de la grille
        currentPosition_ = Position::END_TOP_OF_GRILL;
    }
}
void Path::doSecondHalfGrillFromBottom()
{
    robot_.lineFollower().followLine(GET_CLOSER_TO_SCAN_DELAY_2000MS);
    robot_.wheels().stop(STOP_TO_DETECT_OBSTACLE_1000MS);

    if (robot_.distanceSensor().readDistance() > OBSTACLE_THRESHOLD_VALUE)
    {
        robot_.lineFollower().followLineBackwards(GO_BACK_BECAUSE_OBSTACLE_DELAY_2300MS);
        robot_.wheels().stop(STOP_TO_STABILIZE_500MS);
        robot_.lineFollower().smartTurnRight(TurnType::ON_PLACE);
        robot_.lineFollower().followLine(StopCondition::CROSS);
        robot_.lineFollower().smartTurnLeft(TurnType::CROSSROAD);

        // Nous sommes au milieu de la grille
        currentPosition_ = Position::MIDDLE_OF_GRILL;

        robot_.lineFollower().followLine(GET_CLOSER_TO_SCAN_DELAY_2000MS);
        robot_.wheels().stop(STOP_TO_DETECT_OBSTACLE_1000MS);

        if (robot_.distanceSensor().readDistance() > OBSTACLE_THRESHOLD_VALUE)
        {
            robot_.lineFollower().followLineBackwards(GO_BACK_BECAUSE_OBSTACLE_DELAY_2300MS);
            robot_.wheels().stop(STOP_TO_STABILIZE_500MS);
            robot_.lineFollower().smartTurnRight(TurnType::ON_PLACE);
            robot_.lineFollower().followLine(StopCondition::CROSS);
            robot_.lineFollower().smartTurnLeft(TurnType::SHARP_TURN);

            // Nous sommes au milieu en haut de la grille
            currentPosition_ = Position::MIDDLE_TOP_OF_GRILL;

            // On montre qu'on passe par N
            ShowIfObstacleDetected(false);

            robot_.lineFollower().followLine(StopCondition::LEFT_TURN);
            continueAfterTurn();

            // Nous sommes a N
            currentPosition_ = Position::N;

            robot_.lineFollower().followLine(StopCondition::CROSS);
            robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

            // Nous sommes a la fin en haut de la grille
            currentPosition_ = Position::END_TOP_OF_GRILL;
        }

        else
        {
            // On montre qu'on passe par O
            ShowIfObstacleDetected(false);

            robot_.lineFollower().followLine(StopCondition::CROSS);
            continueAfterTurn();

            // Nous sommes a O
            currentPosition_ = Position::O;

            robot_.lineFollower().followLine(StopCondition::CROSS);
            robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

            // Nous sommes a la fin au milieu de la grille
            currentPosition_ = Position::END_MIDDLE_OF_GRILL;

            robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
            continueAfterTurn();

            // Nous sommes a la fin en haut de la grille
            currentPosition_ = Position::MIDDLE_TOP_OF_GRILL;
        }
    }

    else
    {
        // On montre qu'on passe par P
        ShowIfObstacleDetected(false);

        robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
        continueAfterTurn();

        // Nous sommes a P
        currentPosition_ = Position::P;

        robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
        robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

        // Nous sommes a la fin en bas de la grille
        currentPosition_ = Position::END_BOTTOM_OF_GRILL;

        robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
        continueAfterTurn();

        // Nous sommes a la fin au milieu de la grille
        currentPosition_ = Position::END_MIDDLE_OF_GRILL;

        robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
        continueAfterTurn();

        // Nous sommes a la fin en haut de la grille
        currentPosition_ = Position::END_TOP_OF_GRILL;
    }
}

void Path::doPathFromGrillToA()
{
    doFirstHalfGrill();
    doSecondHalfGrill();

    robot_.lineFollower().followLine(StopCondition::RIGHT_TURN);
    robot_.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

    // Nous sommes a A
    currentPosition_ = Position::A;
}

void Path::doPath()
{
    selectBCDirection();

    _delay_ms(WAIT_BEFORE_START_PATH_DELAY_2000MS);

    Position startingPosition = findStartingPosition();

    if (startingPosition == Position::A)
    {
        currentPosition_ = Position::B;
        finishPathFromB();
    }
    else
    {
        currentPosition_ = Position::START_MIDDLE_OF_GRILL;
        finishPathFromGrill();
    }

    showPathIsFinished();
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
