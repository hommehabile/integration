#ifndef GESTIONNAIREDEL_H
#define GESTIONNAIREDEL_H

#include "lib/del.h"

class GestionnaireDel 
{
	public:
	
		GestionnaireDel();						//	Constructeur par default
		~GestionnaireDel();						//	Destructeur
		
		void allumerDel(uint8_t numeroDels);	//	Allumer une ou plusieurs Dels (cas general) 
		void fermerDel(uint8_t numeroDels);		//	Fermer une  ou plusieurs Dels
		
		// void allumerDelEnRouge(uint8_t numeroDel);
		// void allumerDelEnVert(uint8_t numeroDel);
		// void allumerDelEnAmbre(uint8_t numeroDel);
		
	private:
	
		Del listeDels_[2];						//	Liste de Dels (une Del utilise presentement)
		uint8_t tailleListeDels_;				//	La taille de la liste de Dels
		uint8_t capaciteListeDels_;				//	La capacite maximal de la liste de Dels
		
		
};

#endif
