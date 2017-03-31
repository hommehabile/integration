#include "moteur.h"

/***************************************************************************
 * Fonction              : Moteur()
 * Description           : Constructeur par defaut. Initialisation port D.
 *                         On specifie les pin que l'on veut en sortie.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
Moteur::Moteur() {}

/***************************************************************************
 * Fonction              : Moteur(Cote unCote)
 * Description           : Constructeur par parametres. Initialise le PWM   
 *                         selon le cote specifie en parametre pour le moteur.
 * Parametres d'entree   : 
 * 		- cote (Cote)    : Specifie le cote du moteur que l'on desire creer.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
Moteur::Moteur(Cote unCote) {
    cote_ = unCote;
    switch(cote_) {
        case DROITE: 
            pwm_ = PWM(A1);
            PORTD |= (1 << PD7);
            break;
        case GAUCHE: 
            pwm_ = PWM(B1);
            PORTD |= (1 << PD6);
            break;
    }
}

/***************************************************************************
 * Fonction              : ~Moteur()
 * Description           : Destructeur de la classe Moteur.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
Moteur::~Moteur() {}

/***************************************************************************
 * Fonction              : setDirection
 * Description           : Modificateur pour l'attribut direction_.
 * Parametres d'entree   : 
 * 		- uneDirection (Direction) :
 *                         Nouvelle direction que l'on veut donner au moteur.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Moteur::setDirection(Direction uneDirection) {
    direction_ = uneDirection;

    if(direction_ == ARRIERE) {
        if(cote_ == GAUCHE)
            PORTD |= (1 << PD6);
        else
            PORTD |= (1 << PD7);
    } else {
        if(cote_ == GAUCHE)
            PORTD &= ~(1 << PD6);
        else
            PORTD &= ~(1 << PD7);
    }
}

/***************************************************************************
 * Fonction              : getDirection
 * Description           : Accesseur pour l'attribut direction_.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		- direction_ (Direction)   : 
 *                         On retourne la valeur que contient l'attribut 
 *                         direction_.
 ***************************************************************************/
Direction Moteur::getDirection() const {
    return direction_;
}

/***************************************************************************
 * Fonction              : getCote
 * Description           : Accesseur pour l'attribut cote_.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		- cote_ (Cote)   : On retourne la valeur que contient l'attribut 
 *                         cote_.
 ***************************************************************************/
Cote Moteur::getCote() const {
    return cote_;
}

/***************************************************************************
 * Fonction              : demarrer
 * Description           : Cette fonction ajuste le pwm du moteur et le fait
 *                         ensuite demarrer.
 * Parametres d'entree   : 
 * 		- valeurMax (uint8_t) :
 *                         Cette valeur specifie la valeur maximale auquel le
 *                         moteur devra fonctionner.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Moteur::demarrerMoteur(uint8_t valeurMax) {
    pwm_.demarrerPwm();
    pwm_.ajustementPWM(valeurMax);
}

/***************************************************************************
 * Fonction              : arreter
 * Description           : Cette fonction arrete le pwm, ce qui arretera le
 *                         moteur.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Moteur::arreterMoteur() {
    pwm_.arreterPwm();
}

