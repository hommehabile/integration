//lets play music!
#include "arduinoStarWars.h"

void initialisation();
void setFreq(uint16_t freq);

int main() {
    initialisation();
    
    PORTA = 0x00;
    PORTD = 0x00;
    
    for(;;) {
        loop();
    }
    return 0;
}

void setFreq(uint16_t freq) {
    TCNT1 = 0;
    OCR1A = freq;
}

void initialisation() {
    cli();
    DDRA = 0xff; //sortie
    DDRD = 0xff; //sortie
    
    //COM1A=2 (clear when up-counting) COM1B=0 (no port operation) WGM1=15 (fast pwm with A top)
    TCCR1A |= _BV(COM1A0) | _BV(WGM11) | _BV(WGM10);
    //ICNC1=0 ICES1=0 CS1=2 (prescaler 8)
    TCCR1B |= _BV(WGM12) | _BV(WGM13) | _BV(CS11);
    TIMSK1 |= 0x00; //enable compare A et B
    //valeurs de comparaison
    OCR1A = 0x08e1; //2273
    sei();
}