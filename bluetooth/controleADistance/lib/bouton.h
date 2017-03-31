#ifndef BOUTON_H
#define BOUTON_H

#include "constantes.h"

bool etatBoutton(Ports port, uint8_t pin);
bool antiRebond(uint8_t unPort, uint8_t laPin);

#endif
