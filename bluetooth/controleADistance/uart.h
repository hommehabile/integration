#ifndef UART_H
#define UART_H

#include "constantes.h"

class UART {
public:
	UART();
	void transmissionUART(uint8_t donnee);
	uint8_t receptionUART();
	void initialisationUART();
};

#endif
