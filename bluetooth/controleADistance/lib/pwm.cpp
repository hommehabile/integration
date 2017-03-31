#include "pwm.h"

/***************************************************************************
 * Fonction              : PWM()
 * Description           : Constructeur par defaut. On y appelle la fonction
 *                         initialisation().
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
PWM::PWM() { 
    initialisation();
}

/***************************************************************************
 * Fonction              : PWM(Port port)
 * Description           : Constructeur par parametres. On y appelle la
 *                         fonction initialisation() et on initialise notre
 *                         attribut port_.
 * Parametres d'entree   : 
 * 		- port (Port)    : Specifie le port dans lequel nous aurons le PWM.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
PWM::PWM(Port port) {
    initialisation();
    port_ = port;
}

/***************************************************************************
 * Fonction              : initialisation
 * Description           : Initialise tous les registres pour permettre au 
 *                         microprocesseur de generer le PWM voulu.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void PWM::initialisation() {
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
 * Fonction              : ajustementPWM
 * Description           : Fixe la valeur des registres OCR1A ou OCR1B selon
 *                         le port du moteur.
 * Parametres d'entree   : 
 * 		- valMax (uint8_t) :
                           Valeur maximal de TCNT1 pour Compare Match.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void PWM::ajustementPWM(uint8_t valMax) {                                
    switch(port_) {
        case A1 :
            OCR1A = valMax;
            break;
        case B1 :
            OCR1B = valMax;
            break;
    }
}

/***************************************************************************
 * Fonction              : demarrerPWM
 * Description           : Cette fonction active le Compare Match selon le 
 *                         port du moteur.  Cela permettra la generation
 *                         d'un signal PWM.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void PWM::demarrerPwm() {
    if(port_ == A1)
        TCCR1A |= (1 << COM1A1);    //Activation du Compare Match (Clear OCR1A on Compare Match).
    else if(port_ == B1)
        TCCR1A |= (1 << COM1B1);    //Activation du Compare Match (Clear OCR1B on Compare Match).
}

/***************************************************************************
 * Fonction              : arreterPWM
 * Description           : Cette fonction desactive le Compare Match selon le 
 *                         port du moteur.  Cela cessera la generation
 *                         d'un signal PWM.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void PWM::arreterPwm() {
    if(port_ == A1)
        TCCR1A &= ~(1 << COM1A1);   //Desactivation du Compare Match pour le canal A.
    else if(port_ == B1)
        TCCR1A &= ~(1 << COM1B1);   //Desactivation du Compare Match pour le canal B.
}