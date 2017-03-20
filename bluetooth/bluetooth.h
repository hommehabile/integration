#ifndef DEF_BLUETTOOTH
#define DEF_BLUETTOOTH

/*
 * Pinout
 * PD0 (RXD0) = TX
 * PD1 (TXD0) = RX
*/

class Bluetooth {
public:
	Bluetooth();
	void setBaudRate(uint8_t baud);

private:
	void initialisation();
};

#endif