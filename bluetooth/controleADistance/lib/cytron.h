#ifndef CYTRON_H
#define CYTRON_H

#include "constantes.h"

#define PIN_CYTRON PINC

enum Detecteur {GAUCHE2 = 0, GAUCHE1 = 1, CENTRE = 2, DROITE1 = 3, DROITE2 = 4};

class Cytron {
public:
    Cytron();
    bool tableau(uint8_t Gauche2, uint8_t Gauche1, uint8_t Centre, uint8_t Droite1, uint8_t Droite2);
};

#endif
