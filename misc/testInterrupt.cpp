#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define ETEINT 0
#define VERT 1
#define ROUGE 2

/*Fonctionnement:
 * On presse l'interrupteur du breadboard autant de fois qu'on veut
 * Quand on presse l'interrupteur soude, la Del s'allume ce meme nombre de fois
*/ 

int main() {
    DDRA = 0x00;
    DDRB = 0xff;
    DDRD = 0x00;
    PORTB = ETEINT;
    int compteur = 0;
    bool dejaIncremente = false;
    
    for(;;) {
        if(PIND & 0x04) {
            _delay_ms(10);
            if(PIND & 0x04) {
                while(PIND & 0x04 && compteur > 0) {
                    PORTB = VERT;
                    _delay_ms(1000);
                    PORTB = ETEINT;
                    _delay_ms(500);
                    compteur--;
                }
            }
        }
        else if(PINA & 0x01) { //il faut connecter l'interrupteurau port PA1
            _delay_ms(10);
            if(PINA & 0x01) {
                PORTB = ROUGE;
                if(!dejaIncremente) {
                    compteur++;
                    dejaIncremente = true;
                }
            }
        }
        else {
            dejaIncremente = false;
            PORTB = ETEINT;
        }
    }
}
