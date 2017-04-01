#ifndef CYTRON_H
#define CYTRON_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define PIN_CYTRON PINC

enum Detecteur {GAUCHE2 = 0, GAUCHE1 = 1, CENTRE = 2, DROITE1 = 3, DROITE2 = 4};

class Cytron {
public:
    Cytron();
    ~Cytron();
    
    void initialisation();
    void debutDetection();
    void arretDetection();
    
};

#endif