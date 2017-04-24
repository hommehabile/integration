#ifndef MOTEUR_H
#define MOTEUR_H

#include "constantes.h"

enum Direction {AVANT, ARRIERE, ARRET};
enum Cote {DROITE, GAUCHE};
enum Port {A1, B1};

class Moteur {
public:
    Moteur();
    Moteur(Cote cote);

    void demarrerMoteur(const uint8_t pourcentage) const;
    void arreterMoteur();
    
    void modifierDirection(const Direction dir);
    void modifierVitesse(const uint8_t pourcentage) const;
    
    Direction obtenirDirection() const;
    Cote obtenirCote() const;
private:
    Direction direction_;
    Cote cote_;
    Port port_;
    bool moteurEstDemarre_;

    void initialisationRegistres() const ;
};

#endif
