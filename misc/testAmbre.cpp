#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

#define POURCENT_VERT 95

int main() {
    DDRA = 0xff;
    DDRD = 0x00;
    uint8_t valueA = 0;
    PORTA = 0;
    bool alterne = false;
    int compteur = 0;
    
    for(;;) {
        if(true) {
            if(compteur <= POURCENT_VERT)
                valueA = 0x01;
            else
                valueA = 0x02;
            PORTA = valueA;
            compteur++;
            if(compteur > 100)
                compteur = 0;
        } else {
            valueA = 0x00;
            PORTA = valueA;
        }
    }
}
