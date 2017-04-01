#include "uart.h"
#include "memoire_24.h"
#include <avr/io.h>

void transferer();
void testerTransfert();

int main() {
	DDRA = 0xff;
	PORTA = 0x00;
	transferer();
	//testerTransfert();
}

void transferer() {
	//initialisation
	PORTA = 0x02;
	UART uart;
	uart.initialisationUART();
	Memoire24CXXX memoire;

	//reception de la taille
	//la taille doit etre transmise le high byte en premier
	uint16_t taille = 0x00 | (uart.receptionUART() << 8);
	taille |= uart.receptionUART();
	//ecriture de la taille
	memoire.ecriture(0x00, (uint8_t)(taille >> 8));
	memoire.ecriture(0x01, (uint8_t)(taille));

	//boucle principale
	uint8_t temp;
	for(uint8_t i=2; i<taille; i++) {
		temp = uart.receptionUART(); //reception
		memoire.ecriture(i, temp); //transfert des donnees vers la memoire externe
	}

	PORTA = 0x01; //confirmation
}

void testerTransfert() {
	//initialisation
	PORTA = 0x02;
	UART uart;
	uart.initialisationUART();
	Memoire24CXXX memoire;

	//aquisition de la taille
	uint8_t getter;
	memoire.lecture(0x00, &getter);
	uint16_t taille = 0x0000 | (getter << 8);
	memoire.lecture(0x01, &getter);
	taille |= getter;
	//ecriture de la taille
	//la taille doit etre transmise le high byte en premier
	uart.transmissionUART((uint8_t)(taille >> 8));
	uart.transmissionUART((uint8_t)(taille));

	//boucle principale
	uint8_t temp = 0;
	for(uint8_t i=2; i<taille; i++) {
		memoire.lecture(i, &temp); //lecture
		uart.transmissionUART(temp); //transfert des donnees vers le PC
	}

	PORTA = 0x01; //confirmation
}
