#include "piezo.h"

/***************************************************************************
 * Fonction              : Piezo()
 * Description           : Constructeur par defaut de la classe Piezo.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
Piezo::Piezo() : onde_(0) {}

/***************************************************************************
 * Fonction              : Piezo()
 * Description           : Constructeur par parametres de la classe Piezo.
 * Parametres d'entree   : 
 * 		- frequence (uint8_t) :
 *                         Frequence de la note desiree pour le piezo.  
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
Piezo::Piezo(uint8_t frequence) : onde_(frequence) {}

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
    onde_.debutPwm();
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
    onde_.arretPwm();
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
    double tableauFrequence[] = { 110.00, 116.54, 123.47, 130.81, 138.59,       //45-49
                                   146.83, 155.56, 164.81, 174.61, 184.99,      //50-54
                                   195.99, 207.65, 220.00, 233.08, 246.94,      //55-59
                                   261.63, 277.18, 293.66, 311.12, 329.63,      //60-64
                                   349.23, 369.99, 391.99, 415.30, 440.00,      //65-69
                                   466.16, 493.88, 523.25, 554.37, 587.33,      //70-74
                                   622.25, 659.25, 698.45, 739.99, 783.99,      //75-79
                                   830.61, 880.00 };                            //80-81
        
    double top = 0;
    top = tableauFrequence[note-45];                   //frequence desire
    
    top = (1/top) * (8000000/256);                     //frequence en période (ms)/2
        
    note = note-45;
    if (note >= 0 && note <=36)
        onde_.modifierRatio((uint8_t)top);
}
