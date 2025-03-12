/*
Giovanni Marven Alcena
Adam Azrou

Un compteur est active au rythme de 10 fois par seconde lorsque le bouton est presse.
Une lumiere rouge va clignoter au nombre de compteur/2 fois 2 secondes apres que 
le bouton est relache ou le compteur atteint 120.
10 mars 2025

Composantes :
Une resistance de 100kOhm
Une del bicolore qui est relié au port B0 et B1 en sortie. B1 c'est la couleur rouge et B0 la verte.
Un bouton-poussoir avec signal inverse relie au fil de donnee.
Un fil de donnee qui est connecte sur IntEn qui est relie au port D2 en entree.
Un condensateur de 0.1 uF
*/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Valeurs calculees a l'aide de (F_CPU * MS ) / (1024 * 1000)
#define DELAI_100MS_CALCUL 781
#define DELAI_500MS_CALCUL 3906
#define DELAI_1000MS_CALCUL 7813
#define DELAI_2000MS_CALCUL 15625

#define DELAI_REBOND_MS 10.0

volatile uint8_t gMinuterieExpiree = 0;
volatile uint8_t gBoutonPoussoir = 0;
volatile uint8_t gCompteur = 0;

ISR(TIMER1_COMPA_vect)
{
    gMinuterieExpiree = 1;

    gCompteur++;

    // Desactive les interuptions de la minuterie, on veut seulement activer l'interuption si on repart la minuterie.
    TIMSK1 &= ~(1 << OCIE1A);
}

ISR(INT0_vect)
{
    gBoutonPoussoir = 1;

    _delay_ms(DELAI_REBOND_MS);

    if ((PIND & (1 << PD2)))
    {
        gBoutonPoussoir = 0;
    }
}

void partirMinuterie(uint16_t dureeCalcul)
{
    gMinuterieExpiree = 0;

    // Met la minuterie a 0.
    TCNT1 = 0;

    // Resultat du calcul compare a la minuterie.
    OCR1A = dureeCalcul;

    // Active les interuptions.
    TIMSK1 = (1 << OCIE1A);
}

void allumerDelVerte(uint16_t dureeCalcul = 0)
{
    if (dureeCalcul == 0)
    {
        PORTB = (1 << PB0);
        return;
    }

    PORTB = (1 << PB0);

    partirMinuterie(dureeCalcul);

    while (!gMinuterieExpiree)
    {
    }

    PORTB &= ~(1 << PB0);
}

void allumerDelRouge(uint16_t dureeCalcul = 0)
{
    if (dureeCalcul == 0)
    {
        PORTB = (1 << PB1);
        return;
    }

    PORTB = (1 << PB1);

    partirMinuterie(dureeCalcul);

    while (!gMinuterieExpiree)
    {
    }

    PORTB &= ~(1 << PB1);
}

void eteindreDelVerte(uint16_t dureeCalcul = 0)
{
    if (dureeCalcul == 0)
    {
        PORTB &= ~(1 << PB0);
        return;
    }

    PORTB &= ~(1 << PB0);

    partirMinuterie(dureeCalcul);

    while (!gMinuterieExpiree)
    {
    }
}

void eteindreDelRouge(uint16_t dureeCalcul = 0)
{
    if (dureeCalcul == 0)
    {
        PORTB &= ~(1 << PB1);
        return;
    }

    PORTB &= ~(1 << PB1);

    partirMinuterie(dureeCalcul);

    while (!gMinuterieExpiree)
    {
    }
}

void clignoterDelRouge(uint16_t dureeCalcul)
{
   const uint8_t divisionDuree = 2;
    allumerDelRouge(dureeCalcul / divisionDuree);
    eteindreDelRouge(dureeCalcul / divisionDuree);
}

void initialisationBoutton()
{
    cli();

    // permet les interruptions externes pour int0.
    EIMSK |= (1 << INT0);

    // Fait que les interruptions sur int0 s'activent au rising edge et falling edge du signal.
    EICRA |= (1 << ISC00);

    sei();
}

void initialisationPorts()
{
    cli();

    DDRD &= ~(1 << PD2);

    DDRB |= (1 << PB0) | (1 << PB1);

    sei();
}

void initialisationTimer1()
{
    cli();

    // Operation normale
    TCCR1A = 0x00;

    // Mode CTC avec une frequence divisee par 1024
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);

    // Non utilise
    TCCR1C = 0x00;

    sei();
}

int main()
{
    initialisationPorts();
    initialisationBoutton();
    initialisationTimer1();

    const uint8_t compteurMax = 120;

    while (true)
    {
        while (true)
        {
            if (gBoutonPoussoir)
                break;
        }

        while (gBoutonPoussoir && gCompteur < compteurMax)
        {
            partirMinuterie(DELAI_100MS_CALCUL);

            while (!gMinuterieExpiree && gBoutonPoussoir)
            {
            }
        }

        // Desactive les interruptions si le bouton est lache avant la fin de la minuterie
        TIMSK1 &= ~(1 << OCIE1A);

        const uint8_t divisionCompteur = 2;
        uint8_t compteurFinal = gCompteur / divisionCompteur;

        allumerDelVerte(DELAI_500MS_CALCUL);
        eteindreDelVerte(DELAI_2000MS_CALCUL);

        while (compteurFinal > 0)
        {
            clignoterDelRouge(DELAI_500MS_CALCUL);
            compteurFinal--;
        }

        allumerDelVerte(DELAI_1000MS_CALCUL);
        eteindreDelVerte();
        gCompteur = 0;
    }
}