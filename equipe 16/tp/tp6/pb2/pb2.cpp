/*
Giovanni Marven Alcena
Adam Azrou

C'est un programme qui detecte et affiche l'intensite de la lumiere.
10 mars 2025

Composantes :
Une photoresistance entre 4 et 11 kOhm.
Une resistance de 10 kOhm.
Une del bicolore qui est relie au port B0 et B1 en sortie. B1 c'est la couleur rouge et B0 la verte.
Un fil de donnee qui est connecte en entree au port A0.
Un condensateur de 0.1 uF.
Une source de tension en entrée qui envoie 5V.
*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <can.h>

#define DELAI_AMBREE_MS 5

void initialisationPorts(void)
{
    DDRA &= ~(1 << PA0);
    DDRB |= (1 << PB0) | (1 << PB1);
}

void allumerDelRouge()
{
    PORTB = (1 << PB1);
}

void allumerDelVerte()
{
    PORTB = (1 << PB0);
}

void allumerDelAmbree()
{
    allumerDelVerte();
    _delay_ms(DELAI_AMBREE_MS);
    allumerDelRouge();
    _delay_ms(DELAI_AMBREE_MS);
}

int main()
{
    initialisationPorts();

    uint16_t lecture;
    can convertisseur;

    // Valeurs obtenues experimentalement en testant l'intensité de la lumiere.
    const uint8_t lumiereForte = 200;
    const uint8_t lumiereBasse = 130;

    // Nous devrons decaler la valeur de lecture de 2 bits car nous voulons le tronquer en 8 bits.
    const uint8_t decalageBits = 2;

    while (true)
    {
        lecture = convertisseur.lecture(PA0);
        lecture = lecture >> decalageBits;

        if (lecture < lumiereBasse)
        {
            allumerDelVerte();
        }
        else if (lecture < lumiereForte)
        {
            allumerDelAmbree();
        }
        else
        {
            allumerDelRouge();
        }
    }
}
