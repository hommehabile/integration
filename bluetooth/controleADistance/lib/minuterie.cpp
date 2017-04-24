#include "minuterie.h"

volatile bool minuterieExpiree = false;
volatile uint16_t nombreIterations = 0;

ISR(TIMER2_COMPA_vect) {
	PORTB = 0x02;
	if(nombreIterations>0)
		nombreIterations--;
	else {
		minuterieExpiree = true;
		TCCR2B &= ~(1 << CS21) & ~(1 << CS22);
	}
}

/***************************************************************************
 * Fonction              : Minuterie()
 * Description           : Constructeur par defaut. Ne fait rien ici.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
Minuterie::Minuterie() {
	minuterieExpiree = false;
	nombreIterations = 0;
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
    minuterieExpiree = false;
    nombreIterations = duree; //nombre de millisecondes

	// TCCR0A - Timer/Counter Control Register A.
	// Bit 7 - COM2A1 : Compare Match Output A Mode.
	//					Voir tableau p.1055 de la documentation.
	// Bit 6 - COM2A0 : Compare Match Output A Mode.
	//					Voir tableau p.101 de la documentation.
	// Bit 5 - COM2B1 : Compare Match Output B Mode.
	//					Voir tableau p.102 de la documentation.
	// Bit 4 - COM2B0 : Compare Match Output B Mode.
	//					Voir tableau p.102 de la documentation.
	// Bit 3 - Reserved.
	// Bit 2 - Reserved.
	// Bit 1 - WGM21  : Waveform Generation Mode.
	//					Voir tableau p.103 de la documentation.
	// Bit 0 - WGM20  : Waveform Generation Mode.
	//					Voir tableau p.103 de la documentation.
    TCCR2A |= (1 << WGM21); //Mode CTC timer 2

	// TCCR0B - Timer/Counter Control Register B.
	// Bit 7 - F0C2A : Force Output Compare Match A.
	// Bit 6 - F0C2B : Force Output Compare Match B.
	// Bit 5 - Reserved.
	// Bit 4 - Reserved.
	// Bit 3 - WGM22 : Waveforme Generation Mode.
	//				   Voir tableau p.103 de la documentation.
	// Bit 2 - CS22  : Clock Select.
	//				   Voir tableau p.104 de la documentation.
	// Bit 1 - CS21  : Clock Select.
	//				   Voir tableau p.104 de la documentation.
	// Bit 0 - CS20  : Clock Select.
	//				   Voir tableau p.104 de la documentation.
    TCCR2B |= (1 << CS21) | (1 << CS22); 	//prescaler de 32
	
    // TCNT0 - Timer/Counter Register.
	TCNT2 = 0;      	

	// OCR0A - Output Compare Register A.
    OCR2A = 250; //l'interruption output compare match se fera a chaque milliseconde
	
	// TIMSK0 - Timer/Counter Interrupt Mask Register.
	//			Bit 7:3 - Reserved.
	//			OCIE2A  - Timer/Counter Output Compare Match A Interrupt Enable.
    TIMSK2 |= (1 << OCIE2A);    	// Enable interrupt
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
void Minuterie::arreterMinuterie() const{
	TCCR2B &= ~(1 << CS21) & ~(1 << CS22);    		// Disable clock
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
bool Minuterie::obtenirMinuterieExpiree() const {
	if(minuterieExpiree)
		arreterMinuterie();
	return (bool)minuterieExpiree;
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
