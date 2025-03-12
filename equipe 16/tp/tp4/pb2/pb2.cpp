#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define DELAI_REBOND_MS 10
#define DELAI_1_SECONDE_CALCUL 7812
#define DELAI_10_SECONDES_CALCUL 78125
#define DELAI_100_MS_CALCUL 781

volatile uint8_t gMinuterieExpiree = 0;
volatile uint8_t gBoutonPoussoir = 0;

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

ISR(TIMER1_COMPA_vect)
{

    gMinuterieExpiree = 1;
    TIMSK1 &= ~(1 << OCIE1A); // Desactive les interuptions du timer, on veut seulement active l'interuption si on repart la minuterie.

}

ISR(INT0_vect)
{
    gBoutonPoussoir = 1;

    // anti-rebond

    _delay_ms(DELAI_REBOND_MS);

        if (!(PIND & (1 << PD2)))
        {
            gBoutonPoussoir = 0;
        }
       
}

void partirMinuterie(uint16_t duree)
{

    gMinuterieExpiree = 0;

    TCNT1 = 0; // Met le timer a 0

    OCR1A = duree; // Imaginons que nous voulons faire une minuterie de 1 seconde et que la fréquence est de 8mhz, alors il faut mettre 8000000
                   // dans OCR1A. En effet, celui-ci est constament comparée à TCNT1. Puisque TCNT1 incremente de 1 à chaque cycle de processeur,
                   // le compteur sera égal à 8000000 et donc OCF1A (Output compare flag) sera activée puisque TCNT1 = OCR1A.

    TIMSK1 = (1 << OCIE1A); // Active les interuptions

}

void initialisation(void)
{

    cli(); // Routine qui bloque toutes les interuptions

    DDRD &= ~(1 << PD2);
    DDRA |= (1 << PA0) | (1 << PA1); // Met certains port en mode sortie et entrees

    EIMSK |= (1 << INT0); // permet les interruptions externes pour int0 (relié au port D2)

    EICRA |= (1 << ISC00);  //Fait que les interruptions sur int0 s'activent au rising edge et falling edge du signal sur D2 (donc quand le bouton est appuyer est relacher)

    TCCR1A = 0x00; // Registre de configuration, ici on set certains bits COM1A,B1 ET COM1A,B0 à 0 car nous n'avons pas besoin des sorties OC1A et OC1B
                   // On set aussi d'autres bits à 0 pour la configuration CTC
                   // Voir *documentation TCCR1A

    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // La suite du registre de configuration, WGM12 à 1 nous donne la configuration CTC du timer, CS2 et CS0 à 1
                                                       // nous donne la configuration du clock (frquence divisée par 1024), ainsi ici il roule a une fréquence de 7812Hz
                                                       // (Il faut donc compter 7812 afin de compter 1 seconde)


    TCCR1C = 0x00; // Encore la suite du registre de configuration (on utilise pas vraiment ici)

    sei();  // sei permet de recevoir à nouveau des interruptions.

}

int main()
{

    initialisation();

    partirMinuterie(65000);

    do {
        // on attend que la minuterie expire
    } while ( gMinuterieExpiree == 0);

    partirMinuterie(13125);

    do {
        // on attend que l'a minuterie exprire
    } while ( gMinuterieExpiree == 0);

    allumerDelRouge();

    partirMinuterie(DELAI_100_MS_CALCUL);

    do {
        // on attend que l'on appui sur le bouton ou que la minuterie expire
    } while ( gMinuterieExpiree == 0);

    eteindreDel();

    partirMinuterie(DELAI_1_SECONDE_CALCUL);

    do {
        // on attend que l'on appui sur le bouton ou que la minuterie expire
    } while ( gMinuterieExpiree == 0 && gBoutonPoussoir == 0 );

    cli(); // on desactive les interruptions.

    // Verifier la réponse

    if (gBoutonPoussoir == 1)
    {
        allumerDelVerte();
    }
    else
    {
        allumerDelRouge();
    }

}