#include "control_unit.h"

static const uint8_t BYTE_SHIFT = 8

    ControlUnit::ControlUnit()
{
    mem_.lecture(currentInstructionAddress_, &nInstructions_);
    nInstructions_ = (nInstructions_ << BYTE_SHIFT);
    currentInstructionAddress++;

    uint16_t temp = 0;
    mem_.lecture(currentInstructionAddress, &temp);
    nInstructions_ |= temp;
    currentInstructionAddress++;

    for (; currentInstructionAddress_ < nInstructions_; currentInstructionAdress_ += 2) {

    }
}

ControlUnit::fetch()
{
    uint8_t instruction;
    mem_.lecture(currentInstructionAddress_, &instruction);
    currentInstruction_ = Instruction(instruction);
}