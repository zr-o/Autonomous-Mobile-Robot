#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "memoire_24.h"
#include <string.h>

#define DELAI_5_MS 5

void initialisationUART(void)
{

    // 2400 bauds. Nous vous donnons la valeur des deux

    // premiers registres pour vous éviter des complications.

    UBRR0H = 0;

    UBRR0L = 0xCF;

    UCSR0A = 0X00; // Registre qui contient seuleument des flags et des configurations qui nous interesse pas

    UCSR0B |= (1 << TXEN0); // Active la transmission

    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Format des trames: 8 bits, 1 stop bits, sans parité
}

void transmissionUART(uint8_t donnee)
{
    while (!(UCSR0A & (1 << UDRE0)))
    { // N'ecrit pas tant que le flag UDRE n'est pas actif : "The UDREn Flag indicates if the transmit buffer (UDRn) is ready to receive new data".
    }

    UDR0 = donnee; // ecrit dans le registre, automatiquement le avr envoi a l'autre USART
}

int main()
{
    initialisationUART();

    char phrase[23] = {'P', 'O', 'L', 'Y', 'T', 'E', 'C', 'H', 'N', 'I', 'Q', 'U', 'E', ' ', 'M', 'O', 'N', 'T', 'R', 'E', 'A', 'L', '\0'}; // ce que l'on veut inscrire dans la memoire

    Memoire24CXXX mem; // initialise la class afin de pouvoir utiliser les fonctions

    for (uint16_t adresse = 0x00; adresse < 23; adresse++)
    { // on ecrit le tableau dans la mem avec un delai de 5 ms entre chaque ecriture
        mem.ecriture(adresse, phrase[adresse]);
        _delay_ms(DELAI_5_MS);
    }

    char phraseLecture[23] = {}; // tableau dans lequel nous voulons copier les informations de la memoire

    for (uint16_t adresse = 0x00; adresse < 23; adresse++)
    { // nous lisons de la memoire les informations avec un delai de 5 ms
        uint8_t temp = 0x00;
        mem.lecture(adresse, &temp);
        phraseLecture[adresse] = temp;
        _delay_ms(DELAI_5_MS);
    }


    for (uint8_t i = 0; i < 100; i++)
    {

        for (uint8_t j = 0; j < 23; j++)
        {

            transmissionUART(phraseLecture[j]);
        }
    }

    while (true)
    {
    }
}