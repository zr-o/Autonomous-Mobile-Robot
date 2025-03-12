#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define DELAI_50_MS 0.499
#define DELAI_75_MS 0.749
#define DELAI_25_MS 0.249
#define DELAI_1_US 1.0
#define DELAI_10_US 10.0
#define DELAI_1_MS 1.0
#define DELAI_1000_US 1000.0
#define DELAI_100_US 50.0

void eteindreDel()
{

    PORTA = 0x00;
}

void allumerDelRouge()
{
    PORTA = (1 << PA1);
}

void allumerDelVerte()
{
    PORTA = (1 << PA0);
}

void faireDelaiMicrosecondes(uint16_t microsecondes)
{
uint16_t resultatCalcul = microsecondes / 50;

    for (uint16_t i = 0; i < resultatCalcul; i++)
    {
        _delay_us(DELAI_100_US);
    }
}

void faireDelaiMillisecondes(uint16_t millisecondes)
{
    for (uint16_t i = 0; i < millisecondes; i++)
    {
        _delay_ms(DELAI_1_MS);
    }
}
void allumerDelPourcentage(uint8_t pourcentage)
{
    
    uint16_t delaiA = 10 * pourcentage;
    uint16_t delaiB = 1000 - delaiA;

    allumerDelRouge();
    faireDelaiMicrosecondes(delaiA);
    eteindreDel();
    faireDelaiMicrosecondes(delaiB);
}

int main()
{

    DDRA |= (1 << PA0) | (1 << PA1);

    while (true)
    {
        for (uint16_t i = 3000; i > 0; i--)
        {
            uint16_t pourcentage = i / 30;
            allumerDelPourcentage(pourcentage);
        }
    }
}