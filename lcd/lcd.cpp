#include "lcd.h"

Lcd::Lcd() {
    initialisation();
}

int Lcd::testing() {
    char message[] =  "AAAA";
    uint8_t size = sizeof(message)/sizeof(*message);
    //writeString(message, size);  // Calling a function to send a String of characters, as defined in 'message' string.
                                    // In Extended mode there are four line to print your text. Each line is 16characters long.
                                    // Line 1 starts at 0x80 , line 2 starts at 0x90, line 3 starts at 0x88, line 4 starts at 0x99.
    
    clearGraphics();
    
    //standby();
    
    return 0;
}

void Lcd::initialisation() {
    //initialisation des ports
    DDRA = 0xff;
	DDRB = 0xff;
    PORTA = 0x00;
    PORTB = 0x00;
    
    //initialisation de l'ecran
    EN(0);
    RW(0);
    RS(0);
    RST(0);                             // Resets the display
    _delay_ms(100);
    RST(1);
    _delay_us(DELAY_US);
    sendCommand(CMD_8BITS_INTERFACE) ;  // 8-bit mode.
    _delay_us(DELAY_US);
    sendCommand(CMD_8BITS_INTERFACE);   // 8-bit mode again.
    _delay_us(DELAY_US);
    setBasicGraphicControl(1, 0, 0);         // Display on
    _delay_us(DELAY_US);
    sendCommand(CMD_CLEAR_DISPLAY);     // Clears screen.
    _delay_ms(DELAY_MS);
    sendCommand(CMD_ENTRY_MODE_RIGHT);  // Cursor moves right, no display shift.
    _delay_us(DELAY_US);
    sendCommand(CMD_RETURN_HOME);       // Returns to home. Cursor moves to starting point.
    _delay_us(DELAY_US);
}

void Lcd::writeString(char string[], uint8_t size) {
    setBusDirection(BUS_OUT);
    RS(0);
    RW(0);
    sendCommand(CMD_BASIC_INSTRUCTION);
    _delay_us(DELAY_US);
    for(uint8_t i=0; i<32; i++) {
        //if(string[i] == 'A')
        sendData(i);
    }
}

void Lcd::sendCommand(uint8_t command) {
    setBusDirection(BUS_OUT);
    RW(0);
    RS(0);
    _delay_ms(DELAY_MS);
    LCD_BUS_OUT = command;
    EN(1);
    _delay_ms(DELAY_MS);
    EN(0);
}

void Lcd::sendData(uint8_t data) {
    setBusDirection(BUS_OUT);
    RS(1);
    RW(0);
    _delay_ms(DELAY_MS);
    LCD_BUS_OUT = data;
    EN(1);
    _delay_ms(DELAY_MS);
    EN(0);
}

uint8_t Lcd::readData() {
    setBusDirection(BUS_IN);
    RS(1);
    RW(1);
    EN(1);
    _delay_ms(DELAY_MS);
    uint8_t data = LCD_BUS_IN;
    _delay_ms(DELAY_MS);
    EN(0);
    return data;
}

uint8_t Lcd::readAddressCounter() {
    setBusDirection(BUS_IN);
    RS(0);
    RW(1);
    EN(1);
    _delay_ms(DELAY_MS);
    uint8_t ad = LCD_BUS_IN;
    _delay_ms(DELAY_MS);
    EN(0);
    return ad & 0x7f;
}

uint8_t Lcd::readBusyFlag() {
    setBusDirection(BUS_IN);
    RS(0);
    RW(1);
    EN(1);
    _delay_ms(DELAY_MS);
    uint8_t bf = LCD_BUS_IN;
    _delay_ms(DELAY_MS);
    EN(0);
    return bf >> 7;
}

void Lcd::setBasicGraphicControl(uint8_t display, uint8_t cursor, uint8_t blink) {
    setBusDirection(BUS_OUT);
    RS(0);
    RW(0);
    sendCommand(CMD_BASIC_INSTRUCTION);
    _delay_us(DELAY_US);
    sendCommand(CMD_BASIC_DISPLAY_CONTROL | (display << 2) | (cursor << 1) | (blink << 0));
    _delay_us(DELAY_US);
}

void Lcd::setExtendedGraphicControl(uint8_t display) {
    setBusDirection(BUS_OUT);
    RS(0);
    RW(0);
    sendCommand(CMD_EXTENDED_INSTRUCTION);
    _delay_us(DELAY_US);
    sendCommand(CMD_EXTENDED_DISPLAY_CONTROL | (display << 1));
    _delay_us(DELAY_US);
}

void Lcd::setGDRAMaddress(uint8_t x, uint8_t y) {
    //conversion for the weird shaped screen
    if(y > 31) {
        y -= 32;
        x += 8;
    }
    //setting the address
    setBusDirection(BUS_OUT);
    RS(0);
    RW(0);
    sendCommand(CMD_EXTENDED_INSTRUCTION);
    _delay_us(DELAY_US);
    sendCommand(CMD_SET_GDRAM_ADDRESS | y);
    _delay_us(DELAY_US);
    sendCommand(CMD_SET_GDRAM_ADDRESS | x);
    _delay_us(DELAY_US);
}

void Lcd::setDDRAMaddress(uint8_t address) {
    setBusDirection(BUS_OUT);
    RS(0);
    RW(0);
    sendCommand(CMD_BASIC_INSTRUCTION);
    _delay_us(DELAY_US);
    sendCommand(CMD_SET_DDRAM_ADDRESS | address);
    _delay_us(DELAY_US);
}

void Lcd::standby() {
    setBusDirection(BUS_OUT);
    RS(0);
    RW(0);
    sendCommand(CMD_EXTENDED_INSTRUCTION);
    _delay_us(DELAY_US);
    sendCommand(CMD_STANDBY);
    _delay_us(DELAY_US);
}

void Lcd::returnHome() {
    setBusDirection(BUS_OUT);
    RS(0);
    RW(0);
    sendCommand(CMD_BASIC_INSTRUCTION);
    _delay_us(DELAY_US);
    sendCommand(CMD_RETURN_HOME);
    _delay_us(DELAY_US);
}

void Lcd::clearGraphics() {
    setBusDirection(BUS_OUT);
    RS(0);
    RW(0);
    unsigned char x, y;
    for(y = 0; y < 64; y++) {
        setGDRAMaddress(x, y);
        for(x = 0; x < 8; x++) {
            sendData(0x00);
            sendData(0x00);
        }
    }
}

void Lcd::setPixel(uint8_t x, uint8_t y) {
	setBusDirection(BUS_OUT);
    RS(0);
    RW(0);
    sendCommand(CMD_EXTENDED_INSTRUCTION);

    uint8_t modulo = x % 16; //position in the register
    uint8_t xpos = (x - modulo) / 16; //word position
    uint16_t dot = 0x8000;    //this will be shifted into it's correct position in the word

    //reading previous value
    setGDRAMaddress(xpos, y);
    readData(); //dummy read();
    uint16_t previousData = 0x0000 | (readData() << 8); //high byte
    previousData |= readData(); //low byte

    //writing current value
    setGDRAMaddress(xpos, y);
    uint16_t currentData = previousData | (dot >> modulo);
    sendData((uint8_t)(currentData >> 8)); //high byte
	sendData((uint8_t)currentData); //low byte
}

void Lcd::clearPixel(uint8_t x, uint8_t y) {
    setBusDirection(BUS_OUT);
    RS(0);
    RW(0);
    sendCommand(CMD_EXTENDED_INSTRUCTION);

    uint8_t modulo = x % 16; //position in the register
    uint8_t xpos = (x - modulo) / 16; //word position
    uint16_t dot = 0x8000;    //this will be shifted into it's correct position in the word

    //reading previous value
    setGDRAMaddress(xpos, y);
    readData(); //dummy read();
    uint16_t previousData = 0x0000 | (readData() << 8); //high byte
    previousData |= readData(); //low byte

    //writing current value
    setGDRAMaddress(xpos, y);
    uint16_t currentData = previousData & (0xffff ^ (dot >> modulo));
    sendData((uint8_t)(currentData >> 8)); //high byte
	sendData((uint8_t)currentData); //low byte
}

void Lcd::setPixels(uint8_t x, uint8_t y, uint16_t data) {
    setBusDirection(BUS_OUT);
    RS(0);
    RW(0);
    sendCommand(CMD_EXTENDED_INSTRUCTION);

    uint8_t modulo = x % 16; //position in the register
    uint8_t xpos = (x - modulo) / 16; //word position

    //writing value
    setGDRAMaddress(xpos, y);
    sendData((uint8_t)(data >> 8)); //high byte
	sendData((uint8_t)data); //low byte
}

void Lcd::drawRectangle(uint8_t x, uint8_t y, uint8_t largeur, uint8_t hauteur) {
    uint8_t i, j;
    for(i = x; i < x + largeur; i++) {
    	for(j = y; j < y + hauteur; j++) {
    		setPixel(i, j);
    	}
    }
}

void Lcd::setBusDirection(uint8_t direction) {
    if(direction == BUS_IN)
        LCD_BUS_DIRECTION_REGISTER = 0x00;
    else if(direction == BUS_OUT)
        LCD_BUS_DIRECTION_REGISTER = 0xff;
}
