#ifndef PIEZO_H
#define PIEZO_H

#include "constantes.h"

class Piezo {
public:
    Piezo();
    
    void debutSon() const;
    void arretSon() const;
    
    void modifierFrequence(uint8_t note);
private:
    uint8_t ratio_;
    void initialisationRegistres() const;
};

#endif