#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint8_t changerCouleur(uint8_t initial);
void initialisation();

volatile uint8_t etat = 0;

ISR(TIMER1_COMPA_vect) {
    etat = 1;
}

int main()
{
    uint8_t valueA = 0x00;
    PORTA = valueA;
    
    initialisation();

	for(;;)
	{
        if(etat) {
            valueA = changerCouleur(valueA);
            PORTA = valueA;
            etat = 0;
        }
	}
}

uint8_t changerCouleur(uint8_t initial) {
    if(initial >= 2)
        return 0x01;
    else
        return 0x02;
}

void initialisation() {
    cli();
    
    DDRA = 0xff;
	DDRD = 0xff;
    PORTD = 0x00;
    
    TCCR1A &= 0x4c;
    TCCR1A |= 0x40;
    TCCR1B &= 0xed;
    TCCR1B |= 0x0d;
    
    TIMSK1 |= 0x02;
    
    OCR1A = 0x1F40;
    
    sei();
}
