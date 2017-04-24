#ifndef DEL_H
#define DEL_H

#include "constantes.h"

class Del {
public:
	Del();
	Del(volatile uint8_t *port, uint8_t numeroPortUn, uint8_t numeroPortDeux);
		
	// Methodes pour afficher une couleur
	void afficherVert();
	void afficherRouge();
	void afficherAmbre();
		
	// Methode pour afficher aucune couleur
	void eteindre();
		
	// Methode d'acces
	uint8_t obtenirEtat();
	volatile uint8_t* obtenirPort();
		
private:
	volatile uint8_t *port_;
	uint8_t etat_;
	uint8_t numeroPortUn_;
	uint8_t numeroPortDeux_;
};

#endif
