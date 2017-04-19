#include "Parcours.h"


Parcours::Parcours(){
	robot_ = Robot();
	cytron_ = Cytron();
}

Parcours::~Parcours() {}

//Fonction de déplacement de base.
bool Parcours::ligneDroite() {
	if(!tableauDetecteurs[GAUCHE2] && !tableauDetecteurs[DROITE2]) {
        robot_.avancer(VITESSE_NORMALE, VITESSE_NORMALE);
    }
    else if(tableauDetecteurs[GAUCHE2] && !tableauDetecteurs[DROITE2]) {
        robot_.avancer(VITESSE_NORMALE, VITESSE_RAPIDE);
    }
    else if(!tableauDetecteurs[GAUCHE2] && tableauDetecteurs[DROITE2]) {
        robot_.avancer(VITESSE_RAPIDE, VITESSE_NORMALE);
    }
    else if(tableauDetecteurs[CENTRE] && tableauDetecteurs[GAUCHE2] && tableauDetecteurs[DROITE2]) {
        robot_.avancer(VITESSE_NORMALE, VITESSE_NORMALE);
		return true;
	}
	return false;
}

void Parcours::tournerDroiteSansDetection(){
	robot_.tournerDroite();						//Le robot tournera de 90 degré vers la droite sans le détecteur.
	delai_ms(1850);             				//Permet environ 90 degres.
    robot_.arreter();
}

void Parcours::tournerGaucheSansDetection(){
	robot_.tournerGauche();
	delai_ms(1850);             				//Permet environ 90 degres.
    robot_.arreter();
}
    
void Parcours::tournerDroiteAvecDetection(){
	robot_.tournerDroite();					//Le robot tounera vers la droite.
	cytron_.debutDetection();				//On active la detection du cytron.
	while(!tableauDetecteurs[4]) {}			//Tant que le capteur sera false, le robot tournera.
	robot_.arreter();						//Le robot s'immobilisera.
	cytron_.arretDetection();				//On desactive la detection du cytron.
}
   
void Parcours::tournerGaucheAvecDetection(){
	robot_.tournerDroite();					//Le robot tounera vers la gauche.
	cytron_.debutDetection();				//On active la detection du cytron.
	while(!tableauDetecteurs[0]) {}			//Tant que le capteur sera false, le robot tournera.
	robot_.arreter();						//Le robot s'immobilisera.
	cytron_.arretDetection();				//On desactive la detection du cytron.
}

void Parcours::stationnementTroisLigne(Couleur couleur){
	
}
    
void Parcours::stationnementFin(Couleur couleur){
	
}
   
void Parcours::loiNormale(Couleur couleur){
	
}

void Parcours::cinqQuarante(Couleur couleur){
	
}
    
void Parcours::touchdown(){

}
    
void Parcours::pointille(){
	
}
