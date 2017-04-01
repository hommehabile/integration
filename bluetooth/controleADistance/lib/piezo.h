#ifndef PIEZO_H
#define PIEZO_H

#include "constantes.h"

class Piezo {
public:
    Piezo();
    Piezo(uint8_t ratio);
    ~Piezo();
    
    void debutSon();
    void arretSon();
    
    void setFrequence(uint8_t note);
private:
    uint8_t ratio_;
    void initialisationRegistres();
    void ajusterValeursComparaison();
};

#endif