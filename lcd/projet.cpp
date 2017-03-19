#include "lcd.h"
#include "memoire_24.h"

int main() {
    _delay_ms(100);
	Memoire24CXXX unObjet;
    Lcd lcd(LCD_SERIAL_MODE);
    /*
    uint16_t value = 0;
    uint8_t temp = 0;
    unObjet.lecture(2, &temp);
    value = 0x0000 | (temp << 8);
    unObjet.lecture(3, &temp);
    value |= temp;
    */
    
    uint8_t string[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    uint8_t size = sizeof(string)/sizeof(string[0]);
    lcd.writeString(string, size);
    /*
    lcd.returnHome();
    uint8_t value = lcd.readAddressCounter();
    lcd.writeByte(value);
    uint8_t string2[] = "Yo";
    uint8_t size2 = sizeof(string2)/sizeof(string2[0]);
    //lcd.writeString(string2, size2);*/
    lcd.setBasicGraphics(1, 0, 0);
    
    /*
    lcd.clearExtendedGraphics();
    lcd.setPixel(32, 2);
    //lcd.drawRectangle(2, 2, 20, 10);
    lcd.setExtendedGraphics(1);
	*/

	for(;;) {} //boucle infinie
}
