/*
Giovanni Marven Alcena
Adam Azrou
Elliot Gareau
Anis Feteh Benabderrahmane

Savoir quel capteur des 5 (de facon digitale) qui a ete detecte (droite,milieu droite, milieu,milieu gauche,gauche).
Permet de savoir si c'est un virage a gauche,a droite, si les 5 capteurs sont allume(cross), les
trois du milieu(pickaxe) ou aucun (no_line). Compteur pour chacun des 5 capteurs.
Possibilite de savoir la position de facon analogique.

16 avril 2025

Composantes : 
Capteur makerLine
Convertisseur analogique(voir can.h)
AREF ajusté à 5V
Pin 4 sur le port A en mode entree (voir ports.h)
Pin 3 a 7 sur le port C en mode entree (voir ports.h)
*/

#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

#include "ports.h"
#include "can.h"

// Doit etre calibrer avant et doit etre en mode dark.
class LineSensor
{
public:
    LineSensor(can &converter);
    bool middleDetected();
    bool leftMiddleDetected();
    bool rightMiddleDetected();
    bool leftDetected();
    bool rightDetected();
    bool leftTurnDetected();
    bool pickaxeTurnDetected();
    bool rightTurnDetected();
    bool crossDetected();
    bool noLineDetected();

    uint8_t sensorsCount();
    uint8_t readPosition();

private:
    can &converter_;
};

#endif