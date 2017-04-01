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
            port_ = A1;
            PORTD |= (1 << PD7);
            break;
        case GAUCHE: 
            port_ = B1;
            PORTD |= (1 << PD6);
            break;
    }
    setDirection(ARRET);
    initialisationRegistres();
}

/***************************************************************************
 * Fonction              : initialisationRegistres
 * Description           : Initialise tous les registres pour permettre au 
 *                         microprocesseur de generer le PWM voulu.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Moteur::initialisationRegistres() {
    //TCNT1  - Timer/Counter 1.
    TCNT1 = 0;
    
    //TCCR1A - Timer/Counter 1 Control Register A.
    // Bit 7 - COM1A1 : Compare Output Mode for Channel A.
    //                  Voir tableaux p.128 et 129 de la documentation.
    // Bit 6 - COM1A0 : Compare Output Mode for Channel A.
    //                  Voir tableaux p.128 et 129 de la documentation.
    // Bit 5 - COM1B1 : Compare Output Mode for Channel B.
    //                  Voir tableaux p.128 et 129 de la documentation.
    // Bit 4 - COM1B0 : Compare Output Mode for Channel B.
    //                  Voir tableaux p.128 et 129 de la documentation.
    // Bit 3 - Reserved.
    // Bit 2 - Reserved.
    // Bit 1 - WGM11  : Waveform Generation Mode.
    //                  Voir tableau p.130 de la documentation.
    // Bit 0 - WGM10  : Waveform Generation Mode.
    //                  Voir tableau p.130 de la documentation.
    TCCR1A |= (1 << WGM10);                                     //Fast PWM 8-bits.
    
    //TCCR1B - Timer/Counter 1 Control Register B.
    // Bit 7 - ICNC1 : Input Capture Noise Canceler.
    //                 Quand le Noise Canceler est active, l'entree est filtre.
    // Bit 6 - ICES1 : Input Capture Edge Select.
    //                 This bit selects which edge is used to trigger a capture event.
    // Bit 5 - Reserved.
    // Bit 4 - WGM13 : Waveform Generation Mode.
    //                 Voir tableau p.130 de la documentation.
    // Bit 3 - WGM12 : Waveform Generation Mode.
    //                 Voir tableau p.130 de la documentation.
    // Bit 2 - CS12  : Clock Select.
    //                 Voir tableau p.131 de la documentation.
    // Bit 1 - CS11  : Clock Select.
    //                 Voir tableau p.131 de la documentation.
    // Bit 0 - CS10  : Clock Select.
    //                 Voir tableau p.131 de la documentation.
    TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10);

    //TCCR1C - Timer/Counter 1 Control Register C.
    // Bit 7 - FOC1A : Force Output Compare for Channel A.
    //                 Ce bit peut etre actif seulemet lorsque le
    //                 Waveform Generation Mode est un NON-PWM.
    // Bit 6 - FOC1B : Force Output Compare for Channel B.
    //                 Ce bit peut etre actif seulemet lorsque le
    //                 Waveform Generation Mode est un NON-PWM.
    // Bit 5 - Reserved.
    // Bit 4 - Reserved.
    // Bit 3 - Reserved.
    // Bit 2 - Reserved.
    // Bit 1 - Reserved.
    // Bit 0 - Reserved.
    TCCR1C |= 0;	                                            
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
 * 		- vitesse (uint8_t) :
 *                         Cette valeur specifie la valeur maximale auquel le
 *                         moteur devra fonctionner.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Moteur::demarrerMoteur(uint8_t vitesse) {
    if(port_ == A1)
        TCCR1A |= (1 << COM1A1);    //Activation du Compare Match (Clear OCR1A on Compare Match).
    else if(port_ == B1)
        TCCR1A |= (1 << COM1B1);    //Activation du Compare Match (Clear OCR1B on Compare Match).

    ajustementPWM(vitesse);
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
    if(port_ == A1)
        TCCR1A &= ~(1 << COM1A1);   //Desactivation du Compare Match pour le canal A.
    else if(port_ == B1)
        TCCR1A &= ~(1 << COM1B1);   //Desactivation du Compare Match pour le canal B.

    direction_ = ARRET;
}

void Moteur::setVitesse(uint8_t vitesse) {
    ajustementPWM(vitesse);
}


void Moteur::ajustementPWM(uint8_t vitesse) {
    switch(port_) {
        case A1 :
            OCR1A = vitesse;
            break;
        case B1 :
            OCR1B = vitesse;
            break;
    }
}
