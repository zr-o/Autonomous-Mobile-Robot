#ifndef READBYTECODE_H
#define READBYTECODE_H

#define F_CPU 8000000UL
#include <util/delay.h>
#include "memoire_24.h"
#include "rs232.h"

class readByteCode {

    public :

    readByteCode();
    void readByte();
    uint16_t getSize() const;

    private:
    uint16_t realSize_;
    Memoire24CXXX mem;
};

#endif