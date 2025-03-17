#include "rs232.h"
#include <stdio.h>
#include <stdlib.h>

#define DEBUG_H // à mettre en commentaire ou non au besoin
#ifdef DEBUG_H

class DEBUG
{
public:

// Version pour les chaînes de caractères (pas besoin de sprintf)
static void DebugToRs232(const char* message);

// Version pour les entiers (utilisation de sprintf pour formater)
static void DebugToRs232(int x);

private: 
    DEBUG();
};


# define DEBUG_PRINT(x) DEBUG::write(x)

#else

# define DEBUG_PRINT(x) do {} while (0) // code mort





#endif