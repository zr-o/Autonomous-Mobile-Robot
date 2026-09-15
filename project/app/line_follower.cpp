#include "line_follower.h"

// Valeur calibrés selon le niveau de batterie de robot et selon le contexte d'utilisation
#define SCALE_FACTOR 10
#define MAX_CORRECTION 127
#define INTEGRAL_LIMIT 10000
#define BOOST_DELAY_10MS 10
#define BOOST_DELAY_50MS 50
#define STOP_TO_STABILIZE_500MS 500
#define WHEELS_BASE_SPEED_90 90
#define GO_PAST_LINE_DELAY_2000MS 2000
#define GO_PAST_LINE_DELAY_2500MS 2500
#define GO_PAST_LINE_DELAY_1800MS 1800
#define SKIP_LINE_DELAY_1000MS 1000

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
    int8_t error = lineSensor_.readPosition() - BITS_8_MID_VALUE;

    if (direction == Direction::BACKWARDS)
    {
        error = -error;
    }

    int8_t correction = calculateCorrection(error);

    int16_t adjustedRightWheelSpeed = rightWheelBaseSpeed - correction;
    int16_t adjustedLeftWheelSpeed = leftWheelBaseSpeed + correction;

    wheels_.setSpeedRight((uint8_t)clamp(adjustedRightWheelSpeed, 0, BITS_8_MAX_VALUE), direction);
    wheels_.setSpeedLeft((uint8_t)clamp(adjustedLeftWheelSpeed, 0, BITS_8_MAX_VALUE), direction);
}

void LineFollower::followLine(StopCondition condition)
{
    // Boost les roues avant de commencer a detecter la ligne
    wheels_.goForward(BITS_8_MAX_VALUE);
    _delay_ms(BOOST_DELAY_10MS);

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
    wheels_.goForward(BITS_8_MAX_VALUE);
    _delay_ms(BOOST_DELAY_10MS);

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
    wheels_.goForward(BITS_8_MAX_VALUE);
    _delay_ms(BOOST_DELAY_10MS);

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
    wheels_.goForward(BITS_8_MAX_VALUE);
    _delay_ms(BOOST_DELAY_10MS);

    while (true)
    {
        applyCorrection(Direction::FORWARD);
    }
}

void LineFollower::followLineBackwards(uint16_t delayMs)
{
    wheels_.goBackwards(BITS_8_MAX_VALUE);
    _delay_ms(BOOST_DELAY_10MS);

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
        wheels_.goForward(WHEELS_BASE_SPEED_90, GO_PAST_LINE_DELAY_2500MS);

        wheels_.stop(STOP_TO_STABILIZE_500MS);

        // On boost les roues
        wheels_.pivotLeft(BITS_8_MAX_VALUE);
        _delay_ms(BOOST_DELAY_10MS);

        while (!lineSensor_.leftDetected())
        {
            wheels_.pivotLeft(WHEELS_BASE_SPEED_90);
        }

        while (!lineSensor_.middleDetected())
        {
            wheels_.pivotLeft(WHEELS_BASE_SPEED_90);
        }

        wheels_.stop(STOP_TO_STABILIZE_500MS);

        break;

    case TurnType::SMALL_TURN:
        wheels_.goForward(WHEELS_BASE_SPEED_90, GO_PAST_LINE_DELAY_2000MS);

        wheels_.stop(STOP_TO_STABILIZE_500MS);

        // On boost les roues
        wheels_.pivotLeft(BITS_8_MAX_VALUE);
        _delay_ms(BOOST_DELAY_10MS);

        while (!lineSensor_.leftDetected())
        {
            wheels_.pivotLeft(WHEELS_BASE_SPEED_90);
        }

        while (!lineSensor_.middleDetected())
        {
            wheels_.pivotLeft(WHEELS_BASE_SPEED_90);
        }

        wheels_.stop(STOP_TO_STABILIZE_500MS);

        break;

    case TurnType::CROSSROAD:
        wheels_.goForward(WHEELS_BASE_SPEED_90, SKIP_LINE_DELAY_1000MS);
        followLine(GO_PAST_LINE_DELAY_1800MS);

        wheels_.stop(STOP_TO_STABILIZE_500MS);

        // On boost les roues
        wheels_.pivotLeft(BITS_8_MAX_VALUE);
        _delay_ms(BOOST_DELAY_50MS);

        while (!lineSensor_.leftDetected())
        {
            wheels_.pivotLeft(WHEELS_BASE_SPEED_90);
        }

        while (!lineSensor_.middleDetected())
        {
            wheels_.pivotLeft(WHEELS_BASE_SPEED_90);
        }

        wheels_.stop(STOP_TO_STABILIZE_500MS);

        break;

    case TurnType::ON_PLACE:
        // On boost les roues
        wheels_.pivotLeft(BITS_8_MAX_VALUE);
        _delay_ms(BOOST_DELAY_50MS);

        while (!lineSensor_.leftDetected())
        {
            wheels_.pivotLeft(WHEELS_BASE_SPEED_90);
        }

        while (!lineSensor_.middleDetected())
        {
            wheels_.pivotLeft(WHEELS_BASE_SPEED_90);
        }

        wheels_.stop(STOP_TO_STABILIZE_500MS);

        break;
    }
}

void LineFollower::smartTurnRight(TurnType lineType)
{
    switch (lineType)
    {
    case TurnType::SHARP_TURN:
        wheels_.goForward(WHEELS_BASE_SPEED_90, GO_PAST_LINE_DELAY_2500MS);

        wheels_.stop(STOP_TO_STABILIZE_500MS);

        // On boost les roues
        wheels_.pivotRight(BITS_8_MAX_VALUE);
        _delay_ms(BOOST_DELAY_10MS);

        while (!lineSensor_.rightDetected())
        {
            wheels_.pivotRight(WHEELS_BASE_SPEED_90);
        }

        while (!lineSensor_.middleDetected())
        {
            wheels_.pivotRight(WHEELS_BASE_SPEED_90);
        }

        wheels_.stop(STOP_TO_STABILIZE_500MS);

        break;

    case TurnType::SMALL_TURN:
        wheels_.goForward(WHEELS_BASE_SPEED_90, GO_PAST_LINE_DELAY_2000MS);

        wheels_.stop(STOP_TO_STABILIZE_500MS);

        // On boost les roues
        wheels_.pivotRight(BITS_8_MAX_VALUE);
        _delay_ms(BOOST_DELAY_10MS);

        while (!lineSensor_.rightDetected())
        {
            wheels_.pivotRight(WHEELS_BASE_SPEED_90);
        }

        while (!lineSensor_.middleDetected())
        {
            wheels_.pivotRight(WHEELS_BASE_SPEED_90);
        }

        wheels_.stop(STOP_TO_STABILIZE_500MS);

        break;

    case TurnType::CROSSROAD:
        wheels_.goForward(WHEELS_BASE_SPEED_90, SKIP_LINE_DELAY_1000MS);
        followLine(GO_PAST_LINE_DELAY_1800MS);

        wheels_.stop(STOP_TO_STABILIZE_500MS);

        // On boost les roues
        wheels_.pivotRight(BITS_8_MAX_VALUE);
        _delay_ms(BOOST_DELAY_50MS);

        while (!lineSensor_.rightDetected())
        {
            wheels_.pivotRight(WHEELS_BASE_SPEED_90);
        }

        while (!lineSensor_.middleDetected())
        {
            wheels_.pivotRight(WHEELS_BASE_SPEED_90);
        }

        wheels_.stop(STOP_TO_STABILIZE_500MS);

        break;

    case TurnType::ON_PLACE:
        // On boost les roues
        wheels_.pivotRight(BITS_8_MAX_VALUE);
        _delay_ms(BOOST_DELAY_50MS);

        while (!lineSensor_.rightDetected())
        {
            wheels_.pivotRight(WHEELS_BASE_SPEED_90);
        }

        while (!lineSensor_.middleDetected())
        {
            wheels_.pivotRight(WHEELS_BASE_SPEED_90);
        }

        wheels_.stop(STOP_TO_STABILIZE_500MS);

        break;
    }
}
