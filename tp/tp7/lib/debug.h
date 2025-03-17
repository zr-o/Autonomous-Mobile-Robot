#include "rs232.h"
#include <stdio.h>
#include <stdlib.h>

#define DEBUG_H
#ifdef DEBUG_H

class Debug
{
public:
    // Version pour les chaînes de caractères (pas besoin de sprintf)
    static void display(const char *message);

    // Version pour les entiers (utilisation de sprintf pour formater)
    static void display(const uint16_t x);

private:
    Debug();
};

#define DEBUG_PRINT(x) Debug::write(x)

#else

#define DEBUG_PRINT(x) \
    do                 \
    {                  \
    } while (0) // code mort

#endif