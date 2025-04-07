#include "robot.h"
#include "debug.h"

int main()
{

    Robot &robot = Robot::createRobot();

    // PARTIE BOUTON DEBUT
    uint8_t savedDirection[2] = {1, 0};
    uint8_t savedValuesCounter = 0;

    /*while (savedValuesCounter < 2)
    {

        if (robot.externButton().isPressed())
        {
            savedDirection[savedValuesCounter++] = 1; // 0 pour droite, 1 pour gauche
            while (robot.externButton().isPressed())
            {
                robot.led().lightUp(Color::RED);
            }
        }

        if (robot.motherboardButton().isPressed())
        {
            savedDirection[savedValuesCounter++] = 0; // 0 pour droite, 1 pour gauche
            while (robot.motherboardButton().isPressed())
            {
                robot.led().lightUp(Color::GREEN);
            }
        }
        robot.led().lightUp(Color::OFF);
    }

    DEBUG_PRINT(savedDirection[0]);
    _delay_ms(1000);
    DEBUG_PRINT(savedDirection[1]);*/


/*StopCondition s = robot.lineFollower().followLine(StopCondition::CROSS, StopCondition::NO_LINE);

if (s == StopCondition::CROSS){
    robot.led().lightUp(Color::RED);
} else{
    robot.led().lightUp(Color::GREEN);
}*/


_delay_ms(2000);

    if (savedDirection[0] == 1) {
        robot.wheels().goForward(255, 800);
        while (robot.lineSensor().noLineDetected()) {
            robot.wheels().goLeft(120);
        }
        DEBUG_PRINT("tourner a gauche");
    }

    if (savedDirection[0] == 0) {
        robot.wheels().goForward(255, 800);
        while (robot.lineSensor().noLineDetected()) {
            robot.wheels().goRight(120);
        }
    }

    robot.lineFollower().followLine(StopCondition::NO_LINE);

    if (savedDirection[1] == 1) {
        robot.wheels().goForward(255, 800);
        while (robot.lineSensor().noLineDetected()) {
            robot.wheels().goLeft(120);
        }
    }

    if (savedDirection[1] == 0) {
        robot.wheels().goForward(255, 800);
        while (robot.lineSensor().noLineDetected()) {
            robot.wheels().goRight(120);
        }
    }

    StopCondition directionChange = robot.lineFollower().followLine(StopCondition::RIGHT_TURN, StopCondition::LEFT_TURN);

    if (directionChange == StopCondition::RIGHT_TURN) {
        robot.wheels().goForward(255, 800);
        robot.wheels().goRight(255, 2000);
    }

    if (directionChange == StopCondition::LEFT_TURN) {
        robot.wheels().goForward(255, 800);
        robot.wheels().goLeft(255, 2000);
    }

    robot.lineFollower().followLine(StopCondition::RIGHT_TURN);





}