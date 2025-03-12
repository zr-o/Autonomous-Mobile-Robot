#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define DELAI_10_US 10.0
#define DELAI_1_MS 1.0
#define DELAI_1000_US 1000.0
#define DELAI_100_US 50.0

void eteindreRoue()
{

    PORTA = 0x00;
}

void allumerRoue()
{
    PORTA = (1 << PA1);
}

void faireDelaiMicrosecondes(uint16_t microsecondes)
{
uint16_t resultatCalcul = microsecondes / 10;

    for (uint16_t i = 0; i < resultatCalcul; i++)
    {
        _delay_us(DELAI_10_US);
    }
}

void faireDelaiMillisecondes(uint16_t millisecondes)
{
    for (uint16_t i = 0; i < millisecondes; i++)
    {
        _delay_ms(DELAI_1_MS);
    }
}
void allumerRouePourcentageMs(uint16_t pourcentage, uint16_t frequenceHz, uint16_t tempsMs)
{
    uint16_t periodeMs = 1000.0 / frequenceHz;

    uint16_t delaiA = (pourcentage / 100.0) * periodeMs;
    uint16_t delaiB = periodeMs - delaiA;
    uint16_t iterations = tempsMs / periodeMs;

    for (uint16_t i = 0; i < iterations; i++)
    {
        allumerRoue();
        faireDelaiMillisecondes(delaiA);
        eteindreRoue();
        faireDelaiMillisecondes(delaiB);
    }
}

void allumerRouePourcentageUs(uint16_t pourcentage, uint16_t frequenceHz, uint16_t tempsMs)
{
    uint16_t periodeUs = (1000.0 / frequenceHz) * 1000;

    uint16_t delaiA = (pourcentage / 100.0) * periodeUs;
    uint16_t delaiB = periodeUs - delaiA;
    uint16_t iterations = (tempsMs / periodeUs) * 1000;

    for (uint16_t i = 0; i < iterations; i++)
    {
        allumerRoue();
        faireDelaiMicrosecondes(delaiA);
        eteindreRoue();
        faireDelaiMicrosecondes(delaiB);
    }
}

int main()
{

    DDRA |= (1 << PA0) | (1 << PA1);


    //allumerRouePourcentageMs(100, 60, 2000);
    //allumerRouePourcentageMs(75, 60, 2000);
    //allumerRouePourcentageMs(50, 60, 2000);
    //allumerRouePourcentageMs(25, 60, 2000);
    //allumerRouePourcentageMs(0, 60, 2000);

    allumerRouePourcentageUs(100, 400, 5000);
    allumerRouePourcentageUs(75, 400, 5000);
    allumerRouePourcentageUs(50, 400, 5000);
    allumerRouePourcentageUs(25, 400, 5000);
    allumerRouePourcentageUs(0, 400, 5000);

}