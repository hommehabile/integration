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
		size = blue.receiveString(reponse, 200);
		blue.flush();
		lcd.writeString(reponse, size);
	}
}