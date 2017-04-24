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
 * Fonction              : debutSon
 * Description           : Cette fonction active le piezo, dans le sens ou
 *                         apres l'appel de cette fonction, le piezo produira
 *                         un son.
 * Parametres d'entree   : 
 * 		  Aucun. 
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Piezo::debutSon() const {
    TCCR0B |= _BV(CS02);                //Activation du compteur.
}

/***************************************************************************
 * Fonction              : arretSon
 * Description           : Cette fonction desactive le piezo, dans le sens 
 *                         ou apres l'appel de cette fonction, le piezo ne 
 *                         produira plus de son.
 * Parametres d'entree   : 
 * 		  Aucun. 
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Piezo::arretSon() const {
    PORTB &= 0xcf;               //Mise à 0 de toutes les PINS du port B.
    TCCR0B &= ~(_BV(CS02));      //Desactivation du compteur.
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
void Piezo::modifierFrequence(uint8_t note){
    note -= 45;                                 //On veut obtenir le numero relatif de la note.
    if (note >= 0 && note <=36) {
        ratio_ = 0;
        double tableauFrequence[] = { 110.00, 116.54, 123.47, 130.81, 138.59,    //45-49
                                    146.83, 155.56, 164.81, 174.61, 184.99,      //50-54
                                    195.99, 207.65, 220.00, 233.08, 246.94,      //55-59
                                    261.63, 277.18, 293.66, 311.12, 329.63,      //60-64
                                    349.23, 369.99, 391.99, 415.30, 440.00,      //65-69
                                    466.16, 493.88, 523.25, 554.37, 587.33,      //70-74
                                    622.25, 659.25, 698.45, 739.99, 783.99,      //75-79
                                    830.61, 880.00 };                            //80-81

        ratio_ = (uint8_t)((1/tableauFrequence[note]) * (8000000/256));          //Frequence en période (ms)/2.

        TCNT0 = 0;
        OCR0A = ratio_;
        OCR0B = ratio_/2;
    }
}

/***************************************************************************
 * Fonction              : initialisationRegistres
 * Description           : Cette fonction initialise les bons registres
 *                         pour permettre l'utlisation du compteur.  On
 *                         utilise ici le port B.
 * Parametres d'entree   : 
 * 		  Aucun.  
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Piezo::initialisationRegistres() const {
    DDRB |= 0x30;
    
    TCNT0 = 0;                              //Met le compteur a 0.

    //FAST PWM avec OCR0A top.
    TCCR0A |= _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
    TCCR0B |= _BV(WGM02);       //Division d'horloge par 256.
}