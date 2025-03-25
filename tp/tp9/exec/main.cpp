#define F_CPU 8000000UL

#include <util/delay.h>
#include "led.h"
#include "tone.h"
#include "wheels.h"
#include "control_unit.h"
#include "global_functions.h"
#include "debug.h"

#define DELAY_250_MS 250
#define DELAY_2640_MS_CALCULATED 20650
#define DELAY_2176_MS_CALCULATED 17000
#define EXPERIMENTAL_PERCENTAGE_50 50

volatile bool gExpiredTimer = false;

ISR(TIMER1_COMPA_vect)
{

    gExpiredTimer = true;
    TIMSK1 &= ~(1 << OCIE1A);
}

int main()
{
    Timer0 toneTimer;
    Timer1 delayTimer;
    Timer2 pwmTimer;
    delayTimer.initializeTimerForDelays(gExpiredTimer);

    Led led = Led(Port::A, Pin::N1, Pin::N2);
    Wheels wheels = Wheels(&delayTimer, &pwmTimer);
    Tone tone = Tone(&toneTimer);

    ControlUnit controlUnit = ControlUnit();
    Instruction currentInstruction = controlUnit.getCurrentInstruction();
    uint8_t currentOperand = controlUnit.getCurrentOperand();

    led.lightUp(Color::RED);
    _delay_ms(DELAY_250_MS);
    led.lightUp(Color::GREEN);
    _delay_ms(DELAY_250_MS);
    led.lightUp(Color::RED);
    _delay_ms(DELAY_250_MS);
    led.lightUp(Color::GREEN);
    _delay_ms(DELAY_250_MS);

    DEBUG_PRINT(uint8_t(currentInstruction));
    DEBUG_PRINT(currentOperand);

    while (currentInstruction != Instruction::FIN)
    {
        controlUnit.fetch();
        controlUnit.decode();

        currentInstruction = controlUnit.getCurrentInstruction();
        currentOperand = controlUnit.getCurrentOperand();

        DEBUG_PRINT(uint8_t(currentInstruction));
        DEBUG_PRINT(currentOperand);

        switch (currentInstruction)
        {
        case Instruction::ATT:
            variableDelayMs(25 * currentOperand);
            break;

        case Instruction::DAL:
            if (currentOperand == 1)
            {
                led.lightUp(Color::GREEN);
            }
            if (currentOperand == 2)
            {
                led.lightUp(Color::RED);
            }
            break;

        case Instruction::DET:
            led.lightUp(Color::OFF);
            break;

        case Instruction::MAR1:
            wheels.stop();
            break;

        case Instruction::MAR2:
            wheels.stop();
            break;

        case Instruction::MAV:
            wheels.goForward(((currentOperand * 100) / 255));
            break;

        case Instruction::MRE:
            wheels.goBackwards(((currentOperand * 100) / 255));
            break;

        case Instruction::TRD:
            wheels.goRight(EXPERIMENTAL_PERCENTAGE_50, DELAY_2640_MS_CALCULATED); // valeurs calcule experimentalement
            break;

        case Instruction::TRG:
            wheels.goLeft(EXPERIMENTAL_PERCENTAGE_50, DELAY_2176_MS_CALCULATED); // valeurs calcule experimentalement
            break;

        case Instruction::SGO:
            tone.playNote(currentOperand);
            break;

        case Instruction::SAR:
            tone.turnOffNote();
            break;

        case Instruction::FIN:
            tone.turnOffNote();
            wheels.stop();
            led.lightUp(Color::OFF);

        default:
            break;
        }
    }
}
