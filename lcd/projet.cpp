#include "lcd.h"
#include "memoire_24.h"

int main() {
    _delay_ms(100);
	Memoire24CXXX unObjet;
    Lcd lcd(LCD_SERIAL_MODE);
    
    /*
    lcd.clearBasicGraphics();
    uint8_t string[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    uint8_t size = sizeof(string)/sizeof(string[0]);
    lcd.writeString(string, size);
    lcd.setBasicGraphics(1, 0, 0);
    */
    /*
    lcd.clearExtendedGraphics();
    lcd.drawRectangle(2, 2, 20, 10);
    lcd.setExtendedGraphicControl(1);
	*/

	for(;;) {} //boucle infinie
}
