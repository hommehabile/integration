#ifndef MINUTERIE_H
#define MINUTERIE_H

#include "constantes.h"

class Minuterie {
public:
	Minuterie();

	void partirMinuterie(uint16_t duree);
	void arreterMinuterie();

	bool getMinuterieExpiree();

	void setMinuterieExpiree(bool expiree);
private:
	bool minuterieExpiree_;
};

void delai_us(uint16_t nombreUs);
void delai_ms(uint16_t nombreMs);

#endif
