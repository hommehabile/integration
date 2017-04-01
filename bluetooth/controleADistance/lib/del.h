#ifndef DEL_H
#define DEL_H

#include "constantes.h"

class Del 
{
public:
	Del();				// Constructeur par default
		
	Del(volatile uint8_t *port, uint8_t numeroPortUn, uint8_t numeroPortDeux); // Constructeur par parametre
		
	~Del();				// Destructeur
		
	// Methodes pour afficher une couleur
	void afficherVert();
	void afficherRouge();
	void afficherAmbre();
		
	// Methode pour afficher aucune couleur
	void eteindre();
		
	// Methode d'acces
	uint8_t obtenirEtat();
	volatile uint8_t* obtenirLettrePort();
	uint8_t obtenirNumeroPortUn();
	uint8_t obtenirNumeroPortDeux();
		
private:
	volatile uint8_t *port_;
	uint8_t etat_;
	uint8_t numeroPortUn_;
	uint8_t numeroPortDeux_;
};

#endif
