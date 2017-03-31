#include "uart.h"

UART::UART() {
	
}

// De l'USART vers le PC
void UART::transmissionUART(uint8_t donnee) {
	while (!(UCSR0A & (1 << UDRE0)));		//Wait for empty transmit buffer.
	UDR0 = donnee;							//Put data into buffer, sends the data.
}

// Du PC vers l'USART
uint8_t UART::receptionUART() {
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}

void UART::initialisationUART() {
	// 2400 bauds. Nous vous donnons la valeur des deux
	// premier registres pour vous eviter des complications

	//UBRRnL & UBRRnH - USART Baud Rate Registers
	//Bit 15:12 - Reserved
	//Bit 11:0  - USART Baud Rate Register.
	//			  This is a 12 bit register wich contains the USART baud rate.  
	//			  Page 189 (Atmel doc.) for more details.
	UBRR0L = 0xCF;
	UBRR0H = 0;

	//permettre la reception et la transmission par le UART0
	//UCSRnA - USART Control and Status Register A
	//UCSR0A |= 0xC6 ;

	//UCSRnB - USART Control and Status Register n B.
	//Bit 7 - RXCIEn : RX Complete Interrupt Enable n.
	//				   Enables interrupt on the RCXn flag.
	//Bit 6 - TXCIEn : TX Complete Interrupt Enable n.
	//				   Enables interrupt on the TXCn flag.
	//Bit 5 - UDRIEn : Data Register Empty Interrupt Enable n.
	//				   Enables interrupt on the UDREn flag.
	//Bit 4 - RXENn  : Receiver Enable n.
	//				   Enables the USART Receiver.
	//Bit 3 - TXENn  : Transmitter Enable n.
	//				   Enables the USART Transmitter.
	//Bit 2 - UCSZn2 : Character Size n.
	//				   Sets the number f bits in a frame the Receiver and Transmitter use.
	//Bit 1 - RXB8n  : Receive Data Bit 8 n.
	//				   It's the ninth bit of the received character when operating with serial frames with nine data bits.
	//Bit 0 - TXB8n	 : Transmit Data Bit 8 n.
	//				   It's the ninth data bit to be transmitted when operating with serial frames with nine data bits.
	UCSR0B |= _BV(RXCIE0) | _BV(TXCIE0) | _BV(UDRIE0) | _BV(RXEN0) | _BV(TXEN0);

	// Format des trames: 8 bits, 1 stop bits, none parity

	//UCSRnC - USART Control and Status Register n C.
	//Bit 7:6 - UMSELn1:0 : USART Mode Select
	//			UMSELn1		UMSELn0
	//			   0		   0		Asynchronous USART
	//			   0		   1	    Synchronous USART
	//			   1		   0		(Reserved)
	//			   1		   1		Master SPI (MSPIM)
	//Bit 5:4 - UPMn1:0   : Parity Mode
	//			UPMn1		UPMn0
	//			   0		   0		Disabled
	//			   0		   1	    Reserved
	//			   1		   0		Enabled, Even Parity
	//			   1		   1		Enabled, Odd Parity
	//Bit 3   - USBSn     : Stop Bit Select
	//						This bit selects the number of stop bits to be inserted by the Transmitter.  The Receiver ignores this setting.
	//Bit 2:1 - UCSZn1:0  : Character Size
	//						Sets the number of data bits in a frame the Receiver and the Transmitter use.
	//						Page 188 (Atmel doc.) for the chart.
	//Bit 0   - UCPOLn	  : Clock Polarity
	//						Used for synchronous mode only.  Write this bite o 0 when asynchronous mode is used.
	//						Page 189 (Atmel doc.) for the chart.
	UCSR0C |= 0x06;
}
