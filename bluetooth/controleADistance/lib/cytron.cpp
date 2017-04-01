#include "cytron.h"

/*
 *                      SYNOPSIS
 * Le cytron est très simple. Lorsqu'il capte une ligne foncée, la sortie est 1. 
 * Il possède 5 capteurs. Chacun est indépendant. Si un capteur voit quelque une ligne 
 * foncé, la sortie au port sera 1. On le capte au port 1.
 */

volatile bool tableauDetecteurs[5] = {false, false, false, false, false};

ISR(PCINT2_vect) {
	for(uint8_t i=0; i<5; i++) {
		tableauDetecteurs[i] = (PINC & (1<<(i+2))) >> (i+2); //update le tableau des detecteurs
	}
}

/***************************************************************************
 * Fonction              : Cytron()
 * Description           : Constructeur par defaut de la classe Cytron.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
Cytron::Cytron() {
	initialisation();
}

Cytron::~Cytron() {}

/***************************************************************************
 * Fonction              : Initialisation()
 * Description           : Initialisation de la classe Cytron.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Cytron::initialisation() {
	DDRC &= 0x03;  //PORTC<7..2> en entrée
	PCIFR |= (1<<PCIF2);
	PCMSK2 |= (1<<PCINT18) | (1<<PCINT19) | (1<<PCINT20) | (1<<PCINT21) | (1<<PCINT22);
}

void Cytron::debutDetection() {
	PCIFR |= (1<<PCIF2); //enable interrupts
}

void Cytron::arretDetection() {
	PCIFR &= ~(1<<PCIF2); //disable interrupts
}

