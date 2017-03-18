#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint8_t changerCouleur(uint8_t initial);
void initialisation();

volatile uint8_t etat = 0;

ISR(INT0_vect) {
    _delay_ms(30);
    if(PIND & 4)
        etat = 1;
    EIFR |= (1 << INTF0);
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
	DDRD = 0x00;
    
    EIMSK |= _BV(INT0);
    EICRA |= 0x3; //il me semblait que le changement de ces bits quand EIMSK=1 pouvait provoquer une interruption...
    
    sei();
}
