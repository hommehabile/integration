#ifndef GESTIONNAIREMOTEURS_H
#define GESTIONNAIREMOTEURS_H

#include "lib/moteur.h"
#include "lib/minuterie.h"

class GestionnaireMoteurs {
public:
    GestionnaireMoteurs();
    ~GestionnaireMoteurs();
    
    void avancer(uint8_t pourcentage);
    void reculer(uint8_t pourcentage);
    void tournerDroite();
    void tournerGauche();
    void arreter();

private:
    Moteur moteurDroite_;
    Moteur moteurGauche_;
};

#endif
