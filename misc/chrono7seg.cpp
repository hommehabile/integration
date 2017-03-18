#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lib7seg.h"

void initialisation();

volatile bool change = false, enable = false;
volatile uint8_t compteur = 0;

ISR(INT0_vect) {
    _delay_ms(10);
    if(PIND & 4) {
        if(enable)
            enable = false;
        else {
            enable = true;
            compteur = 0;
        }
    }
    EIFR |= (1 << INTF0);
}

ISR(TIMER1_COMPA_vect) {
    change = true;
}

int main()
{
    uint8_t valueA = 0, valueB = 0;
    PORTA = valueA;
    PORTB = valueB;
    
    initialisation();

	for(;;)
	{
        if(change) {
            if(enable) {
                compteur++;
                if(compteur > 99)
                compteur = 0;
                uint8_t unites = compteur % 10;
                /* SANS LE DECODEUR 7 SEGMENTS
                valueA = ~translate(unites);
                PORTA = valueA;
                valueB = ~translate((compteur - unites) / 10); 
                PORTB = valueB; */
                
                /* AVEC LE DECODEUR 7 SEGMENTS */
                valueA = unites | (((compteur - unites) / 10) << 4);
                PORTA = valueA;
            }
            change = false;
        }
	}
}

void initialisation() {
    cli();
    
    DDRA = 0xff;
	DDRB = 0xff;
    DDRD = 0x00;
    
    TCCR1A &= 0x4c;
    TCCR1A |= 0x40;
    TCCR1B &= 0xed;
    TCCR1B |= 0x0d;
    TIMSK1 |= 0x02;
    //OCR1A = 0x1F40; //8000
    OCR1A = 0x0320; //800
    
    EIMSK |= _BV(INT0);
    EICRA |= 0x3;
    
    sei();
}
