#ifndef ROBOT_H
#define ROBOT_H

#include "moteur.h"
#include "minuterie.h"
#include "del.h"
#include "piezo.h"

class Robot {
public:
    Robot();

    //Fonction du gestionnaire de moteurs.
    void avancer(const uint8_t pourcentageGauche, const uint8_t pourcentageDroite);
    void reculer(const uint8_t pourcentageGauche, const uint8_t pourcentageDroite);
    void arreter();
    void tournerDroite();
    void tournerDroite(const uint8_t pourcentageGauche, const uint8_t pourcentageDroite);
    void tournerGauche();
    void tournerGauche(const uint8_t pourcentageGauche, const uint8_t pourcentageDroite);

    //Fonction du gestionnaire de DEL.
    void allumerDel(const uint8_t numeroDels);
    void fermerDel(const uint8_t numeroDels);

    // Fonction du gestionnaire Piezo
    void debutSon() const;
    void arretSon() const;
    void modifierFrequence(uint8_t note);

private:
    Moteur moteurGauche_;
    Moteur moteurDroite_;
    Piezo piezo_;
    Del listeDels_[2];
    uint8_t tailleListeDels_;
    uint8_t capaciteListeDels_;
};

#endif