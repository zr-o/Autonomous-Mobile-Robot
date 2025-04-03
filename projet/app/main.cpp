#include "robot.h"
#include "debug.h"

int main()
{
    Robot &robot = Robot::createRobot();

    // PARTIE BOUTON DEBUT
    /*uint8_t savedDirection[2];
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
    DEBUG_PRINT(savedDirection[1]);*/

    while (true){
        // Fonction qui fait crash apres 30 s
        robot.lineFollower().followLine();

        // Apres 30 seconde, la lumiere cesse d'oscillier et reste verte ou rouge (le programme crash)
        robot.led().lightUp(Color::GREEN);
        _delay_ms(100);
        robot.led().lightUp(Color::RED);
        _delay_ms(100);
    }
}