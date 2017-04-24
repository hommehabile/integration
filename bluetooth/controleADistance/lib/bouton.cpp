#include "bouton.h"

Bouton::Bouton() {}

/***************************************************************************
 * Fonction              : Bouton()
 * Description           : Constructeur par parametre de la classe Bouton.
 * Parametres d'entree   : 
 * 		- regitre (volatile uint8_t *) :
 *						   Permettera l'initisation des PINs du bon port.
 *	    - numeroPin (uint8_t) :
 *						   Specifie qu'elle PIN initialiser.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
Bouton::Bouton(volatile uint8_t *registre, uint8_t numeroPin, bool inverse) {
	registre_ = registre;
	numeroPin_ = numeroPin;
	inverse_ = inverse;

	if(registre_ == &PORTA)
		DDRA &= ~(1 << numeroPin_);
	else if(registre_ == &PORTB)
		DDRB &= ~(1 << numeroPin_);
	else if(registre_ == &PORTC)
		DDRC &= ~(1 << numeroPin_);
	else if(registre_ == &PORTD)
		DDRD &= ~(1 << numeroPin_);
}

 /***************************************************************************
 * Fonction              : etatBoutton
 * Description           : Cette fonction permet de retourner l'etat dans
 *						    lequel se trouve la pin du port specifie en parametre.
 * Parametres d'entree   : 
 * 		- port (Ports)   : Specifie le port dont il faut verifier l'etat.
 *		- pin  (uint8_t) : Specifie le numero de la pin dont il faut verifier l'etat.
 * Parametres de sortie  :     
 * 		- etatBtn (bool) : Renvoie l'etat du boutton.  Si le boutton est presse, 
 *						   etatBtn sera a TRUE.  Si le boutton n'est pas presse,
 *                         etatBtn sera a FALSE.
 ***************************************************************************/
bool Bouton::etatBouton(){
    bool etat = false;
    if(inverse_) {
    	if(~(*registre_ | ~(1<<numeroPin_))) {
			_delay_ms(10);
			if(~(*registre_ | ~(1<<numeroPin_)))         
				etat = true;   
		}
    }
	else {
		if(*registre_ & (1<<numeroPin_)) {
			_delay_ms(10);
			if(*registre_ & (1<<numeroPin_))         
				etat = true;   
		}
	}
	return etat;
}