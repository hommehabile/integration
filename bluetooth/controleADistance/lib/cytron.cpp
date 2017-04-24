#include "cytron.h"

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
Cytron::Cytron() {
	DDRC &= 0x03;  //PORTC<7..2> en entrée
    PCICR |= (1<<PCIE2);
    PCMSK2 |= (1<<PCINT18) | (1<<PCINT19) | (1<<PCINT20) | (1<<PCINT21) | (1<<PCINT22);
}

/***************************************************************************
 * Fonction              : tableau
 * Description           : Cette fonction compare les parametres recus avec
 *                         le capteur du robot.  Voir synopsis pour de plus
 *                         amples informations.
 *                         L'entre 2 agit comme un "don't care".
 * Parametres d'entree   : 
 * 		- gauche2 (uint8_t) :
 *                         Valeur qui devra etre compare avec le capteur le plus a gauche.
 *      - gauche1 (uint8_t) :
 *                         Valeur qui devra etre compare avec le capteur se situant
 *                         entre celui completement a gauche et celui du centre.
 *      - centre (uint8_t) :
 *                         Valeur qui devra etre compare avec le capteur en plein centre.
 *      - droite1 (uint8_t) :
 *                         Valeur qui devra etre compare avec le capteur se situant
 *                         entre celui completement a droite et celui du centre.
 *      - droite2 (uint8_t) :
 *                         Valeur qui devra etre compare avec le capteur le plus a droite.
 * Parametres de sortie  :     
 * 		- estDetect (bool) :
 *                         Retournera vraie si les valeurs en entree coincide avec
 *                         les valeurs du capteur.
 ***************************************************************************/
bool Cytron::tableau(uint8_t gauche2, uint8_t gauche1, uint8_t centre, uint8_t droite1, uint8_t droite2) {
    bool estDetect = false;
    if (gauche2 == 2 || ((PINC & (1<<PC2))>>PC2) == gauche2){				
        if (gauche1 == 2 || ((PINC & (1<<PC3))>>PC3)  == gauche1){			
            if (centre == 2 || ((PINC & (1<<PC4))>>PC4)  == centre){		
                if (droite1 == 2 || ((PINC & (1<<PC5))>>PC5)  == droite1){	
                    if (droite2 == 2 || ((PINC & (1<<PC6))>>PC6)  == droite2){   
                        estDetect = true;
                    }
                }
            }
        }
    }
	return estDetect;
};


