#include "piezo.h"

/***************************************************************************
 * Fonction              : Piezo()
 * Description           : Constructeur par defaut de la classe Piezo.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
Piezo::Piezo() {
    initialisationRegistres();
}

/***************************************************************************
 * Fonction              : Piezo()
 * Description           : Constructeur par parametres de la classe Piezo.
 * Parametres d'entree   : 
 * 		- frequence (uint8_t) :
 *                         Frequence de la note desiree pour le piezo.  
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
Piezo::Piezo(uint8_t ratio) : ratio_(ratio) {
    initialisationRegistres();
    ajusterValeursComparaison();
}

void Piezo::initialisationRegistres() {
    DDRB |= 0xff;
    //Met le compteur a 0.
    TCNT0 = 0;

    //fast pwm avec OCR0A top
    TCCR0A |= _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
    TCCR0B |= _BV(WGM02) | _BV(CS02);     // division d'horloge par 256
}


/***************************************************************************
 * Fonction              : ~Piezo()
 * Description           : Destructeur de la classe Piezo.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
Piezo::~Piezo() {}

/***************************************************************************
 * Fonction              : debutSon
 * Description           : Cette fonction activera le piezo, dans le sens ou
 *                         apres l'appel de cette fonction, le piezo produira
 *                         un son.
 * Parametres d'entree   : 
 * 		  Aucun. 
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Piezo::debutSon() {
    PORTB = 0x00;
    
    //enable le compteur
    TCCR0B |= _BV(CS02);
}

/***************************************************************************
 * Fonction              : arretSon
 * Description           : Cette fonction desactivera le piezo, dans le sens 
 *                         ou apres l'appel de cette fonction, le piezo ne 
 *                         produira plus de son.
 * Parametres d'entree   : 
 * 		  Aucun. 
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Piezo::arretSon() {
    //disable le compteur
    TCCR0B &= ~(0x00 | _BV(CS02));
}

/***************************************************************************
 * Fonction              : setFrequence
 * Description           : Cette fonction recoit en parametre une note qui
 *                         doit etre jouee par le piezo.  La fonction determinera
 *                         quelle frequence est associee a cette note et
 *                         la donnera a l'attribut responsable de generer le son.
 * Parametres d'entree   : 
 * 		- note (uint8_t) : Cette note est une valeur se situant entre 45 et 81.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Piezo::setFrequence(uint8_t note){
    note -= 45;
    if (note >= 0 && note <=36) {
        double top = 0;
        double tableauFrequence[] = { 110.00, 116.54, 123.47, 130.81, 138.59,       //45-49
                                    146.83, 155.56, 164.81, 174.61, 184.99,      //50-54
                                    195.99, 207.65, 220.00, 233.08, 246.94,      //55-59
                                    261.63, 277.18, 293.66, 311.12, 329.63,      //60-64
                                    349.23, 369.99, 391.99, 415.30, 440.00,      //65-69
                                    466.16, 493.88, 523.25, 554.37, 587.33,      //70-74
                                    622.25, 659.25, 698.45, 739.99, 783.99,      //75-79
                                    830.61, 880.00 };                            //80-81
        
        top = tableauFrequence[note];                   //frequence desire
        top = (1/top) * (8000000/256);                     //frequence en période (ms)/2
        ratio_ = top;
        ajusterValeursComparaison();
    }
}

void Piezo::ajusterValeursComparaison() {
    TCNT0 = 0;
    OCR0A = ratio_;
    OCR0B = ratio_/2;
}