#include "GestionnaireInstructions.h"

GestionnaireInstructions::GestionnaireInstructions() {}

void GestionnaireInstructions::executer() {
	Instruction uneInstruction;
	while(1){
        uneInstruction.setOpcode(blue_.receive());
        blue_.receive();
        blue_.receive();//flushing
        uneInstruction.setOperande(blue_.receive());
        blue_.receive();
        blue_.receive();//flushing
        switch(uneInstruction.getOpcode()){
                case att: 
                    delai_ms(uneInstruction.getOperande() * 25);       //25 fois la valeur de l'operande
                    break;
                case dal:
                    PORTB = 0x01;
                    robot_.allumerDel(uneInstruction.getOperande());
                    break;
                case det:
                    robot_.fermerDel(uneInstruction.getOperande()); 
                    break;
                case sgo: 
                    
                    break;
                case sar: 
                    
                    break;
                case mar:
                case 0x61:
                    robot_.arreter();
                    break;
                case mav:
                    robot_.avancer(uneInstruction.getOperande(), uneInstruction.getOperande()); 
                    break;
                case mre: 
                    robot_.reculer(uneInstruction.getOperande(), uneInstruction.getOperande());
                    break;
                case trd: 
                    robot_.tournerDroite();
                    break;
                case trg: 
                    robot_.tournerGauche();
                    break;
                case dbc:
                    //not implemented yet
                    break;
                case fbc:
                	//not implemented yet
                    break;
                case fin:
                    robot_.arreter();
                    break;
        }
	}
}
