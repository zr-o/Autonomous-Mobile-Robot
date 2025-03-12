#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

void initialisationUART ( void ) {

// 2400 bauds. Nous vous donnons la valeur des deux

// premiers registres pour vous éviter des complications.

UBRR0H = 0;

UBRR0L = 0xCF;

UCSR0A = 0X00; // Registre qui contient seuleument des flags et des configurations qui nous interesse pas

UCSR0B |= (1 << TXEN0); // Active la transmission

UCSR0C |= (1 << UCSZ01)|(1 << UCSZ00); // Format des trames: 8 bits, 1 stop bits, sans parité

}

void transmissionUART ( uint8_t donnee ) {
while (!( UCSR0A & (1 << UDRE0))){ // N'ecrit pas tant que le flag UDRE n'est pas actif : "The UDREn Flag indicates if the transmit buffer (UDRn) is ready to receive new data".
}

UDR0 = donnee; // ecrit dans le registre, automatiquement le avr envoi a l'autre USART
}

int main(){

initialisationUART();

char mots[21] = "Le robot en INF1900\n";

uint8_t i, j;

for ( i = 0; i < 100; i++ ) {

for ( j=0; j < 20; j++ ) {

transmissionUART ( mots[j] );

}

}



}