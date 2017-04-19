#ifndef PARCOURS_H
#define PARCOURS_H

#include "Robot.h"
#include "cytron.h"

#define VITESSE_LENTE		70
#define VITESSE_NORMALE		100
#define VITESSE_RAPIDE		130



extern volatile bool tableauDetecteurs[5];

class Parcours {
public:
    Parcours();
    ~Parcours();

    //Fonction de déplacement de base.
    bool ligneDroite();
    
    void tournerDroiteSansDetection();
    void tournerGaucheSansDetection();
    
    void tournerDroiteAvecDetection();
    void tournerGaucheAvecDetection();
    
    //Fonction de déplacement plus avance.
    
    //Fonction Stationnement
    
    void stationnementTroisLigne(Couleur couleur);
    void stationnementFin(Couleur couleur);

    // Fonction pre-enregistree
    
    void loiNormale(Couleur couleur);
    void cinqQuarante(Couleur couleur);
    void touchdown();
    void pointille();

private:
    Robot robot_;
    Cytron cytron_;
};

#endif
