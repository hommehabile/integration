#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lib7seg.h"

#define VERT 1
#define ROUGE 2
#define ETEINT 0

int main() {
    DDRA = 0xff;
    DDRB = 0xff;
    DDRD = 0x00;
    uint8_t compteur = 0;
    bool dejaIncremente = false;
    PORTA = 0x00;
    PORTB = ETEINT;
    
    for(;;) {
        if(PIND & 0x04) {
            _delay_ms(10);
            if(PIND & 0x04 && !dejaIncremente) {
                compteur++;
                if(compteur >= 10)
                    compteur = 0;
                PORTB = ROUGE;
                PORTA = ~(translate(compteur));
                dejaIncremente = true;
            }
        } else {
            PORTB = ETEINT;
            dejaIncremente = false;
            while(!(PIND & 0x04)){
                PORTA = ~(translate(compteur));
                _delay_ms(990);
                if(compteur == 0)
                    compteur = 9;
                else
                    compteur--;
            }
        }
    }
}
