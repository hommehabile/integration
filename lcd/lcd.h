#ifndef DEF_LCD
#define DEF_LCD

#include "commonlib.h"

/* Pinout
 * 8 bits parralel mode
 * PB0-7 = DB0-7
 * PA0 = E
 * PA1 = R/W
 * PA2 = RS
 * PA3 = RST
 *
 * Serial mode
 * PA0 = SCLK
 * PA1 = SID
 * PA2 = CS
 * PA3 = RST
*/

//Parallel:	PSB = 1
//Serial:	PSB = 0

//constantes de gestion
#define LCD_BUS_OUT                     	PORTB
#define LCD_BUS_IN                      	PINB
#define LCD_BUS_DIRECTION_REGISTER      	DDRB
#define LCD_CONTROL_BUS_OUT              	PORTA
#define LCD_CONTROL_BUS_IN					PINA
#define LCD_CONTROL_DIRECTION_REGISTER		DDRA
//8 bits parallel mode
#define EN(x)      if(x==0){ LCD_CONTROL_BUS_OUT &= 0b11111110; } else if(x==1){ LCD_CONTROL_BUS_OUT |= 0b00000001; }
#define RW(x)      if(x==0){ LCD_CONTROL_BUS_OUT &= 0b11111101; } else if(x==1){ LCD_CONTROL_BUS_OUT |= 0b00000010; }
#define RS(x)      if(x==0){ LCD_CONTROL_BUS_OUT &= 0b11111011; } else if(x==1){ LCD_CONTROL_BUS_OUT |= 0b00000100; }
#define RST(x)     if(x==0){ LCD_CONTROL_BUS_OUT &= 0b11110111; } else if(x==1){ LCD_CONTROL_BUS_OUT |= 0b00001000; }
//serial mode
#define SCLK(x)    if(x==0){ LCD_CONTROL_BUS_OUT &= 0b11111110; } else if(x==1){ LCD_CONTROL_BUS_OUT |= 0b00000001; }
#define SID(x)     if(x==0){ LCD_CONTROL_BUS_OUT &= 0b11111101; } else if(x==1){ LCD_CONTROL_BUS_OUT |= 0b00000010; }
#define CS(x)      if(x==0){ LCD_CONTROL_BUS_OUT &= 0b11111011; } else if(x==1){ LCD_CONTROL_BUS_OUT |= 0b00000100; }

//mode de transfert de donnees
#define LCD_SERIAL_MODE 0
#define LCD_8BITS_PARALLEL_MODE 1

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
#define DELAY_CLK 2

class Lcd {
public:
    Lcd(uint8_t mode);
    void writeString(char string[], uint8_t size);
    void setBasicGraphics(uint8_t display, uint8_t cursor, uint8_t blink);
    void setExtendedGraphics(uint8_t display);
    void clearBasicGraphics();
    void clearExtendedGraphics();
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
    void transmitSerial(uint8_t rw, uint8_t rs, uint8_t data);
    uint8_t receiveSerial();

    uint8_t mode_;
};

#endif
