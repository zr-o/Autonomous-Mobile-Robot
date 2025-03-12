#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "memoire_24.h"
#include <string.h>

#define DELAI_5_MS 5

void eteindreDel()
{

    PORTA = 0x00;
}

void allumerDelRouge()
{
    PORTA = (1 << PA1);
}

int main(){

DDRA |= (1 << PA0) | (1 << PA1);

eteindreDel();

char phrase[23] = {'P', 'O', 'L', 'Y', 'T', 'E', 'C', 'H', 'N', 'I', 'Q', 'U', 'E', ' ', 'M', 'O', 'N', 'T', 'R', 'E', 'A', 'L', '\0'}; // ce que l'on veut inscrire dans la memoire

Memoire24CXXX mem; //initialise la class afin de pouvoir utiliser les fonctions

for (uint16_t adresse = 0x00; adresse < 23; adresse++){ //on ecrit le tableau dans la mem avec un delai de 5 ms entre chaque ecriture
    mem.ecriture(adresse, phrase[adresse]);
    _delay_ms(DELAI_5_MS);
}

char phraseLecture[23] = { }; // tableau dans lequel nous voulons copier les informations de la memoire

for (uint16_t adresse = 0x00; adresse < 23; adresse++){ // nous lisons de la memoire les informations avec un delai de 5 ms
    uint8_t temp = 0x00;
    mem.lecture(adresse, &temp);
    phraseLecture[adresse] = temp;
    _delay_ms(DELAI_5_MS);
}

if(strcmp(phraseLecture, phrase) == 0){ //on compare le tableau que nous avons lu de la memoire avec le tableau initiale, si ce sont les memes, on allume la del.
allumerDelRouge();
}

}