#ifndef PARCOURS_H
#define PARCOURS_H

#include "Robot.h"
#include "cytron.h"
#include "bouton.h"
#include "can.h"


#define VITESSE_LENTE		20
#define VITESSE_SEMI_LENTE	30
#define VITESSE_NORMALE		40
#define VITESSE_SEMI_RAPIDE	50
#define VITESSE_RAPIDE      60

#define TEMPS_ATTENTE_VIRAGE    900
#define TEMPS_90_DEGRES         1700
#define TEMPS_AVANT_STATIONNEMENT   3600

class Parcours {
public:
    Parcours();

    //methodes de parcours
    CouleurParcours assignerCouleurParcours(bool &changerEtat);
    void debutParcours();
    void stationnementTroisLignes(CouleurParcours couleur);
    void loiNormale(CouleurParcours couleur);
    void cinqQuarante();
    void touchdown();
    void pointille();
    void stationnementFin(CouleurParcours couleur);

private:
    Robot robot_;
    Cytron cytron_;
    Bouton boutonSelection_, boutonConfirmation_, boutonInterruption_;

    //methodes de deplacement
    void ligneDroite();
    void arreterMoteurs();                     
    void tournerDroiteSansDetection();
    void tournerGaucheSansDetection();
    void tournerDroiteSansDetection(uint16_t temps);
    void tournerGaucheSansDetection(uint16_t temps);
    void tournerDroiteAvecDetection();
    void tournerGaucheAvecDetection();
    void suivreLigneDroiteAvecTempsMs(uint16_t tempsMs);
};

#endif
