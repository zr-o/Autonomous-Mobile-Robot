/*
Giovanni Marven Alcena
Adam Azrou
Elliot Gareau
Anis Feteh Benabderrahmane

Un programme qui effectue une lecture d'un capteur infrarouge chaque 50ms à l'aide d'un CAN, puis 
retourne la mediane des 5 dernières distances enregistrés.
16 avril 2025

Composantes :
Un capteur de distance infrarouge Sharp GP2Y0A21YK0F
Un fil de donnee qui est connecte en entree au port/pin analogique sélectionné (dans ce cas A8)
VCC de 5 volt avec AREF ajusté a 5
*/

#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

#include "lib_defines.h"
#include <avr/io.h>
#include "can.h"
#include "ports.h"
#include <util/delay.h>


class DistanceSensor
{
public:
    DistanceSensor(can &converter);
    uint16_t readDistance();

private:
    can &converter_;
};

#endif
