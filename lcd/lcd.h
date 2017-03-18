#ifndef DEF_LCD
#define DEF_LCD

#include "commonlib.h"

/* Pinout
 * PB0-7 = DB0-7
 * PA0 = E
 * PA1 = R/W
 * PA2 = RS
 * PA3 = RST
*/

//constantes de gestion
#define LCD_BUS_OUT                     PORTB
#define LCD_BUS_IN                      PINB
#define LCD_BUS_DIRECTION_REGISTER      DDRB
#define CONTROL_BUS                     PORTA
#define EN(x)      if(x==0){ CONTROL_BUS &= 0b11111110; } else if(x==1){ CONTROL_BUS |= 0b00000001; }
#define RW(x)      if(x==0){ CONTROL_BUS &= 0b11111101; } else if(x==1){ CONTROL_BUS |= 0b00000010; }
#define RS(x)      if(x==0){ CONTROL_BUS &= 0b11111011; } else if(x==1){ CONTROL_BUS |= 0b00000100; }
#define RST(x)     if(x==0){ CONTROL_BUS &= 0b11110111; } else if(x==1){ CONTROL_BUS |= 0b00001000; }

//bus directions
#define BUS_IN 0
#define BUS_OUT 1

//basic instructions
#define CMD_CLEAR_DISPLAY               0b00000001 //Clear display
#define CMD_RETURN_HOME                 0b00000010 //Return Home
#define CMD_ENTRY_MODE_RIGHT            0b00000110 //Entry mode set for: Cursor moves to the right after writing
#define CMD_BASIC_DISPLAY_CONTROL       0b00001000
#define CMD_EXTENDED_INSTRUCTION        0b00110100 //Enable instruction set 2
#define CMD_8BITS_INTERFACE             0b00110000 //Specify the interface
#define CMD_SET_DDRAM_ADDRESS           0b10000000

//extended instructions
#define CMD_STANDBY                     0b00000001 //Puts display on standby
#define CMD_BASIC_INSTRUCTION           0b00110000 //Enable instruction set 1
#define CMD_EXTENDED_DISPLAY_CONTROL    0b00110100
#define CMD_SET_GDRAM_ADDRESS           0b10000000

//standard delays
#define DELAY_US 80
#define DELAY_MS 2

class Lcd {
public:
    Lcd();
    int testing();
    void writeString(char string[], uint8_t size);
    void setBasicGraphicControl(uint8_t display, uint8_t cursor, uint8_t blink);
    void setExtendedGraphicControl(uint8_t display);
    void clearGraphics();
    void sendData(uint8_t data);
    uint8_t readData();
    uint8_t readAddressCounter();
    uint8_t readBusyFlag();
    void returnHome();
    void standby();
    void setPixel(uint8_t x, uint8_t y);
    void clearPixel(uint8_t x, uint8_t y);
    void setPixels(uint8_t x, uint8_t y, uint16_t data);
    void drawRectangle(uint8_t x, uint8_t y, uint8_t largeur, uint8_t hauteur);

private:
    void initialisation();
    void setBusDirection(uint8_t direction);
    void sendCommand(uint8_t command);
    void setGDRAMaddress(uint8_t x, uint8_t y);
    void setDDRAMaddress(uint8_t address);
};

#endif
