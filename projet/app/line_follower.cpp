#include "line_follower.h"

#define SCALE_FACTOR 10
#define MAX_CORRECTION 127
#define INTEGRAL_LIMIT 10000

// Obtenu a la suite du calcul suivant : 8000000 / 1024 * 1000ms = 7.8125 = 8
#define CALCULATED_DELAY_CONSTANT 8

bool gTimerIsExpired = false;

ISR(TIMER1_COMPA_vect)
{
    gTimerIsExpired = true;
    Timer1::disallowInterrupts(OutputComparePin::A); // Desactive les interuptions du timer, on veut seulement active l'interuption si on repart la minuterie.
}

static inline int16_t clamp(int16_t value, int16_t minVal, int16_t maxVal)
{
    return (value < minVal) ? minVal : (value > maxVal ? maxVal : value);
}

LineFollower::LineFollower(Timer1 &delayTimer, Wheels &wheels, LineSensor &lineSensor)
    : delayTimer_(delayTimer), wheels_(wheels), lineSensor_(lineSensor)
{
    delayTimer_.initializeTimerForDelays();
}

int8_t LineFollower::calculateCorrection(int8_t error)
{
    errorIntegral_ += error;

    if (errorIntegral_ > INTEGRAL_LIMIT || errorIntegral_ < -INTEGRAL_LIMIT)
    {
        errorIntegral_ = 0;
    }

    int32_t correction = ((int32_t)kp_ * error +
                          (int32_t)ki_ * errorIntegral_ +
                          (int32_t)kd_ * (error - previousError_)) >>
                         SCALE_FACTOR;

    previousError_ = error;

    correction = clamp(correction, -MAX_CORRECTION, MAX_CORRECTION);

    return (int8_t)correction;
}

void LineFollower::applyCorrection(Direction direction)
{
    int8_t error = lineSensor_.readPosition() - 127;

    if (direction == Direction::BACKWARDS)
    {
        error = -error;
    }

    int8_t correction = calculateCorrection(error);

    int16_t adjustedRightWheelSpeed = rightWheelBaseSpeed - correction;
    int16_t adjustedLeftWheelSpeed = leftWheelBaseSpeed + correction;

    wheels_.setSpeedRight((uint8_t)clamp(adjustedRightWheelSpeed, 0, 255), direction);
    wheels_.setSpeedLeft((uint8_t)clamp(adjustedLeftWheelSpeed, 0, 255), direction);
}

void LineFollower::followLine(StopCondition condition)
{
    // Boost les roues avant de commencer a detecter la ligne
    wheels_.goForward(255);
    _delay_ms(10);

    switch (condition)
    {
    case StopCondition::LEFT_TURN:
        while (!lineSensor_.leftTurnDetected())
        {
            applyCorrection(Direction::FORWARD);
        }
        wheels_.stop();
        break;

    case StopCondition::RIGHT_TURN:
        while (!lineSensor_.rightTurnDetected())
        {
            applyCorrection(Direction::FORWARD);
        }
        wheels_.stop();
        break;

    case StopCondition::CROSS:
        while (!lineSensor_.crossDetected())
        {
            applyCorrection(Direction::FORWARD);
        }
        wheels_.stop();
        break;

    case StopCondition::NO_LINE:
        while (!lineSensor_.noLineDetected())
        {
            applyCorrection(Direction::FORWARD);
        }
        wheels_.stop();
        break;

    case StopCondition::PICKAXE_TURN:
        while (!lineSensor_.pickaxeTurnDetected())
        {
            applyCorrection(Direction::FORWARD);
        }
        wheels_.stop();
        break;
    }
}

StopCondition LineFollower::followLine(StopCondition firstCondition, StopCondition secondCondition)
{
    // Boost les roues avant de commencer a detecter la ligne
    wheels_.goForward(255);
    _delay_ms(10);

    while (true)
    {
        applyCorrection(Direction::FORWARD);

        switch (firstCondition)
        {
        case StopCondition::LEFT_TURN:
            if (lineSensor_.leftTurnDetected())
            {
                wheels_.stop();
                return firstCondition;
            }
            break;

        case StopCondition::RIGHT_TURN:
            if (lineSensor_.rightTurnDetected())
            {
                wheels_.stop();
                return firstCondition;
            }
            break;

        case StopCondition::CROSS:
            if (lineSensor_.crossDetected())
            {
                wheels_.stop();
                return firstCondition;
            }
            break;

        case StopCondition::NO_LINE:
            if (lineSensor_.noLineDetected())
            {
                wheels_.stop();
                return firstCondition;
            }
            break;

        case StopCondition::PICKAXE_TURN:
            if (lineSensor_.pickaxeTurnDetected())
            {
                wheels_.stop();
                return firstCondition;
            }
            break;
        }

        switch (secondCondition)
        {
        case StopCondition::LEFT_TURN:
            if (lineSensor_.leftTurnDetected())
            {
                wheels_.stop();
                return secondCondition;
            }
            break;

        case StopCondition::RIGHT_TURN:
            if (lineSensor_.rightTurnDetected())
            {
                wheels_.stop();
                return secondCondition;
            }
            break;

        case StopCondition::CROSS:
            if (lineSensor_.crossDetected())
            {
                wheels_.stop();
                return secondCondition;
            }
            break;

        case StopCondition::NO_LINE:
            if (lineSensor_.noLineDetected())
            {
                wheels_.stop();
                return secondCondition;
            }
            break;

        case StopCondition::PICKAXE_TURN:
            if (lineSensor_.pickaxeTurnDetected())
            {
                wheels_.stop();
                return firstCondition;
            }
            break;
        }
    }
}

void LineFollower::followLine(uint16_t delayMs)
{
    // Boost les roues avant de commencer a detecter la ligne
    wheels_.goForward(255);
    _delay_ms(10);

    gTimerIsExpired = false;
    delayTimer_.startTimer(OutputComparePin::A, delayMs * CALCULATED_DELAY_CONSTANT);

    while (!gTimerIsExpired)
    {
        applyCorrection(Direction::FORWARD);
    }

    wheels_.stop();
}

void LineFollower::followLine()
{
    // Boost les roues avant de commencer a detecter la ligne
    wheels_.goForward(255);
    _delay_ms(10);

    while (true)
    {
        applyCorrection(Direction::FORWARD);
    }
}

void LineFollower::followLineBackwards(uint16_t delayMs)
{
    wheels_.goBackwards(255);
    _delay_ms(10);

    gTimerIsExpired = false;
    delayTimer_.startTimer(OutputComparePin::A, delayMs * CALCULATED_DELAY_CONSTANT);

    while (!gTimerIsExpired)
    {
        applyCorrection(Direction::BACKWARDS);
    }

    wheels_.stop();
}

void LineFollower::smartTurnLeft(TurnType lineType)
{
    switch (lineType)
    {
    case TurnType::SHARP_TURN:
        wheels_.goForward(90, 2500);

        wheels_.stop(500);

        wheels_.pivotLeft(255);
        _delay_ms(10);

        while (!lineSensor_.leftDetected())
        {
            wheels_.pivotLeft(90);
        }

        while (!lineSensor_.middleDetected())
        {
            wheels_.pivotLeft(90);
        }

        wheels_.stop(500);

        break;

    case TurnType::SMALL_TURN:
        wheels_.goForward(90, 2000);

        wheels_.stop(500);

        wheels_.pivotLeft(255);
        _delay_ms(10);

        while (!lineSensor_.leftDetected())
        {
            wheels_.pivotLeft(90);
        }

        while (!lineSensor_.middleDetected())
        {
            wheels_.pivotLeft(90);
        }

        wheels_.stop(500);

        break;

    case TurnType::CROSSROAD:
        wheels_.goForward(90, 1000);
        followLine(1800);

        wheels_.stop(500);

        wheels_.pivotLeft(255);
        _delay_ms(50);

        while (!lineSensor_.leftDetected())
        {
            wheels_.pivotLeft(90);
        }

        while (!lineSensor_.middleDetected())
        {
            wheels_.pivotLeft(90);
        }

        wheels_.stop(500);

        break;

    case TurnType::ON_PLACE:
        wheels_.pivotLeft(255);
        _delay_ms(50);

        while (!lineSensor_.leftDetected())
        {
            wheels_.pivotLeft(90);
        }

        while (!lineSensor_.middleDetected())
        {
            wheels_.pivotLeft(90);
        }

        wheels_.stop(500);

        break;
    }
}

void LineFollower::smartTurnRight(TurnType lineType)
{
    switch (lineType)
    {
    case TurnType::SHARP_TURN:
        wheels_.goForward(90, 2500);

        wheels_.stop(500);

        wheels_.pivotRight(255);
        _delay_ms(10);

        while (!lineSensor_.rightDetected())
        {
            wheels_.pivotRight(90);
        }

        while (!lineSensor_.middleDetected())
        {
            wheels_.pivotRight(90);
        }

        wheels_.stop(500);

        break;

    case TurnType::SMALL_TURN:
        wheels_.goForward(90, 2000);

        wheels_.stop(500);

        wheels_.pivotRight(255);
        _delay_ms(10);

        while (!lineSensor_.rightDetected())
        {
            wheels_.pivotRight(90);
        }

        while (!lineSensor_.middleDetected())
        {
            wheels_.pivotRight(90);
        }

        wheels_.stop(500);

        break;

    case TurnType::CROSSROAD:
        wheels_.goForward(90, 1000);
        followLine(1800);

        wheels_.stop(500);

        wheels_.pivotRight(255);
        _delay_ms(50);

        while (!lineSensor_.rightDetected())
        {
            wheels_.pivotRight(90);
        }

        while (!lineSensor_.middleDetected())
        {
            wheels_.pivotRight(90);
        }

        wheels_.stop(500);

        break;

    case TurnType::ON_PLACE:
        wheels_.pivotRight(255);
        _delay_ms(50);

        while (!lineSensor_.rightDetected())
        {
            wheels_.pivotRight(90);
        }

        while (!lineSensor_.middleDetected())
        {
            wheels_.pivotRight(90);
        }

        wheels_.stop(500);

        break;
    }
}
