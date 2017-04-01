#ifndef GESTIONNAIREINSTRUCTIONS_H
#define GESTIONNAIREINSTRUCTIONS_H

#include "Robot.h"
#include "bluetooth.h"
#include "Instruction.h"

#define dbt 0x01 		//debut
#define att 0x02 		//attendre
#define dal 0x44		//allumer Del
#define det 0x45 		//eteindre Del
#define sgo 0x48 		//jouer une sonnerie
#define sch 0x49		//jouer une chanson
#define sar 0x09 		//arreter de jouer une sonnerie ou une chanson
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
	Robot robot_;
    Bluetooth blue_;
};

#endif