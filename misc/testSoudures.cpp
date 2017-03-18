#include <avr/io.h>

#define VERT 1
#define ROUGE 2

int main() {
    DDRA = 0xff;
    DDRB = 0xff;
    DDRC = 0xff;
    DDRD = 0xff;
    
    for(;;) {
        PORTA = 0x55;
        PORTB = 0x55;
        PORTC = 0x55;
        PORTD = 0x55;
    }
}
