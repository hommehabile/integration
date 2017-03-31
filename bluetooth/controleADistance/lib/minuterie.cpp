#include "minuterie.h"

/***************************************************************************
 * Fonction              : Minuterie()
 * Description           : Constructeur par defaut. Ne fait rien ici.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
Minuterie::Minuterie() {
	minuterieExpiree_ = false;
}

/***************************************************************************
 * Fonction              : partirMinuterie
 * Description           : Methode qui permet de demarrer notre minuterie en
 *						   modifiant le(s) bon(s) registre(s). On remet 
 *						   egalement a zero le compteur de la minuterie.
 * Parametres d'entree   : 
 * 		- duree (uint16_t) : 
 *						   Ce parametre est la valeur maximale pour la 
 *						   comparaison (CTC timer 0). Cette valeur sera mis
 						   dans le registre OCR0A.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Minuterie::partirMinuterie(uint16_t duree) {
    minuterieExpiree_ = false;

	// TCCR0A - Timer/Counter Control Register A.
	// Bit 7 - COM0A1 : Compare Match Output A Mode.
	//					Voir tableau p.101 de la documentation.
	// Bit 6 - COM0A0 : Compare Match Output A Mode.
	//					Voir tableau p.101 de la documentation.
	// Bit 5 - COM0B1 : Compare Match Output B Mode.
	//					Voir tableau p.102 de la documentation.
	// Bit 4 - COM0B0 : Compare Match Output B Mode.
	//					Voir tableau p.102 de la documentation.
	// Bit 3 - Reserved.
	// Bit 2 - Reserved.
	// Bit 1 - WGM01  : Waveform Generation Mode.
	//					Voir tableau p.103 de la documentation.
	// Bit 0 - WGM00  : Waveform Generation Mode.
	//					Voir tableau p.103 de la documentation.
    TCCR0A |= (1 << COM0A1) | (1 << WGM01); //Mode CTC timer 0 & Clear OCR0A on Compare Match.

	// TCCR0B - Timer/Counter Control Register B.
	// Bit 7 - F0C0A : Force Output Compare Match A.
	// Bit 6 - FOC0B : Force Output Compare Match B.
	// Bit 5 - Reserved.
	// Bit 4 - Reserved.
	// Bit 3 - WGM02 : Waveforme Generation Mode.
	//				   Voir tableau p.103 de la documentation.
	// Bit 2 - CS02  : Clock Select.
	//				   Voir tableau p.104 de la documentation.
	// Bit 1 - CS01  : Clock Select.
	//				   Voir tableau p.104 de la documentation.
	// Bit 0 - CS00  : Clock Select.
	//				   Voir tableau p.104 de la documentation.
    TCCR0B |= (1 << CS00) | (1 << CS02); 	//CS00 & CS02 permettent un clock/1024.
	
    // TCNT0 - Timer/Counter Register.
	TCNT0 = 0;      	

	// OCR0A - Output Compare Register A.
    OCR0A = duree;  	
	
	// TIMSK0 - Timer/Counter Interrupt Mask Register.
	//			Bit 7:3 - Reserved.
	//			OCIE0A  - Timer/Counter Output Compare Match A Interrupt Enable.
    TIMSK0 |= (1 << OCIE0A);    	// Enable interrupt
}

/***************************************************************************
 * Fonction              : arreterMinuterie
 * Description           : Methode qui permet d'arreter notre minuterie.  On
 *						   modifie le(s) bon(s) registre(s) qui permettront
 * 						   d'arreter la minuterie sans remettre a zero le
 						   compteur de la minuterie.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Minuterie::arreterMinuterie() {
	TIMSK0 &= ~(1 << OCIE0A);    		// Disable interrupt
}

/***************************************************************************
 * Fonction              : getMinuterieExpiree
 * Description           : Methode qui permet d'obtenir la valeur de
 *						   l'attribut minuterieExpiree_.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		- expiree (bool) : Valeur que l'on veut pour l'attribut.
 ***************************************************************************/
bool Minuterie::getMinuterieExpiree() {
	return minuterieExpiree_;
}

/***************************************************************************
 * Fonction              : setMinuterieExpiree
 * Description           : Methode qui permet de modifier la valeur de
 *						   l'attribut minuterieExpiree_.
 * Parametres d'entree   : 
 * 		- expiree (bool) : Nouvelle valeur que l'on veut pour l'attribut.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Minuterie::setMinuterieExpiree(bool expiree) {
	minuterieExpiree_ = expiree;
}

/***************************************************************************
 * Fonction    : delai_us
 * Description : Nous avons cree une fonction afin de nous faciliter un peu
 *               la tache de gestions des delais.  Nous avons utilise
 *               _delay_loop_2 pour creer un delai, mais nous devons modifie
 *               la valeur du parametre pour pouvoir avoir un nombre de us
 *               bien precis.  Nous avons donc cree une fonction afin que cela
 *               soit gere a part de notre main.
 *  Parametres d'entree  : 
 * 		- nombreUs (unint16_t) : Contient le nombre de microsecondes
 *                               durant lesquels on veut un delai.
 *  Parametres de sortie :     
 * 		  Aucun.
 ***************************************************************************/
void delai_us(uint16_t nombreUs) {
    	for(uint16_t i = 0; i < nombreUs; i++) {
            _delay_loop_2(2);
        }
}

/***************************************************************************
 * Fonction :    delai_ms
 * Description : Nous avons cree une fonction afin de nous faciliter un peu
 *               la tache de gestions des delais.  Nous avons utilise
 *               _delay_loop_2 pour creer un delai, mais nous devons modifie
 *               la valeur du parametre pour pouvoir avoir un nombre de ms
 *               bien precis.  Nous avons donc cree une fonction afin que cela
 *               soit gere a part de notre main.
 *  Parametres d'entree  : 
 * 		- nombreMs (unint16_t) : Contient le nombre de microsecondes
 *                               durant lesquels on veut un delai.
 *  Parametres de sortie :     
 * 		  Aucun.
 ***************************************************************************/
void delai_ms(uint16_t nombreMs) {
    	for(uint16_t i = 0; i < nombreMs; i++) {
            _delay_loop_2(2000);
        }
}
