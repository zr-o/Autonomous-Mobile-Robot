/*

Giovanni Marven Alcena
Adam Azrou
C'est une machine à état qui allume des couleurs de la del selon les différents états.
20 janvier 2025

Composantes :
Un fil femelle à femelle reliés à la del qui sont connectés au ports A1 et A2.
La couleur verte est le port A1 et la couleur rouge est le port A2.
Une del en sortie.
Un bouton-poussoir.

+-------------------+-----------------+-------------------+------------+
| État présent      | Bouton-poussoir | État suivant      | Sortie DEL |
+-------------------+-----------------+-------------------+------------+
| INITIALE          | RELACHE         | INITIALE          | ROUGE      |
| INITIALE          | APPUYER         | PREMIER_APPUI     | ROUGE      |
| PREMIER_APPUI     | APPUYER         | PREMIER_APPUI     | AMBREE     |
| PREMIER_APPUI     | RELACHE         | PREMIER_RELACHE   | AMBREE     |
| PREMIER_RELACHE   | RELACHE         | PREMIER_RELACHE   | VERTE      |
| PREMIER_RELACHE   | APPUYER         | DEUXIEME_APPUI    | VERTE      |
| DEUXIEME_APPUI    | APPUYER         | DEUXIEME_APPUI    | ROUGE      |
| DEUXIEME_APPUI    | RELACHE         | DEUXIEME_RELACHE  | ROUGE      |
| DEUXIEME_RELACHE  | RELACHE         | DEUXIEME_RELACHE  | ETEINTE    |
| DEUXIEME_RELACHE  | APPUYER         | TROISIEME_APPUI   | ETEINTE    |
| TROISIEME_APPUI   | APPUYER         | TROISIEME_APPUI   | VERTE      |
| TROISIEME_APPUI   | RELACHE         | INITIALE          | VERTE      |
+-------------------+-----------------+-------------------+------------+


*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define DELAI_REBOND_MS 10
#define DELAI_AMBREE_MS 5


volatile bool boutonEstAppuye = false;

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



void allumerDelRouge()
{

    PORTA = (1 << PA1);
}

void allumerDelVerte()
{

    PORTA = (1 << PA0);
}

void eteindreDel()
{

    PORTA &= ~(1 << PA1);
}

enum class Etat
{
    INITIALE,
    PREMIER_APPUI,
    DEUXIEME_APPUI,
    TROISIEME_APPUI,
    PREMIER_RELACHE,
    DEUXIEME_RELACHE
};

Etat retournerEtatSuivant(Etat etatActuel)
{

    switch (etatActuel)
    {

        case Etat::INITIALE:

            allumerDelRouge();
            if (boutonEstAppuye)
            {
                return Etat::PREMIER_APPUI;
            }
            break;

        case Etat::PREMIER_APPUI:

            allumerDelRouge();
            _delay_ms(DELAI_AMBREE_MS);
            allumerDelVerte();
            _delay_ms(DELAI_AMBREE_MS);

            if (!boutonEstAppuye)
            {
                return Etat::PREMIER_RELACHE;
            }
            break;

        case Etat::PREMIER_RELACHE:

            allumerDelVerte();
            if (boutonEstAppuye)
            {

                return Etat::DEUXIEME_APPUI;
            }
            break;

        case Etat::DEUXIEME_APPUI:

            allumerDelRouge();
            if (!boutonEstAppuye)
            {

                return Etat::DEUXIEME_RELACHE;
            }
            break;

        case Etat::DEUXIEME_RELACHE:

            eteindreDel();
            if (boutonEstAppuye)
            {

                return Etat::TROISIEME_APPUI;
            }
            break;

        case Etat::TROISIEME_APPUI:

            allumerDelVerte();
            if (!boutonEstAppuye)
            {

                return Etat::INITIALE;
            }
            break;
    }

    return etatActuel;
}

ISR(INT0_vect){

    boutonEstAppuye = estAppuye();

    EIFR |= (1 << INTF0);

}

void initialisation ( void ) {

cli ();

DDRD &= ~(1 << PD2);

DDRA |= (1 << PA0) | (1 << PA1);

EIMSK |= (1 << INT0);


EICRA |= (1 << ISC00);

sei ();

}

int main()
{

    initialisation();

    Etat etatActuel = Etat::INITIALE;

    while(true){

        etatActuel = retournerEtatSuivant(etatActuel);

    }

}