/*
Giovanni Marven Alcena
Adam Azrou
C'est une machine à état qui allume la couleur verte seulement si l'on appuie et relache 3 fois
20 janvier 2025

Composantes :
Un fil femelle à femelle reliés à la del qui sont connectés au ports A1 et A2.
La couleur verte est le port A2 et la rouge le port A2.
Une del en sortie.
Bouton-poussoir.
┌───────────────────┬─────────────────┬───────────────────┬────────────┐
│ État présent      │ Bouton-poussoir │ État suivant      │ Sortie DEL │
├───────────────────┼─────────────────┼───────────────────┼────────────┤
│ INITIALE          │ RELACHE         │ INITIALE          │ ETEINTE    │
│ INITIALE          │ APPUYER         │ PREMIER_APPUI     │ ETEINTE    │
│ PREMIER_APPUI     │ RELACHE         │ PREMIER_RELACHE   │ ETEINTE    │
│ PREMIER_APPUI     │ APPUYER         │ PREMIER_APPUI     │ ETEINTE    │
│ PREMIER_RELACHE   │ RELACHE         │ PREMIER_RELACHE   │ ETEINTE    │
│ PREMIER_RELACHE   │ APPUYER         │ DEUXIEME_APPUI    │ ETEINTE    │
│ DEUXIEME_APPUI    │ RELACHE         │ DEUXIEME_RELACHE  │ ETEINTE    │
│ DEUXIEME_APPUI    │ APPUYER         │ DEUXIEME_APPUI    │ ETEINTE    │
│ DEUXIEME_RELACHE  │ RELACHE         │ DEUXIEME_RELACHE  │ ETEINTE    │
│ DEUXIEME_RELACHE  │ APPUYER         │ TROISIEME_APPUI   │ ETEINTE    │
│ TROISIEME_APPUI   │ RELACHE         │ TROISIEME_RELACHE │ ETEINTE    │
│ TROISIEME_APPUI   │ APPUYER         │ TROISIEME_APPUI   │ ETEINTE    │
│ TROISIEME_RELACHE │ X               │ INITIALE          │ VERT       │
└───────────────────┴─────────────────┴───────────────────┴────────────┘

*/
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define DELAI_2_SECONDES 2000
#define DELAI_REBOND_MS 10

bool estAppuye()
{
    if (PIND & (1 << PD2))
    {
        _delay_ms(DELAI_REBOND_MS);

        if (PIND & (1 << PD2))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void eteindreDelVerte()
{
    PORTA &= ~(1 << PA1);
}

void allumerDelVerte()
{
    PORTA |= (1 << PA1);
}

enum class Etat
{
    INITIALE,
    PREMIER_APPUI,
    PREMIER_RELACHE,
    DEUXIEME_APPUI,
    DEUXIEME_RELACHE,
    TROISIEME_APPUI,
    TROISIEME_RELACHE
};

Etat retournerEtatSuivant(Etat etatActuel)
{

    switch (etatActuel)
    {

        case Etat::INITIALE:

            eteindreDelVerte();

            if (estAppuye())
            {
                return Etat::PREMIER_APPUI;
            }
            break;

        case Etat::PREMIER_APPUI:

            if (!estAppuye())
            {
                return Etat::PREMIER_RELACHE;
            }
            break;

        case Etat::PREMIER_RELACHE:

            if (estAppuye())
            {
                return Etat::DEUXIEME_APPUI;
            }
            break;

        case Etat::DEUXIEME_APPUI:

            if (!estAppuye())
            {
                return Etat::DEUXIEME_RELACHE;
            }
            break;

        case Etat::DEUXIEME_RELACHE:

            if (estAppuye())
            {
                return Etat::TROISIEME_APPUI;
            }
            break;

        case Etat::TROISIEME_APPUI:

            if (!estAppuye())
            {
                return Etat::TROISIEME_RELACHE;
            }
            break;

        case Etat::TROISIEME_RELACHE:

            allumerDelVerte();
            _delay_ms(DELAI_2_SECONDES);

            return Etat::INITIALE;
    }

    return etatActuel;
}

int main()
{

    DDRD &= ~(1 << PD2);
    DDRA |= (1 << PA0) | (1 << PA1);

    Etat etatActuel = Etat::INITIALE, etatSuivant = Etat::INITIALE;

    while (true)
    {

        etatSuivant = retournerEtatSuivant(etatActuel);
        etatActuel = etatSuivant;
    }
}