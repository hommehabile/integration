#include "bluetooth.h"

Bluetooth::Bluetooth() {
	initialisation();
}

bool Bluetooth::testAT() {
	transmit('A');
	transmit('T');
	transmit(0x0d);
	transmit(0x0a);
	return receive();
}

void Bluetooth::changeName(char name[]) {
	setBaudRate(12);
	transmitString("AT+NAME=");
	transmitString(name);
	transmit(0x0d);
	transmit(0x0a);
}

void Bluetooth::initialisation() {
	setBaudRate(51);
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (3<<UCSZ00);
}

void Bluetooth::setBaudRate(uint8_t baud) {
	/* Set baud rate */
	UBRR0H = (uint8_t)(baud>>8);
	UBRR0L = (uint8_t)baud;
}

void Bluetooth::transmit(uint8_t data) {
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

uint8_t Bluetooth::receive() {
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}

void Bluetooth::transmitString(char *string) {
	while(*string) {
		transmit(*string++);
	}
}

uint8_t Bluetooth::receiveString(uint8_t string[], uint8_t maxSize) {
	uint8_t size = 0, temp;
	for(uint8_t i=0; i<maxSize; i++) {
		temp = receive();
		if(temp == 0x0d) {
			size = i;
			break;
		}
		else {
			string[i] = temp;
		}
	}
	//add end of line?
	return size;
}

void Bluetooth::flush() {
	uint8_t dummy;
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}