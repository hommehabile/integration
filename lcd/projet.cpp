#include "lcd.cpp"
#include "memoire_24.h"

void initialisationUART(void);
void transmissionUART(uint8_t donnee);

int main() {
    _delay_ms(100);
	Memoire24CXXX unObjet;
    Lcd lcd;
    
    lcd.clearGraphics();
    lcd.drawRectangle(2, 2, 20, 10);
    lcd.setExtendedGraphicControl(1);

	for(;;) {} //boucle infinie
}

void initialisationUART(void) {
    DDRD = 0xff;
	UBRR0L = 0xCF;
	UBRR0H = 0;
	UCSR0B |= _BV(RXCIE0) | _BV(TXCIE0) | _BV(UDRIE0) | _BV(TXEN0);
	UCSR0C |= 0x06;
}

// De l'USART vers le PC
void transmissionUART(uint8_t donnee) {
	while (!(UCSR0A & (1 << UDRE0)));		//Wait for empty transmit buffer.
	UDR0 = donnee;							//Put data into buffer, sends the data.
}
