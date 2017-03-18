#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

uint8_t changerCouleur(uint8_t initial);

int main()
{
	DDRA = 0xff;
	DDRD = 0x00;
    uint8_t valueA = 0x02;
    PORTA = valueA;
    bool dejaEvalue = false;

	for(;;)
	{
        if(PIND & 0x04){
            if(!dejaEvalue) {
                _delay_ms(10);
                if(PIND & 0x04) {
                    valueA = changerCouleur(valueA);
                    PORTA = valueA;
                    dejaEvalue = true;
                }
            }
        } else {
            dejaEvalue = false;
        }
	}
}

uint8_t changerCouleur(uint8_t initial) {
    if(initial >= 2)
        return 0x01;
    else
        return 0x02;
}
