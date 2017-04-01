#include "Robot.h"

Robot::Robot() {
    DDRA |= 0xFF;                   //****** A CONFIRMER ********
    DDRD |= 0xFF;                   //Initialisation du port D en sortie;
    PORTD = 0x00;                   //Toutes les broches sont initialisées à 0.
    moteurGauche_ = Moteur(GAUCHE); //Creation du moteur gauche.
    moteurDroite_ = Moteur(DROITE); //Creation du moteur droite.


    capaciteListeDels_ = 8;
    tailleListeDels_ = 2;
    listeDels_[0] = Del(&PORTB, 1, 0);
    listeDels_[1] = Del(&PORTB, 0, 1);
    DDRB = 0xff;
    PORTB = 0;
}

Robot::~Robot() {}

void Robot::avancer(uint8_t vitesseGauche, uint8_t vitesseDroite) {
    switch(moteurDroite_.getDirection()) {
        case ARRET : 
            moteurDroite_.setDirection(AVANT);
            moteurDroite_.demarrerMoteur(vitesseDroite);
            break;
        case ARRIERE :
            moteurDroite_.setDirection(AVANT);
            moteurDroite_.setVitesse(vitesseDroite);
            break;
        case AVANT :
            moteurDroite_.setVitesse(vitesseDroite);
            break;
    }

    switch(moteurGauche_.getDirection()) {
        case ARRET :
            moteurGauche_.setDirection(AVANT);
            moteurGauche_.demarrerMoteur(vitesseGauche);
            break;
        case ARRIERE :
            moteurGauche_.setDirection(AVANT);
            moteurGauche_.setVitesse(vitesseGauche);
            break;
        case AVANT :
            moteurGauche_.setVitesse(vitesseGauche);
            break;
    }
}

void Robot::reculer(uint8_t vitesseGauche, uint8_t vitesseDroite) {
    switch(moteurDroite_.getDirection()) {
        case ARRET : 
            moteurDroite_.setDirection(AVANT);
            moteurDroite_.demarrerMoteur(vitesseDroite);
            break;
        case ARRIERE :
            moteurDroite_.setDirection(AVANT);
            moteurDroite_.setVitesse(vitesseDroite);
            break;
        case AVANT :
            moteurDroite_.setVitesse(vitesseDroite);
            break;
    }

    switch(moteurGauche_.getDirection()) {
        case ARRET :
            moteurGauche_.setDirection(AVANT);
            moteurGauche_.demarrerMoteur(vitesseGauche);
            break;
        case ARRIERE :
            moteurGauche_.setDirection(AVANT);
            moteurGauche_.setVitesse(vitesseGauche);
            break;
        case AVANT :
            moteurGauche_.setVitesse(vitesseGauche);
            break;
    }
}

void Robot::arreter() {
    moteurDroite_.arreterMoteur();
    moteurGauche_.arreterMoteur();
}

void Robot::tournerDroite() {
    moteurDroite_.setDirection(ARRIERE);
    moteurGauche_.setDirection(AVANT);

    uint8_t uneVitesse = 150;
    
    moteurDroite_.demarrerMoteur(uneVitesse);
    moteurGauche_.demarrerMoteur(uneVitesse);
    
}

void Robot::tournerGauche() {
    moteurDroite_.setDirection(AVANT);
    moteurGauche_.setDirection(ARRIERE);

    uint8_t uneVitesse = 150;
    
    moteurDroite_.demarrerMoteur(uneVitesse);
    moteurGauche_.demarrerMoteur(uneVitesse);
}

void Robot::allumerDel(uint8_t numeroDels) {
    for (uint8_t i = 0; i < tailleListeDels_; i++){			
		if ((((numeroDels & (1 << i))) >> i) == 1){			
			listeDels_[i].afficherVert();
		}
	}
}

void Robot::fermerDel(uint8_t numeroDels){
    for (uint8_t i = 0; i < tailleListeDels_; i++){	
		if ((((numeroDels & (1 << i))) >> i) == 1){
			listeDels_[i].eteindre();
		}
	}
}