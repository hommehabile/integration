#include "GestionnaireDel.h"

// Constructeur par defaut permettant de creer le tableau de Dels
GestionnaireDel::GestionnaireDel(){
	
	capaciteListeDels_ = 8;				// Maximum de Dels que nous pouvons utiliser
	tailleListeDels_ = 2;					// Taille de la liste de Dels; nous utilisons une Del presentement
	listeDels_[0] = Del(B, 0, 1);		// La Del que nous utilisons est brancher aux port A aux numeros 0 et 1
	listeDels_[1] = Del(B, 1, 0);
	// listeDels_[2] = Del(A, 4, 5);
	// listeDels_[3] = Del(A, 6, 7);
	// listeDels_[4] = Del(B, 0, 1);
	// listeDels_[5] = Del(C, 0, 1);
	// listeDels_[6] = Del(D, 0, 1);
	// listeDels_[7] = Del(D, 2, 3);
}

// Destructeur
GestionnaireDel::~GestionnaireDel()	{}

// Methode pour allumer une ou plusieurs Dels.
// Regarde chacune des Dels dans la liste de Dels ( donc de 0 a la taille de la liste de Dels).
// Effectue un ET binaire entre numeroDels et le valeur voulue.
// Effectue un shift pour pouvoir conclure si elle est bien 1.
// Si c'est le cas, elle affichera la couleur verte.
void GestionnaireDel::allumerDel(uint8_t numeroDels){
	
	for (uint8_t i = 0; i < tailleListeDels_; i++){			
		if ((((numeroDels & (1 << i))) >> i) == 1){			
			listeDels_[i].afficherVert();
		}
	}
}

// Methode pour fermer une ou plusieurs Dels.
// Regarde chacune des Dels dans la liste de Dels ( donc de 0 a la taille de la liste de Dels).
// Effectue un ET binaire entre numeroDels et le valeur voulue.
// Effectue un shift pour pouvoir conclure si elle est bien 1.
// Si c'est le cas, elle n'affichera aucune couleur.
void GestionnaireDel::fermerDel(uint8_t numeroDels){
	
	for (uint8_t i = 0; i < tailleListeDels_; i++){	
		if ((((numeroDels & (1 << i))) >> i) == 1){
			listeDels_[i].eteindre();
		}
	}
}

// Exemple
// if (((numeroDels & (1 << i))) >> i) == 1)
// numeroDels = 1010 1010 , i = 3
// (1 << (3)) <=> 0000 0001 << 3 <=> 0000 1000
// (numeroDels & (1 << i)) <=>
//	1010 1010
//	0000 1000 &(ET)
//	0000 1000 
//	0000 1000 >> (3) <=> 0000 0001
//	0000 0001 == 1?		OUI!

