#ifndef DEBUG_H
#define DEBUG_H

#include "rs232.h"
#include <stdio.h>
#include <string.h>

#ifdef DEBUG
#define DEBUG_PRINT(x) Debug::display((x))

#else
#define DEBUG_PRINT(x) do{} while(0)

#endif

class Debug
{
public:
    static void display(const char *message);
    static void display(const uint16_t x);
    static void display(const uint8_t x);

private:
    Debug() = default;
};


#endif