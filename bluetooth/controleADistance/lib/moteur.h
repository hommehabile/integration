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
    ~Moteur();

    void demarrerMoteur(uint8_t vitesse);
    void arreterMoteur();
    void setDirection(Direction dir);
    void setVitesse(uint8_t vitesse);
    
    Direction getDirection() const;
    Cote getCote() const;
    
private:
    Direction direction_;
    Cote cote_;
    Port port_;
    bool moteurEstDemarre_;

    void initialisationRegistres();
    void ajustementPWM(uint8_t vitesse);
};

#endif
