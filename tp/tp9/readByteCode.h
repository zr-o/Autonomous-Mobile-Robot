#ifndef READBYTECODE_H
#define READBYTECODE_H

#include "memoire_24.h"
#include "rs232.h"

class readByteCode {

    public :

    readByteCode();
    void readByte();
    void getSize();

    private:
    uint16_t realSize_;
    Memoire24CXXX mem;
};

#endif