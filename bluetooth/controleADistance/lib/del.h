#ifndef DEL_H
#define DEL_H

#include "constantes.h"

class Del 
{
public:
	Del();				// Constructeur par default
		
	Del(Ports lettrePort, uint8_t numeroPortUn, uint8_t numeroPortDeux); // Constructeur par parametre
		
	~Del();				// Destructeur
		
	// Methodes pour afficher une couleur
	void afficherVert();
	void afficherRouge();
	void afficherAmbre();
		
	// Methode pour afficher aucune couleur
	void eteindre();
		
	// Methode d'acces
	uint8_t obtenirEtat();
	Ports obtenirLettrePort();
	uint8_t obtenirNumeroPortUn();
	uint8_t obtenirNumeroPortDeux();
		
private:
	Ports lettrePort_;
	uint8_t etat_;
	uint8_t numeroPortUn_;
	uint8_t numeroPortDeux_;
};

#endif
