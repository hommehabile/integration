#ifndef GESTIONNAIREINSTRUCTIONS_H
#define GESTIONNAIREINSTRUCTIONS_H

#include "lib/bouton.h"
#include "lib/memoire_24.h"
#include "lib/can.h"
#include "lib/uart.h"
#include "lib/piezo.h"
#include "bluetooth.h"

#include "GestionnaireDel.h"
#include "GestionnaireMoteurs.h"
#include "Instruction.h"

#define dbt 0x01 		//debut
#define att 0x02 		//attendre
#define dal 0x44		//allumer Del
#define det 0x45 		//eteindre Del
#define sgo 0x48 		//jouer une sonnerie
#define sar 0x09 		//arreter de jouer une sonnerie
#define mar 0x60  		//arreter les moteurs            ***PEUT PRENDRE VALEUR 0x60 OU 0x61****
#define mav 0x62 		//avancer
#define mre 0x63 		//reculer
#define trd 0x64 		//tourner a droite
#define trg 0x65 		//tourner a gauche
#define dbc 0xC0 		//debut de boucle
#define fbc 0xC1 		//fin de boucle
#define fin 0xFF 		//fin

class GestionnaireInstructions {
public:
	GestionnaireInstructions();
	void executer();

private:
	Memoire24CXXX mem_;
    Minuterie minut_;
	GestionnaireDel del_;
    Piezo piezo_;
    GestionnaireMoteurs moteur_;
    Bluetooth blue_;
    bool debut_, finProg_;
    uint16_t tailleProg_;
};

#endif