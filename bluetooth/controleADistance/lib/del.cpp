#include "del.h"

/***************************************************************************
 * Fonction              : Del()
 * Description           : Constructeur par defaut de la classe Del.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
Del::Del() {}

/***************************************************************************
 * Fonction              : Del
 * Description           : Constructeur par parametres de la classe Del.
 *						   Les quatres choix de Ports disponibles sont :
 *									A, B, C, D 
 *						   Les numeros des Ports disponibles pour chacun des Ports sont:
 *									1 3 5 7				(disposition)
 *									0 2 4 6				(disposition)
 *
 *									7 6 5 4 3 2 1 0		(numeros des Ports)
 *									x x x x x x x x		(binaire)
 *						   Il est a noter que le fils pourra juste etre lier a la verticale.
 *						   Pour eviter toute confusion, nous utiliserons le numeroPortUn pour
 *						   la ligne en bas et le numeroPortDeux pour la ligne en haut.
 * Parametres d'entree   : 
 * 		- port (volatile uint8_t *) :
 *						   Valeur pour initialiser l'attribut port_.
 * 	 	- numeroPortUn (uint8_t) :
 *						   Valeur pour initialiser l'attribut numeroPortUn_.
 *		- numeroPortDeux (uint8_t) :
 *						   Valeur pour initialiser l'attribut numeroPortDeux_.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
Del::Del(volatile uint8_t *port, uint8_t numeroPortUn, uint8_t numeroPortDeux){
	port_ = port;
	numeroPortUn_ = numeroPortUn;
	numeroPortDeux_ = numeroPortDeux;
	if(port_ == &PORTA)
		DDRA |= (1 << numeroPortUn_) | (1 << numeroPortDeux_);
	else if(port_ == &PORTB)
		DDRB |= (1 << numeroPortUn_) | (1 << numeroPortDeux_);
	else if(port_ == &PORTC)
		DDRC |= (1 << numeroPortUn_) | (1 << numeroPortDeux_);
	else if(port_ == &PORTD)
		DDRD |= (1 << numeroPortUn_) | (1 << numeroPortDeux_);
}


/***************************************************************************
 * Fonction              : afficherVert
 * Description           : Permet d'afficher la couleur verte.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Del::afficherVert() {
    etat_ = VERTE;			// Decimale = 1, valeur binaire = 0b01

    *port_ &= ~(1 << numeroPortDeux_);
    *port_ |= (1 << numeroPortUn_);
}

/***************************************************************************
 * Fonction              : afficherRouge
 * Description           : Permet d'afficher la couleur rouge.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Del::afficherRouge() {
	etat_ = ROUGE;			// Decimale = 2, valeur binaire = 0b10

	*port_ &= ~(1 << numeroPortUn_);
    *port_ |= (1 << numeroPortDeux_);
}

/***************************************************************************
 * Fonction              : afficherAmbre
 * Description           : Permet d'afficher la couleur ambre.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Del::afficherAmbre(){
    etat_ = AMBRE;
    afficherRouge();
    delai_ms(1);
    afficherVert();
    delai_ms(3);
}

/***************************************************************************
 * Fonction              : etteindre
 * Description           : Permet d''eteindre la DEL, peu importe l'etat dans
 *						   lequelle elle etait.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Del::eteindre() {
	etat_ = ETEINTE;		// Decimale = 0, valeur binaire = 0b00

	*port_ &= ~((1 << numeroPortUn_) | (1 << numeroPortDeux_));
}

/***************************************************************************
 * Fonction              : obtenirEtat
 * Description           : Accesseur de l'attribut etat_.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		- etat_ (uint8_t): Attribut contenant l'etat de la DEL.
 ***************************************************************************/
uint8_t Del::obtenirEtat() {
    return etat_;
}

/***************************************************************************
 * Fonction              : obtenirPort
 * Description           : Accesseur de l'attribut port_.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		- port_ (volatile uint8_t*) : 
 *						   Attribut contenant le port de la DEL.
 ***************************************************************************/
volatile uint8_t* Del::obtenirPort() {
    return port_;
}
