#include "lcd.h"
#include "bluetooth.h"
#include "uart.h"

int main() {
	UART uart;
	Lcd lcd(LCD_SERIAL_MODE);
	DDRB = 0xff;
	PORTB = 0x00;
	DDRD = 0x02;

	uart.initialisationUART();
	uint8_t donnee = uart.receptionUART();
	lcd.writeByte(donnee);
	lcd.setBasicGraphics(1, 0, 0);

	for(;;) {
		donnee = uart.receptionUART();
		lcd.writeByte(donnee);
	}
}