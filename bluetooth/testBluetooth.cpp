#include "lcd.h"
#include "bluetooth.h"

int main() {
	Lcd lcd(LCD_SERIAL_MODE);
	Bluetooth blue;
	DDRB = 0xff;
	PORTB = 0x00;
	DDRD |= 0x02;

	uint8_t reponse[200];
	uint8_t size = blue.receiveString(reponse, 200);

	lcd.writeString(reponse, size);
	lcd.setBasicGraphics(1, 0, 0);

	for(;;) {
		
	}
}