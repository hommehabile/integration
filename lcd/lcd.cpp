#include "lcd.h"

Lcd::Lcd(uint8_t mode) {
	mode_ = mode;
    initialisation();
}

void Lcd::initialisation() {
    //initialisation des ports
    if(mode_ == LCD_8BITS_PARALLEL_MODE) {
    	LCD_BUS_DIRECTION_REGISTER = 0xff;
    	LCD_CONTROL_DIRECTION_REGISTER |= 0x0f;
    	LCD_BUS_OUT = 0x00;
    	LCD_CONTROL_BUS_OUT = 0x08;
    } else {
    	LCD_CONTROL_DIRECTION_REGISTER |= 0x0f;
    	LCD_CONTROL_BUS_OUT = 0x0c;
    }
    
    //initialisation de l'ecran
    RST(0);                             // Resets the display
    _delay_ms(100);
    RST(1);
    _delay_us(DELAY_US);
    sendCommand(CMD_8BITS_INTERFACE) ;  // 8-bit mode.
    _delay_us(DELAY_US);
    sendCommand(CMD_8BITS_INTERFACE);   // 8-bit mode again.
    _delay_us(DELAY_US);
    sendCommand(CMD_ENTRY_MODE_RIGHT);  // Cursor moves right, no display shift.
    _delay_us(DELAY_US);
    sendCommand(CMD_RETURN_HOME);       // Returns to home. Cursor moves to starting point.
    _delay_us(DELAY_US);
}

void Lcd::writeString(uint8_t string[], uint8_t size) {
	clearBasicGraphics();
    uint8_t tempSize = size;
    for(uint8_t i=0; i<tempSize && i<16; i++) {
        sendData(*string++);
    }
    if(tempSize > 16) {
    	tempSize -= 16;
    	setDDRAMaddress(0x90); //deuxieme ligne
    	for(uint8_t i=0; i<tempSize && i<16; i++) {
	        sendData(*string++);
	    }
	    if(tempSize > 16) {
	    	tempSize -= 16;
	    	setDDRAMaddress(0x88); //troisieme ligne
	    	for(uint8_t i=0; i<tempSize && i<16; i++) {
		        sendData(*string++);
		    }
		    if(tempSize > 16) {
		    	tempSize -= 16;
		    	setDDRAMaddress(0x98); //quatrieme ligne
		    	for(uint8_t i=0; i<tempSize && i<16; i++) {
			        sendData(*string++);
			    }
		    }
	    }
    }
}

void Lcd::writeHex(uint8_t hex) {
	//Ecrit un octect sous la forme 0xHH
	sendCommand(CMD_BASIC_INSTRUCTION);
    sendData('0');
    sendData('x');
    for(char i=1; i>=0; i--) {
    	uint8_t half = (hex >> (4*i)) & 0x0f;
    	switch(half) {
    		case 10:
    			sendData('A');
    			break;
    		case 11:
    			sendData('B');
    			break;
    		case 12:
    			sendData('C');
    			break;
    		case 13:
    			sendData('D');
    			break;
    		case 14:
    			sendData('E');
    			break;
    		case 15:
    			sendData('F');
    			break;
    		default:
    			sendData(half);
    			break;
    	}
    }
}

void Lcd::writeByte(uint8_t byte) {
	//Ecrit un octect sous la forme 0bXXXXXXXX
	sendCommand(CMD_BASIC_INSTRUCTION);
    sendData('0');
    sendData('b');
    for(uint8_t i=0; i<8; i++) {
    	sendData(0x30 | ((byte >> (7-i)) & 0x01));
    }
}

void Lcd::sendCommand(uint8_t command) {
	setBusDirection(BUS_OUT);
	if(mode_ == LCD_8BITS_PARALLEL_MODE) {
	    RW(0);
	    RS(0);
	    _delay_ms(DELAY_MS);
	    LCD_BUS_OUT = command;
	    EN(1);
	    _delay_ms(DELAY_MS);
	    EN(0);
	}
	else {
		transmitSerial(0, 0, command);
	}
}

void Lcd::sendData(uint8_t data) {
	setBusDirection(BUS_OUT);
	if(mode_ == LCD_8BITS_PARALLEL_MODE) {
	    RW(0);
	    RS(1);
	    _delay_ms(DELAY_MS);
	    LCD_BUS_OUT = data;
	    EN(1);
	    _delay_ms(DELAY_MS);
	    EN(0);
	}
	else {
		transmitSerial(0, 1, data);
	}
}

uint8_t Lcd::readData() {
	setBusDirection(BUS_IN);
	uint8_t data;
	if(mode_ == LCD_8BITS_PARALLEL_MODE) {
	    RW(1);
	    RS(1);
	    EN(1);
	    _delay_ms(DELAY_MS);
	    data = LCD_BUS_IN;
	    _delay_ms(DELAY_MS);
	    EN(0);
	    
	}
	else {
		data = 0x00; //read not supported in serial mode
	}
	return data;
}

uint8_t Lcd::readAddressCounter() {
	setBusDirection(BUS_IN);
	uint8_t ad;
	if(mode_ == LCD_8BITS_PARALLEL_MODE) {
	    RW(1);
	    RS(0);
	    EN(1);
	    _delay_ms(DELAY_MS);
	    ad = LCD_BUS_IN;
	    _delay_ms(DELAY_MS);
	    EN(0);
	}
	else {
		ad = 0x00; //read not supported in serial mode
	}
	return ad & 0x7f;
}

uint8_t Lcd::readBusyFlag() {
	setBusDirection(BUS_IN);
	uint8_t bf;
	if(mode_ == LCD_8BITS_PARALLEL_MODE) {
	    RW(1);
	    RS(0);
	    EN(1);
	    _delay_ms(DELAY_MS);
	    bf = LCD_BUS_IN;
	    _delay_ms(DELAY_MS);
	    EN(0);
	}
	else {
		bf = 0x00; //read not supported in serial mode
	}
	return bf >> 7;
}

void Lcd::setBasicGraphics(uint8_t display, uint8_t cursor, uint8_t blink) {
    sendCommand(CMD_BASIC_INSTRUCTION);
    _delay_us(DELAY_US);
    sendCommand(CMD_BASIC_DISPLAY_CONTROL | (display << 2) | (cursor << 1) | (blink << 0));
    _delay_us(DELAY_US);
}

void Lcd::setExtendedGraphics(uint8_t display) {
    sendCommand(CMD_EXTENDED_INSTRUCTION);
    _delay_us(DELAY_US);
    sendCommand(CMD_EXTENDED_DISPLAY_CONTROL | (display << 1));
    _delay_us(DELAY_US);
}

void Lcd::clearBasicGraphics() {
	sendCommand(CMD_BASIC_INSTRUCTION);
	_delay_us(DELAY_US);
	sendCommand(CMD_CLEAR_DISPLAY);
	_delay_ms(DELAY_MS);
}

void Lcd::clearExtendedGraphics() {
    unsigned char x, y;
    for(y = 0; y < 64; y++) {
        setGDRAMaddress(x, y);
        for(x = 0; x < 8; x++) {
            sendData(0x00);
            sendData(0x00);
        }
    }
}

void Lcd::setGDRAMaddress(uint8_t x, uint8_t y) {
    //conversion for the weird shaped screen
    if(y > 31) {
        y -= 32;
        x += 8;
    }
    //setting the address
    sendCommand(CMD_EXTENDED_INSTRUCTION);
    _delay_us(DELAY_US);
    sendCommand(CMD_SET_GDRAM_ADDRESS | y);
    _delay_us(DELAY_US);
    sendCommand(CMD_SET_GDRAM_ADDRESS | x);
    _delay_us(DELAY_US);
}

void Lcd::setDDRAMaddress(uint8_t address) {
    sendCommand(CMD_BASIC_INSTRUCTION);
    _delay_us(DELAY_US);
    sendCommand(CMD_SET_DDRAM_ADDRESS | address);
    _delay_us(DELAY_US);
}

void Lcd::standby() {
    sendCommand(CMD_EXTENDED_INSTRUCTION);
    _delay_us(DELAY_US);
    sendCommand(CMD_STANDBY);
    _delay_us(DELAY_US);
}

void Lcd::returnHome() {
    sendCommand(CMD_BASIC_INSTRUCTION);
    _delay_us(DELAY_US);
    sendCommand(CMD_RETURN_HOME);
    _delay_us(DELAY_US);
}

void Lcd::setPixel(uint8_t x, uint8_t y) {
    sendCommand(CMD_EXTENDED_INSTRUCTION);

    uint8_t modulo = x % 16; //position in the register
    uint8_t xpos = (x - modulo) / 16; //word position
    uint16_t dot = 0x8000;    //this will be shifted into it's correct position in the word

    //reading previous value
    setGDRAMaddress(xpos, y);
    readData(); //dummy read();
    uint16_t previousData = 0x0000 | (readData() << 8); //high byte
    previousData |= readData(); //low byte
    if(previousData != 0xffff) {
    	//writing current value
	    setGDRAMaddress(xpos, y);
	    uint16_t currentData = previousData | (dot >> modulo);
	    sendData((uint8_t)(currentData >> 8)); //high byte
		sendData((uint8_t)currentData); //low byte
    }
	    
}

void Lcd::clearPixel(uint8_t x, uint8_t y) {
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
    if(mode_ == LCD_8BITS_PARALLEL_MODE) {
    	if(direction == BUS_IN)
	        LCD_BUS_DIRECTION_REGISTER = 0x00;
	    else if(direction == BUS_OUT)
	        LCD_BUS_DIRECTION_REGISTER = 0xff;
    }
	else {
		if(direction == BUS_IN)
	        LCD_CONTROL_DIRECTION_REGISTER &= 0xfd;
	    else if(direction == BUS_OUT)
	        LCD_CONTROL_DIRECTION_REGISTER |= 0x02;
	}
}

void Lcd::transmitSerial(uint8_t rw, uint8_t rs, uint8_t data) {
	uint8_t i;
	SID(1);
	for(i=0; i<5; i++) { //synchronizing bit string
		SCLK(1);
		_delay_us(DELAY_CLK);
		SCLK(0);
		_delay_us(DELAY_CLK);
	}
	SID(rw); //RW
	SCLK(1);
	_delay_us(DELAY_CLK);
	SCLK(0);
	_delay_us(DELAY_CLK);
	SID(rs); //RS
	SCLK(1);
	_delay_us(DELAY_CLK);
	SCLK(0);
	_delay_us(DELAY_CLK);
	SID(0); //buff
	SCLK(1);
	_delay_us(DELAY_CLK);
	SCLK(0);
	_delay_us(DELAY_CLK);
	for(i=0; i<4; i++) {
		SID(((data >> (7-i)) & 0x01));
		SCLK(1);
		_delay_us(DELAY_CLK);
		SCLK(0);
		_delay_us(DELAY_CLK);
	}
	SID(0);
	for(i=0; i<4; i++) {
		SCLK(1);
		_delay_us(DELAY_CLK);
		SCLK(0);
		_delay_us(DELAY_CLK);
	}
	for(i=0; i<4; i++) {
		SID(((data >> (3-i)) & 0x01));
		SCLK(1);
		_delay_us(DELAY_CLK);
		SCLK(0);
		_delay_us(DELAY_CLK);
	}
	SID(0);
	for(i=0; i<4; i++) {
		SCLK(1);
		_delay_us(DELAY_CLK);
		SCLK(0);
		_delay_us(DELAY_CLK);
	}
}