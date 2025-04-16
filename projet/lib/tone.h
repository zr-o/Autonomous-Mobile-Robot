/*
Giovanni Marven Alcena
Adam Azrou
Elliot Gareau
Anis Feteh Benabderrahmane

Permet de jouer une note ou une série de notes voulu. A aussi la capacite
a eteindre la note qui est entrain de jouer.
16 avril 2025

Composantes : 
Utilisation d'une minuterie en mode CTC. (voir timer0.h)
Le fil du piezo rouge qui est relie a la pin 3 en sortie sur le port B et le noir a la pin 4 en entree sur le port B.
(Voir ports.h pour la configuration des fonctions)
*/

#ifndef TONE_H
#define TONE_H

#include "timer0.h"
#include "wheels.h"
#include "ports.h"

class Tone
{
public:
    Tone(Timer0& tomeTimer);
    void playNote(uint8_t note);
    void turnOffNote();

private:
Timer0& toneTimer_;
};

#endif