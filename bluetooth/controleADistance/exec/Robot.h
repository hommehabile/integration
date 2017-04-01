#ifndef ROBOT_H
#define ROBOT_H

#include "moteur.h"
#include "minuterie.h"
#include "del.h"

class Robot {
public:
    Robot();
    ~Robot();

    //Fonction du gestionnaire de moteurs.
    void avancer(uint8_t vitesseGauche, uint8_t vitesseDroite);
    void reculer(uint8_t vitesseGauche, uint8_t vitesseDroite);
    void arreter();
    void tournerDroite();
    void tournerGauche();

    //Fonction du gestionnaire de DEL.
    void allumerDel(uint8_t numeroDels);
    void fermerDel(uint8_t numeroDels);
private:
    Moteur moteurGauche_;
    Moteur moteurDroite_;

    Del listeDels_[2];
    uint8_t tailleListeDels_;
    uint8_t capaciteListeDels_;
};

#endif