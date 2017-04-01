#ifndef DEF_BLUETTOOTH
#define DEF_BLUETTOOTH

#include <avr/io.h>

/*
 * Pinout
 * PD0 (RXD0) = TX
 * PD1 (TXD0) = RX
*/

class Bluetooth {
public:
	Bluetooth();
	bool testAT();
	void changeName(char name[]);
	void transmit(uint8_t data);
	uint8_t receive();
	void transmitString(char *string);
	uint8_t receiveString(uint8_t string[], uint8_t maxSize);
	void flush();

private:
	void initialisation();
	void setBaudRate(uint8_t baud);
};

#endif