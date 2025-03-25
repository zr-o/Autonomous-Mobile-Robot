#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include <avr/io.h>
#include <memoire_24.h>
#include "util/delay.h"

enum class Instruction
{
    NOINSTRUCTION = 0x00,
    DBT = 0x01,
    ATT = 0x02,
    DAL = 0x44,
    DET = 0x45,
    SGO = 0x48,
    SAR = 0x09,
    MAR1 = 0x60,
    MAR2 = 0x61,
    MAV = 0x62,
    MRE = 0x63,
    TRD = 0x64,
    TRG = 0x65,
    DBC = 0xC0,
    FBC = 0xC1,
    FIN = 0xFF
};

class ControlUnit
{
public:
    ControlUnit();
    void fetch();
    void decode();
    uint8_t getCurrentOperand();
    Instruction getCurrentInstruction();

private:
    uint16_t loopReturnAddress_ = 0x0000;
    uint16_t currentInstructionAddress_ = 0x0000;
    uint16_t nCodeBytes_ = 0;
    uint8_t loopCounter_ = 0;
    uint8_t currentInstruction_ = 0x00;
    uint8_t currentOperand_ = 0x00;
    Memoire24CXXX mem_ = Memoire24CXXX();
};

#endif