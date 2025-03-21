<<<<<<< HEAD
=======

>>>>>>> 648598c78ea985aaa4eb4b2367241a21fdc42fa0
#ifndef DEBUG_H
#define DEBUG_H

#include "rs232.h"
#include <stdio.h>
#include <string.h>

<<<<<<< HEAD
#ifdef DEBUG
#define DEBUG_PRINT(x) Debug::display((x))

#else
#define DEBUG_PRINT(x) do{} while(0)

#endif

=======
>>>>>>> 648598c78ea985aaa4eb4b2367241a21fdc42fa0
class Debug
{
public:
    static void display(const char *message);
    static void display(const uint16_t x);
    static void display(const uint8_t x);

private:
    Debug() = default;
};

<<<<<<< HEAD
=======


#ifdef DEBUG
#define DEBUG_PRINT(x) Debug::display(x)
#else
#define DEBUG_PRINT(x) \
    do                 \
    {                  \
    } while (0) // code mort
>>>>>>> 648598c78ea985aaa4eb4b2367241a21fdc42fa0

#endif

#endif

