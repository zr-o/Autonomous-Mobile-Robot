#include "robot.h"
#include "debug.h"

int main()
{
    Robot &robot = Robot::createRobot();

    uint8_t savedDirection[2];
    uint8_t savedValuesCounter = 0;

    while (savedValuesCounter < 2)
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
    DEBUG_PRINT(savedDirection[1]);
}