/*
Giovanni Marven Alcena
Adam Azrou
Elliot Gareau
Anis Feteh Benabderrahmane

Un programme qui prend un message (string) ou une variable (int) et renvoie la valeur au terminal via rs232 avec un bel affichage.
16 avril 2025

Composantes :
Protocole de communication RS232 (voir rs232.h)
Probablement un cable USB
*/

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
    static void display(const int8_t x);

private:
    Debug() = default;
};


#endif


