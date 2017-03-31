#ifndef MOTEUR_H
#define MOTEUR_H

#include "pwm.h"

enum Direction {AVANT, ARRIERE};
enum Cote {DROITE, GAUCHE};

class Moteur {
public:
    Moteur();
    Moteur(Cote cote);
    ~Moteur();

    void demarrerMoteur(uint8_t pourcentage);
    void arreterMoteur();
    void setDirection(Direction dir);
    
    Direction getDirection() const;
    Cote getCote() const;
private:
    PWM pwm_;
    Direction direction_;
    Cote cote_;
    void initialisationPort();
};

#endif
