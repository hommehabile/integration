
#include "pwmSon.h"

/***************************************************************************
 * Fonction              : PwmSon()
 * Description           : Constructeur par defaut de la classe PwmSon.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
PwmSon::PwmSon(){
    init();
}

/***************************************************************************
 * Fonction              : PwmSon()
 * Description           : Constructeur par parametre de la classe PwmSon.
 * Parametres d'entree   : 
 * 		- ratio (uint8_t): Le ratio sera envoye a la fonction modifirRatio.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
PwmSon::PwmSon(uint8_t ratio){
    init();
    modifierRatio(ratio);
}

/***************************************************************************
 * Fonction              : init
 * Description           : Cette fonction initialise les registres pour
 *                         generer le signal en sortie voulue.  La fonction
 *                         place aussi le port B en sortie.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void PwmSon::init(){
    DDRB |= 0xFF;

    //Reinitialise le compteur
    TCNT0 = 0;

    //fast pwm avec OCR0A top
    TCCR0A |= _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
    TCCR0B |= _BV(WGM02) | _BV(CS02);     // division d'horloge par 256
}

/***************************************************************************
 * Fonction              : ~PwmSon()
 * Description           : Destructeur de la classe PwmSon.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
PwmSon::~PwmSon() {}

/***************************************************************************
 * Fonction              : modifierRatio
 * Description           : Cette fonction met a 0 le compteur (TCNT0) et
 *                         place le ratio recu en parametre dans les registres
 *                         OCR0A et OCR0B.  Rappelons que OCR0x sont les
 *                         "top", utile pour le Compare Match.
 * Parametres d'entree   : 
 * 		- ratio (uint8_t): Ce parametre sera place dans les registres OCR0x.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void PwmSon::modifierRatio(uint8_t ratio){
    TCNT0 = 0;
    OCR0A = ratio;
    OCR0B = ratio/2;
}

/***************************************************************************
 * Fonction              : debutPwm
 * Description           : Cette fonction permet de demarrer la generation 
 *                         du signal PWM pour le son.  Elle met aussi toutes
 *                         les broches du port B a 0.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void PwmSon::debutPwm(){
    PORTB = 0x00;
    
    //Active le compteur
    TCCR0B |= _BV(CS02);
}

/***************************************************************************
 * Fonction              : arretPwm
 * Description           : Cette fonction permet d'arreter la generation 
 *                         du signal PWM pour le son.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void PwmSon::arretPwm(){
    //Desactive le compteur
    TCCR0B &= ~(0x00 | _BV(CS02));
}


