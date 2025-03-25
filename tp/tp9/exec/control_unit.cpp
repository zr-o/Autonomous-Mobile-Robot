#include "control_unit.h"

#define DELAY_MEMORY_MS 5

static const uint8_t BYTE_SHIFT = 8;

ControlUnit::ControlUnit()
{
    uint8_t temp = 0;

    mem_.lecture(currentInstructionAddress_, &temp);
    nCodeBytes_ = temp;
    nCodeBytes_ <<= BYTE_SHIFT;
    currentInstructionAddress_++;
    _delay_ms(DELAY_MEMORY_MS);

    mem_.lecture(currentInstructionAddress_, &temp);
    nCodeBytes_ |= temp; // Lecture du deuxieme octet
    currentInstructionAddress_++;
    _delay_ms(DELAY_MEMORY_MS);

    while (currentInstruction_ != 0x01)
    {
    fetch();
    }
}

void ControlUnit::fetch()
{
    mem_.lecture(currentInstructionAddress_, &currentInstruction_);
    currentInstructionAddress_++;
    _delay_ms(DELAY_MEMORY_MS);

    mem_.lecture(currentInstructionAddress_, &currentOperand_);
    currentInstructionAddress_++;
    _delay_ms(DELAY_MEMORY_MS);
}

void ControlUnit::decode()
{

    switch (Instruction(currentInstruction_))
    {
    case Instruction::DBC:
        loopReturnAddress_ = currentInstructionAddress_;
        loopCounter_ = currentOperand_;
        fetch();
        break;

    case Instruction::FBC:
        if (loopCounter_ > 0)
        {
            currentInstructionAddress_ = loopReturnAddress_;
            loopCounter_--;
        }
        fetch();
        break;

    default:
        break;
    }
}

uint8_t ControlUnit::getCurrentOperand()
{
    return currentOperand_;
}

Instruction ControlUnit::getCurrentInstruction()
{
    return Instruction(currentInstruction_);
}