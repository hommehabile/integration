#include "del.h"

Del::Del(){}			// Constructeur par defaut.

// Constructeur par parametres.
// Les quatres choix de Ports disponibles sont : 
//
//		A, B, C, D 
//	
// Les numeros des Ports disponibles pour chacun des Ports sont:
//
//		1 3 5 7				(disposition)
//		0 2 4 6				(disposition)
//
//		7 6 5 4 3 2 1 0		(numeros des Ports)
//		x x x x x x x x		(binaire)
//
// Il est a noter que le fils pourra juste etre lier a la verticale.
// Pour eviter toute confusion, nous utiliserons le numeroPortUn pour
// la ligne en bas et le numeroPortDeux pour la ligne en haut.
Del::Del(volatile uint8_t *port, uint8_t numeroPortUn, uint8_t numeroPortDeux){
	
	port_ = port;
	numeroPortUn_ = numeroPortUn;
	numeroPortDeux_ = numeroPortDeux;
	/*if(port_ == &PORTA)
		DDRA |= (1 << numeroPortUn_) | (1 << numeroPortDeux_);
	else if(port_ == &PORTB)
		DDRB |= (1 << numeroPortUn_) | (1 << numeroPortDeux_);
	else if(port_ == &PORTC)
		DDRC |= (1 << numeroPortUn_) | (1 << numeroPortDeux_);
	else if(port_ == &PORTD)
		DDRD |= (1 << numeroPortUn_) | (1 << numeroPortDeux_);*/
}


Del::~Del(){}				// Destructeur


void Del::afficherVert() {	// Afficher la couleur vert
	
    etat_ = VERTE;			// Decimale = 1, valeur binaire = 0b01

    *port_ &= ~(1 << numeroPortDeux_);
    *port_ |= (1 << numeroPortUn_);
}

// Afficher la couleur rouge
void Del::afficherRouge() {
	
	etat_ = ROUGE;			// Decimale = 2, valeur binaire = 0b10

	*port_ &= ~(1 << numeroPortUn_);
    *port_ |= (1 << numeroPortDeux_);
}

// Afficher la couleur ambre
void Del::afficherAmbre(){
    etat_ = AMBRE;
    afficherRouge();
    _delay_ms(1);
    afficherVert();
    _delay_ms(3);
}

// Afficher aucune couleur
void Del::eteindre() {
	
	etat_ = ETEINTE;		// Decimale = 0, valeur binaire = 0b00

	*port_ &= ~((1 << numeroPortUn_) | (1 << numeroPortDeux_));
}

// Methodes d'acces
uint8_t Del::obtenirEtat() {
    return etat_;
}

volatile uint8_t* Del::obtenirLettrePort() {
    return port_;
}
uint8_t Del::obtenirNumeroPortUn() {
    return numeroPortUn_;
}

uint8_t Del::obtenirNumeroPortDeux() {
    return numeroPortDeux_;
}
