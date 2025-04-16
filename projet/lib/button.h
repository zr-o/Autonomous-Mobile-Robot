/*
Giovanni Marven Alcena
Adam Azrou
Elliot Gareau
Anis Feteh Benabderrahmane

Un programme qui initialise des ports en entrée pour permettre l'utilisation des boutons.
Le programme permet l'utilisation d'un bouton interne et/ou un bouton externe et gere/enregistre les etats des boutons.
16 avril 2025

Composantes :
bouton-poussoir blanc (Digi-Key: EG1328-ND)
bouton-poussoir interne
Une resistance de 10 kOhm.
Un fil de donnee qui est connecte en entree au port sélectionné.
Un condensateur de 0.1 uF.
VCC de 5v
*/

#ifndef BUTTON_H
#define BUTTON_H

#include "lib_defines.h"

#include <util/delay.h>
#include <avr/interrupt.h>
#include "ports.h"

enum class ButtonType
{
    MOTHERBOARD,
    EXTERN
};

class Button
{
public:
    Button(ButtonType type, Port port, Pin pin);
    bool isPressed();
    bool wasPressed();
    void resetPressMemory();

private:
    ButtonType type_;
    Port port_;
    Pin pin_;
    bool buttonPressMemory_ = false;
};

#endif