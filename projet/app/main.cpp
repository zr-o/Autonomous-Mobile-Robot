#include "path.h"

int main(){
  Robot& robot = Robot::createRobot();

robot.lineFollower().followLine(StopCondition::CROSS);
robot.wheels().goForward(90, 500);
robot.lineFollower().followLine(2300);

//DETECTION DU POTEAU L
robot.wheels().stop(1000);

robot.lineFollower().smartTurnRight(TurnType::ON_PLACE);
robot.lineFollower().followLine(StopCondition::LEFT_TURN);
robot.lineFollower().smartTurnLeft(TurnType::SHARP_TURN);

//DETECTION DU POTEAU K
robot.lineFollower().followLine(2000);
robot.wheels().stop(1000);

robot.lineFollower().followLineBackwards(2000);
robot.wheels().stop(1000);
robot.lineFollower().smartTurnLeft(TurnType::ON_PLACE);
robot.lineFollower().followLine(StopCondition::CROSS);
robot.wheels().goForward(90, 500);
robot.lineFollower().followLine(StopCondition::RIGHT_TURN);
robot.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

//DETECTION DU POTEAU M (Pas besoin)
robot.lineFollower().followLine(2000);
robot.wheels().stop(1000);

robot.lineFollower().followLineBackwards(2000);
robot.wheels().stop(1000);
robot.lineFollower().followLine(StopCondition::RIGHT_TURN);
robot.wheels().goForward(90, 500);
robot.lineFollower().followLine(StopCondition::RIGHT_TURN);
robot.lineFollower().smartTurnRight(TurnType::CROSSROAD);
robot.lineFollower().followLine(StopCondition::CROSS);
robot.lineFollower().smartTurnLeft(TurnType::CROSSROAD);

//DETECTION DU POTEAU O
robot.lineFollower().followLine(2000);
robot.wheels().stop(1000);

robot.lineFollower().followLineBackwards(2000);
robot.wheels().stop(1000);
robot.lineFollower().smartTurnRight(TurnType::ON_PLACE);
robot.lineFollower().followLine(StopCondition::CROSS);
robot.lineFollower().smartTurnLeft(TurnType::SHARP_TURN);

//DETECTION DU POTEAU N
robot.lineFollower().followLine(2000);
robot.wheels().stop(1000);

robot.lineFollower().followLineBackwards(2000);
robot.wheels().stop(1000);
robot.lineFollower().smartTurnLeft(TurnType::ON_PLACE);
robot.lineFollower().followLine(StopCondition::CROSS);
robot.wheels().goForward(90, 500);
robot.lineFollower().followLine(StopCondition::CROSS);
robot.lineFollower().smartTurnRight(TurnType::SHARP_TURN);

//DETECTION DU POTEAU P(Pas besoin)
robot.lineFollower().followLine(2000);
robot.wheels().stop(1000);

robot.lineFollower().followLineBackwards(2000);
robot.wheels().stop(1000);
robot.lineFollower().followLine(StopCondition::RIGHT_TURN);
robot.wheels().goForward(90, 500);
robot.lineFollower().followLine(StopCondition::RIGHT_TURN);
robot.lineFollower().smartTurnRight(TurnType::SHARP_TURN);
robot.lineFollower().followLine(StopCondition::RIGHT_TURN);
robot.wheels().goForward(90, 500);
robot.lineFollower().followLine(StopCondition::RIGHT_TURN);
robot.wheels().goForward(90, 500);
robot.lineFollower().followLine(StopCondition::RIGHT_TURN);

















}