#include "lcd.h"
#include "bluetooth.h"

int main() {
	Lcd lcd(LCD_SERIAL_MODE);
	Bluetooth blue;
	DDRB = 0xff;
	PORTB = 0x00;
	DDRD |= 0x02;

	lcd.setBasicGraphics(1, 0, 0);
	uint8_t reponse[200], size;
	for(;;) {
		size = blue.receive();
		blue.receive();
		blue.receive();
		lcd.writeByte(size);
	}
}