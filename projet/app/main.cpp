#include "robot.h"
#include "debug.h"

Robot &robot = Robot::createRobot();

    
int main()
{

    // PARTIE BOUTON DEBUT
    uint8_t savedDirection[2] = {1, 1};
    uint8_t savedValuesCounter = 0;

    /*while (true){
        //DEBUG_PRINT(robot.lineFollower().calculateCorrection(robot.lineSensor().readPosition() - 127));
       robot.lineFollower().applyCorrection();
        //DEBUG_PRINT(robot.lineSensor().readPosition());
    }*/
    
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

    // DETECTION DE DEBUT A OU J
    StopCondition s = robot.lineFollower().followLine(StopCondition::CROSS, StopCondition::NO_LINE);

    if (s == StopCondition::CROSS)
    {
        robot.led().lightUp(Color::RED);
    }
    else
    {
        robot.led().lightUp(Color::GREEN);
    }

    // PARTIE BC

    robot.tone().playNote(45);
    _delay_ms(1000);
    robot.tone().turnOffNote();

    if (savedDirection[0] == 1)
    {
        robot.wheels().goForward(100, 500);
        while (robot.lineSensor().noLineDetected())
        {   
            
            robot.wheels().goLeft(110);
        }
    }

    if (savedDirection[0] == 0)
    {
        robot.wheels().goForward(100, 500);
        while (robot.lineSensor().noLineDetected())
        {
            robot.wheels().goRight(110);
        }
    }

    robot.wheels().stop(500);
    robot.lineFollower().followLine(StopCondition::NO_LINE);

    robot.tone().playNote(45);
    _delay_ms(1000);
    robot.tone().turnOffNote();

    if (savedDirection[1] == 1)
    {   
        robot.wheels().goForward(100, 500);
        while (robot.lineSensor().noLineDetected())
        {   
            robot.wheels().goLeft(110);
        }
    }

    if (savedDirection[1] == 0)
    {   
        robot.wheels().goForward(100, 500);
        while (robot.lineSensor().noLineDetected())
        {   
            robot.wheels().goRight(110);
        }
    }

    robot.wheels().stop(500);
    
 
    StopCondition directionChange = robot.lineFollower().followLine(StopCondition::RIGHT_TURN, StopCondition::LEFT_TURN);

    if (directionChange == StopCondition::RIGHT_TURN)
    {
        robot.wheels().goForward(100, 1000);
        while (robot.lineSensor().noLineDetected())
        {
            robot.wheels().goRight(90);
        }
    }

    if (directionChange == StopCondition::LEFT_TURN)
    {
        robot.wheels().goForward(100, 1000);
        while (robot.lineSensor().noLineDetected())
        {
            robot.wheels().goLeft(90);
        }
    }
    robot.wheels().stop(500);

    robot.lineFollower().followLine(StopCondition::RIGHT_TURN);

    robot.wheels().stop(500);
    robot.wheels().goForward(100, 2200);

    while(!robot.lineSensor().rightDetected()){
    robot.wheels().setSpeedLeft(125, Direction::FORWARD);
    robot.wheels().setSpeedRight(125, Direction::BACKWARDS);}
    robot.wheels().stop(500);




    //TEST POUR VIRAGE DE 90 A GAUCHE POUR LA PARTI DE LA GRILLE
    /* robot.lineFollower().followLine(StopCondition::CROSS);
    robot.wheels().stop(500);
    robot.wheels().goForward(100, 2200);

    while(!robot.lineSensor().rightDetected()){
    robot.wheels().setSpeedLeft(125, Direction::FORWARD);
    robot.wheels().setSpeedRight(125, Direction::BACKWARDS);
}
robot.wheels().stop(1000);
    
    robot.lineFollower().followLine(StopCondition::LEFT_TURN);
    robot.wheels().stop(500);
    robot.wheels().goForward(100, 2200);

while(!robot.lineSensor().leftDetected()){
    robot.wheels().setSpeedLeft(125, Direction::BACKWARDS);
    robot.wheels().setSpeedRight(125, Direction::FORWARD);
}
robot.wheels().stop(1000);

//boost
robot.wheels().setSpeedLeft(255, Direction::BACKWARDS);
    robot.wheels().setSpeedRight(255, Direction::FORWARD);
    _delay_ms(10);


while(!robot.lineSensor().leftDetected()){
    robot.wheels().setSpeedLeft(125, Direction::BACKWARDS);
    robot.wheels().setSpeedRight(125, Direction::FORWARD);
}
robot.wheels().stop(1000);

robot.lineFollower().followLine(StopCondition::CROSS);

robot.wheels().stop(1000);

robot.wheels().goForward(100, 1000);

robot.lineFollower().followLine(StopCondition::RIGHT_TURN);*/


// Boucle maison D a F
robot.lineFollower().followLine(StopCondition::RIGHT_TURN);

robot.wheels().stop(1000);
robot.wheels().goForward(100,1000);

robot.lineFollower().followLine(StopCondition::RIGHT_TURN); // A F

robot.wheels().stop(500);
    robot.wheels().goForward(100, 2200);

    while(!robot.lineSensor().rightDetected()){
    robot.wheels().setSpeedLeft(125, Direction::FORWARD);
    robot.wheels().setSpeedRight(125, Direction::BACKWARDS);}
    robot.wheels().stop(500);

    // Detection du poteau H
    bool hPostFlag = false;

    robot.lineFollower().followLine(StopCondition::RIGHT_TURN); // A G

    robot.wheels().stop(500);
    robot.wheels().goForward(100, 2200);

    while(!robot.lineSensor().rightDetected()){
    robot.wheels().setSpeedLeft(125, Direction::FORWARD);
    robot.wheels().setSpeedRight(125, Direction::BACKWARDS);}

    robot.wheels().stop(500);

    /*if (robot.distanceSensor().readDistance() > 20) {
        hPostFlag = true;
    }*/

        

    // Si le poteau H est detecte
    if (hPostFlag) {
        while(!robot.lineSensor().rightDetected()){
    robot.wheels().setSpeedLeft(125, Direction::FORWARD);
    robot.wheels().setSpeedRight(125, Direction::BACKWARDS);}   //tourne vers I
    robot.wheels().stop(500);
    robot.lineFollower().followLine(StopCondition::RIGHT_TURN); //avance vers I
    
    robot.wheels().stop(500);
    robot.wheels().goForward(100, 2200);
    
    while(!robot.lineSensor().rightDetected()){
        robot.wheels().setSpeedLeft(125, Direction::FORWARD);
        robot.wheels().setSpeedRight(125, Direction::BACKWARDS);}   //tourne vers E
}
else {
    robot.lineFollower().followLine(StopCondition::RIGHT_TURN); //avance vers H
    robot.wheels().stop(500);
    robot.wheels().goForward(100, 2200);
    while(!robot.lineSensor().rightDetected()){
        robot.wheels().setSpeedLeft(125, Direction::FORWARD);
        robot.wheels().setSpeedRight(125, Direction::BACKWARDS);}   //tourne vers I
        robot.wheels().stop(500);
        robot.lineFollower().followLine(StopCondition::RIGHT_TURN); //avance vers I
    
    robot.wheels().stop(500);
    robot.wheels().goForward(100, 2200);
    
    while(!robot.lineSensor().rightDetected()){
        robot.wheels().setSpeedLeft(125, Direction::FORWARD);   //tourne vers E
        robot.wheels().setSpeedRight(125, Direction::BACKWARDS);}
}

robot.wheels().stop(500);
robot.lineFollower().followLine(StopCondition::CROSS);
robot.wheels().stop(500);
robot.wheels().goForward(100, 2200);
while(!robot.lineSensor().rightDetected()){
    robot.wheels().setSpeedLeft(125, Direction::FORWARD);
    robot.wheels().setSpeedRight(125, Direction::BACKWARDS);}
    robot.wheels().stop(500);


robot.lineFollower().followLine(StopCondition::RIGHT_TURN);
robot.wheels().stop(500);
robot.wheels().goForward(100, 1500);
robot.lineFollower().followLine(StopCondition::RIGHT_TURN);


robot.wheels().stop(500);
robot.wheels().goForward(100, 2200);
while(!robot.lineSensor().rightDetected()){
    robot.wheels().setSpeedLeft(125, Direction::FORWARD);
    robot.wheels().setSpeedRight(125, Direction::BACKWARDS);}
    robot.wheels().stop(500);


    robot.lineFollower().followLine(StopCondition::CROSS);

    


    /*
    // grille

    if(directionChange == StopCondition::CROSS) {

        if (distance < 20) {
            robot.lineFollower().followLine(); 
        }

       turnRightUntilLine();
        if (distance > 20) {
            robot.wheels().stop();
            hPostFlag = true;
        }

        turnLeftUntilLine();
        turnLeftUntilLine(); // pour aller a M
        
    }
    bool robotAtN = false;
    if(directionChange == StopCondition::CROSS) {

         if (distance < 20) {
            robot.lineFollower().followLine();
        }

       turnRightUntilLine();
        if (distance > 20) {
            robot.wheels().stop();
            hPostFlag = true;
        }

        turnLeftUntilLine();
        turnLeftUntilLine(); // pour aller a P


    }
    */
}