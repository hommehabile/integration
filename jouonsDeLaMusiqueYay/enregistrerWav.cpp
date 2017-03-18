
#define F_CPU 8000000UL

#define ETEINTE 0x00
#define VERTE 0x01
#define ROUGE 0x02

#include <util/delay.h>
#include "memoire_24.h"

void pcCommunicationTest();
void savingTest();
void USART_Trasmit(uint8_t data);
uint8_t USART_Receive();
void initialisationUART();

int main() {
    initialisationUART();
    
    //Memoire24CXXX unObjet;
    
    uint16_t adresse = 0x00;
    
    /*
    uint8_t tableauEcriture[] = {"E*C*O*L*E* *P*O*L*Y*T*E*C*H*N*I*Q*U*E*"};
    uint8_t sizeTableau = sizeof(tableauEcriture) / sizeof(uint8_t);
    unObjet.ecriture(adresse, tableauEcriture, sizeTableau);
    
    uint8_t tableauLecture[sizeTableau];
    unObjet.lecture(adresse, tableauLecture, sizeTableau);

    bool ok = true;
    for(uint8_t i = 0; i < sizeTableau && ok; i++) {
        if(tableauEcriture[i] != tableauLecture[i] )
            ok = false;
    }
    
    if(ok) {
        PORTA = 0x01;       //LUMIERE VERTE
    }
    else
        PORTA = 0x02;       //LUMIERE ROUGE
    
    
    for(uint8_t i=0; i<sizeTableau; i++) {
        transmissionUART(tableauLecture[i]);
    }
    */
    savingTest();
}

void pcCommunicationTest() {
    //reception
    PORTA = ROUGE;
    uint8_t tab[20] = {};
    for(uint8_t i=0; i<20; i++) {
        tab[i] = USART_Receive();
    }
    //transmission
    PORTA = VERTE;
    for(uint8_t i=0; i<20; i++) {
        USART_Trasmit(tab[i]);
    }
    PORTA = ETEINTE;
}

void savingTest() {
    //recuperation des donnees depuis le pc
    PORTA = ETEINTE;
    uint32_t size = USART_Receive() << 24;
    size |= USART_Receive() << 16;
    size |= USART_Receive() << 8;
    size |= USART_Receive();
    size--; //on enleve EOF
    PORTA = ROUGE;
    uint8_t tableau[size];
    for(uint32_t i=0; i<size; i++) {
        tableau[i] = USART_Receive();
    }
    PORTA = VERTE;
    //ecriture dans l'eeprom
    uint16_t adresse = 0x00;
    Memoire24CXXX unObjet;
    const uint8_t sizeTableau = sizeof(tableau) / sizeof(uint8_t);
    unObjet.ecriture(adresse, tableau, sizeTableau);
    PORTA = ETEINTE;
}

void USART_Trasmit(uint8_t data) {
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) );
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

uint8_t USART_Receive() {
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) );
    /* Get and return received data from buffer */
    return UDR0;
}

void initialisationUART() {
    DDRA = 0xff;
    
    // permettre la reception et la transmission par le UART0
    //UCSR0A = 'modifier ici'; //rien a mettre
    UCSR0B |= _BV(RXCIE0) | _BV(TXCIE0) | _BV(UDRIE0) | _BV(RXEN0) | _BV(TXEN0);

    // Format des trames: 8 bits, 1 stop bits, none parity
    //UCSR0C |= _BV(UCSZ1) | _BV(UCSZ0);
    UCSR0C |= 0x06;
    
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premier registres pour vous éviter des complications
    UBRR0H = 0;
    UBRR0L = 0xCF;
}



