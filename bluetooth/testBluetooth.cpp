#include "lcd.h"
#include "bluetooth.h"

int main() {
	Lcd lcd(LCD_SERIAL_MODE);
	Bluetooth blue;
	DDRB = 0xff;
	PORTB = 0x00;
	DDRD = 0x02;

	PORTB = 0x02;
	uint8_t reponse[200];
	uint8_t size = blue.receiveString(reponse, 200);
	PORTB = 0x01;

	lcd.setBasicGraphics(1, 1, 0);
	//lcd.writeString(reponse, size);
	for (int i = 0; i < size; ++i)
	{
		lcd.writeByte(reponse[i]);
	}

	PORTB = 0x00;
	if(reponse[0] != 'a')
		PORTB = 0x00;

	for(;;) {
		
	}
}