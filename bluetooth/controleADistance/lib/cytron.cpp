#include "cytron.cpp"
#include "can.h"

/*
 *                      SYNOPSIS
 * Le cytron est très simple. Lorsqu'il capte une ligne foncée, la sortie est 1. 
 * Il possède 5 capteurs. Chacun est indépendant. Si un capteur voit quelque une ligne 
 * foncé, la sortie au port sera 1. On le capte au port 1.
 */

/***************************************************************************
 * Fonction              : Cytron()
 * Description           : Constructeur par defaut de la classe Cytron.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
Cytron::Cytron() : {
void initialisation();

}

/***************************************************************************
 * Fonction              : Initialisation()
 * Description           : Initialisation de la classe Cytron.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
Cytron::Initialisation(){

DDRA = 0x00;  //PORTA en entrée

}
/***************************************************************************
 * Fonction              : GetPin()
 * Description           : Obtenir la bonne Pin d'entree.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/

int Cytron::getPin(int DECT)
{
	switch (DECT){

		case DECT1:
			return 0x02;
			break;
		case DECT2:
			return 0x03;
			break;
		case DECT3:
			return 0x04;
			break;
		case DECT4:
			return 0x05;
			break;
		case DECT5:
			return 0x06;
			break;
	}
}

/***************************************************************************
 * Fonction              : Detection()
 * Description           : Bool pour savoir si il y a detection.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
bool Cytron::Detection(int DECT){

    
    int position = getPin();                       
    uint8_t valeurPort;
    Can convertisseur         
   
        valeurPort = (convertisseur.lecture(position) && 0x01);  
        if(valeurPort ==1) {
            return true;
        } 
	else {
            return false;
        }
    
}
