/*
Giovanni Marven Alcena
Adam Azrou
Elliot Gareau
Anis Feteh Benabderrahmane

Permet de mettre les ports ou les pins souhaites en mode ecriture ou lecture.
Ainsi que lire ou ecrire une valeur sur les ports ou les pins voulus.
16 avril 2025

Composantes : 
Ports A,B,C et D du microcontrolleur.
*/

#ifndef PORTS_H
#define PORTS_H

#include <avr/io.h>

enum class Port
{
    A,
    B,
    C,
    D
};

enum class Pin
{
    N1 = 0,
    N2,
    N3,
    N4,
    N5,
    N6,
    N7,
    N8
};

enum class PortMode
{
    WRITE,
    READ
};

class Ports
{
public:
    static void setPinMode(PortMode mode, Port port, Pin pin);
    static uint8_t readPort(Port port);
    static void writePort(Port port, uint8_t value);
    static bool readPin(Port port, Pin pin);
    static void writePin(Port port, Pin pin, bool value);

private:
    Ports() = default;
};

#endif