#include "GestionnaireInstructions.h"

GestionnaireInstructions::GestionnaireInstructions() {
	debut_ = false;
}

void GestionnaireInstructions::executer() {
	Instruction uneInstruction;
    uint8_t temp;
	while(!finProg_){
        temp = blue_.receive();
        if(temp == 0x0a || temp == 0x0d)
            temp = dal;
		uneInstruction.setOpcode(temp);
        uneInstruction.setOperande(0);
        if(debut_) {
            switch(uneInstruction.getOpcode()){
                    case att: 
                        delai_ms(uneInstruction.getOperande() * 25);       //25 fois la valeur de l'operande
                        break;
                    case dal:
                        del_.allumerDel(uneInstruction.getOperande());
                        break;
                    case det:
                        del_.fermerDel(uneInstruction.getOperande()); 
                        break;
                    case sgo: 
                        piezo_.debutSon();
                        piezo_.setFrequence(uneInstruction.getOperande());
                        break;
                    case sar: 
                        piezo_.arretSon();
                        break;
                    case mar: 
                        moteur_.arreter();
                        break;
                    case 0x61:
                        moteur_.arreter();
                        break;
                    case mav:
                        moteur_.avancer(150); 
                        break;
                    case mre: 
                        moteur_.reculer(150);
                        break;
                    case trd: 
                        moteur_.tournerDroite();
                        break;
                    case trg: 
                        moteur_.tournerGauche();
                        break;
                    case dbc:
                        
                        break;
                    case fbc:
                    	
                        break;
                    case fin: 
                        finProg_ = true;
                        moteur_.arreter();
                        break;
            }
        }
        else if(uneInstruction.getOpcode() == dbt) {
            debut_ = true;
        }
	}
}
