#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <can.h>

void initialize()
{
  DDRB |=  (1 << PB0) | (1 << PB1);
}

void delRed()
{
  PORTB |= (1 << PB0);
  PORTB &= ~(1 << PB1);
}

void delGreen()
{
  PORTB |= (1 << PB0);
  PORTB &= ~(1 << PB1);
}

void delYellow()
{
    const uint8_t DELAY_RED_TO_GREEN = 3;
    const uint8_t DELAY_GREEN_TO_RED = 5;
    delRed();
    _delay_ms(DELAY_RED_TO_GREEN);
    delGreen();
    _delay_ms(DELAY_GREEN_TO_RED);
}

int main() {
   
    while (true) {
        can sensor = can();
        uint16_t read = sensor.lecture(0);
        uint8_t light = (read >> 2);
    
    if (read < 100) {
        delGreen();
    }
    else if (read >= 100 && read <= 220){
        delYellow();
    }
    else {
        delRed();
    }

}
}