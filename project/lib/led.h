/*
Giovanni Marven Alcena  
Adam Azrou  
Elliot Gareau  
Anis Feteh Benabderrahmane  

Permet d’allumer une DEL bicolore (rouge/verte) via deux broches du microcontrôleur ATmega324PA.  
16 avril 2025 

Composantes :  
Utilisation de deux broches pour contrôler une DEL bicolore.  
(Voir ports.h pour la configuration des broches)  
*/

#ifndef LED_H
#define LED_H

#include "ports.h"
#include "lib_defines.h"
#include <util/delay.h>

enum class Color
{
    OFF,
    GREEN,
    RED
};

class Led
{
public:
    Led(Port port, Pin pinA, Pin pinB);
    void lightUp(Color color);
    void flashAt2Hz(Color color, uint8_t durationSeconds);
    void flashAt4Hz(Color color, uint8_t durationSeconds);
    void flashGreenRed2Hz();

private:
    Port port_;
    Pin pinA_;
    Pin pinB_;
};

#endif