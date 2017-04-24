#ifndef BOUTON_H
#define BOUTON_H

#include "constantes.h"

class Bouton {
public:
	Bouton();
	Bouton(volatile uint8_t *registre, uint8_t numeroPin, bool inverse = false);
	bool etatBouton();

private:
	volatile uint8_t *registre_;
	uint8_t numeroPin_;
	bool inverse_;
};

#endif
