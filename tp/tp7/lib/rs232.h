#ifndef RS232_H
#define RS232_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "memoire_24.h"



class RS232
{
public:
    RS232();
    void write(const char* message);
};

#endif