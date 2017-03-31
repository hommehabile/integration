#include "bouton.h"

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
bool etatBoutton(Ports port, uint8_t pin){
    bool etatBtn = false;
	switch(port) {
		case A:
			etatBtn = antiRebond(PINA, pin);
			break;
		case B:
			etatBtn = antiRebond(PINB, pin); 
			break;
		case C:
			etatBtn = antiRebond(PINC, pin); 
			break;
		case D:
			etatBtn = antiRebond(PIND, pin); 
			break;
	}
    return etatBtn;
}

 /***************************************************************************
 * Fonction              : antiRebond
 * Description           : Cette fonction permet d'obtenir l'etat reel d'un 
 * 						   port et d'une pin specifie en parametre.  En effet,
 * 					       cette fonction permet d'ignorer les rebonds mecaniques
 * 						   produient lorsque l'on presse un boutton, et ainsi 
 * 					       detecte que le boutton n'a ete presse qu'une seule fois 
 *						   dans un tres court interval de temps.
 * Parametres d'entree   : 
 * 		- unPort (uint8_t) : 
 *						   Specifie le port dont il faut verifier l'etat.
 *		- laPin  (uint8_t) : 
 *						   Specifie le numero de la pin dont il faut verifier l'etat.
 * Parametres de sortie  :     
 * 		- etat (bool)      : 
 *						   Renvoie l'etat du boutton.  Si le boutton est pressé,
 *                         etatBtn sera a TRUE.  Si le boutton n'est pas pressé, etatBtn
 *                         sera à FALSE.
 ***************************************************************************/
bool antiRebond(uint8_t unPort, uint8_t laPin) {
	bool etat = false;
	if(unPort & laPin) {
		_delay_ms(10);
		if(unPort & laPin)         
			etat = true;   
	}
	return etat;
}