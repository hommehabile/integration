#include "Robot.h"

/***************************************************************************
 * Fonction              : Robot()
 * Description           : Constructeur par defaut de la classe Robot.
 *                         Il y a creation de deux moteurs, un pour le cote
 *                         gauche et un autre pour le cote droit.  Il y a 
 *                         aussi creation du piezo.  
 *                         Par la suite, il y a initialisation des attributs
 *                         de la classe.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
Robot::Robot() {    
    moteurGauche_ = Moteur(GAUCHE);
    moteurDroite_ = Moteur(DROITE);
    piezo_ = Piezo();

    capaciteListeDels_ = 8;
    tailleListeDels_ = 2;
    listeDels_[0] = Del(&PORTB, 0, 1);
    listeDels_[1] = Del(&PORTB, 1, 0);
}

/***************************************************************************
 * Fonction              : avancer
 * Description           : Cette fonction permet au robot d'avancer selon
 *                         deux vitesses bien precises recues en parametre,
 *                         une pour chaque moteur. Selon la direction dans
 *                         laquelle se trouvait les moteurs, les parametres
 *                         seront modifies afin de dire aux moteurs d'aller
 *                         vers l'avant.
 * Parametres d'entree   : 
 * 		- pourcentageGauche (const uint8_t) :
 *                         Specifie le pourcentage auquel le moteur gauche
 *                         doit fonctionner.
 *      - pourcentageDroite (const uint8_t) :
 *                         Specifie le pourcentage auquel le moteur droit
 *                         doit fonctionner.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Robot::avancer(const uint8_t pourcentageGauche, const uint8_t pourcentageDroite) {
    switch(moteurDroite_.obtenirDirection()) {
        case ARRET : 
            moteurDroite_.modifierDirection(AVANT);
            moteurDroite_.demarrerMoteur(pourcentageDroite);
            break;
        case ARRIERE :
            moteurDroite_.modifierDirection(AVANT);
            moteurDroite_.modifierVitesse(pourcentageDroite);
            break;
        case AVANT :
            moteurDroite_.modifierVitesse(pourcentageDroite);
            break;
    }

    switch(moteurGauche_.obtenirDirection()) {
        case ARRET :
            moteurGauche_.modifierDirection(AVANT);
            moteurGauche_.demarrerMoteur(pourcentageGauche);
            break;
        case ARRIERE :
            moteurGauche_.modifierDirection(AVANT);
            moteurGauche_.modifierVitesse(pourcentageGauche);
            break;
        case AVANT :
            moteurGauche_.modifierVitesse(pourcentageGauche);
            break;
    }
}

/***************************************************************************
 * Fonction              : reculer
 * Description           : Cette fonction permet au robot de reculer selon
 *                         deux vitesses bien precises recues en parametre,
 *                         une pour chaque moteur. Selon la direction dans
 *                         laquelle se trouvait les moteurs, les parametres
 *                         seront modifies afin de dire aux moteurs d'aller
 *                         vers l'arriere.
 * Parametres d'entree   : 
 * 		- pourcentageGauche (const uint8_t) :
 *                         Specifie le pourcentage auquel le moteur gauche
 *                         doit fonctionner.
 *      - pourcentageDroite (const uint8_t) :
 *                         Specifie le pourcentage auquel le moteur droit
 *                         doit fonctionner.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Robot::reculer(const uint8_t pourcentageGauche, const uint8_t pourcentageDroite) {
    switch(moteurDroite_.obtenirDirection()) {
        case ARRET : 
            moteurDroite_.modifierDirection(ARRIERE);
            moteurDroite_.demarrerMoteur(pourcentageDroite);
            break;
        case AVANT :
            moteurDroite_.modifierDirection(ARRIERE);
            moteurDroite_.modifierVitesse(pourcentageDroite);
            break;
        case ARRIERE :
            moteurDroite_.modifierVitesse(pourcentageDroite);
            break;
    }

    switch(moteurGauche_.obtenirDirection()) {
        case ARRET :
            moteurGauche_.modifierDirection(ARRIERE);
            moteurGauche_.demarrerMoteur(pourcentageGauche);
            break;
        case AVANT :
            moteurGauche_.modifierDirection(ARRIERE);
            moteurGauche_.modifierVitesse(pourcentageGauche);
            break;
        case ARRIERE :
            moteurGauche_.modifierVitesse(pourcentageGauche);
            break;
    }
}

/***************************************************************************
 * Fonction              : avancer
 * Description           : Cette fonction permet au robot de s'arreter.
 *                         Elle appelera la fonction arreterMoteur de la
 *                         classe Moteur.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Robot::arreter(){
    moteurDroite_.arreterMoteur();
    moteurGauche_.arreterMoteur();
}

/***************************************************************************
 * Fonction              : tournerDroite
 * Description           : Cette fonction permet au robot de tourner a droite.
 *                         Elle appelera deux fonctions pour chaque moteur.
 *                         Le moteur droit ira dans la direction arriere.
 *                         Le moteur gauche ira dans la direction avant.
 *                         Un pourcentage sera precise, et chaque moteur 
 *                         fera appel a la fonction demarrerMoteur.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Robot::tournerDroite() {
    moteurDroite_.modifierDirection(ARRIERE);
    moteurGauche_.modifierDirection(AVANT);

    uint8_t pourcentage = 40;
    
    moteurDroite_.demarrerMoteur(pourcentage);
    moteurGauche_.demarrerMoteur(pourcentage);
}

/***************************************************************************
 * Fonction              : tournerDroite
 * Description           : Cette fonction permet au robot de tourner a droite.
 *                         Elle appelera deux fonctions pour chaque moteur.
 *                         Le moteur droit ira dans la direction arriere.
 *                         Le moteur gauche ira dans la direction avant.
 *                         La vitesse est precisee en parametre, et chaque  
 *                         moteur fera appel a la fonction demarrerMoteur
 *                         avec la vitesse en parametre.
 * Parametres d'entree   : 
 * 		- pourcentageGauche (const uint8_t) :
 *                         Specifie le pourcentage auquel le moteur gauche
 *                         doit fonctionner.
 *      - pourcentageDroite (const uint8_t) :
 *                         Specifie le pourcentage auquel le moteur droit
 *                         doit fonctionner.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Robot::tournerDroite(const uint8_t pourcentageGauche, const uint8_t pourcentageDroite) {
    moteurDroite_.modifierDirection(ARRIERE);
    moteurGauche_.modifierDirection(AVANT);
    
    moteurDroite_.demarrerMoteur(pourcentageDroite);
    moteurGauche_.demarrerMoteur(pourcentageGauche);
}

/***************************************************************************
 * Fonction              : tournerDroite
 * Description           : Cette fonction permet au robot de tourner a droite.
 *                         Elle appelera deux fonctions pour chaque moteur.
 *                         Le moteur droit ira dans la direction arriere.
 *                         Le moteur gauche ira dans la direction avant.
 *                         Un pourcentage sera precise, et chaque moteur 
 *                         fera appel a la fonction demarrerMoteur.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Robot::tournerGauche() {
    moteurDroite_.modifierDirection(AVANT);
    moteurGauche_.modifierDirection(ARRIERE);

    uint8_t pourcentage = 40;
    
    moteurDroite_.demarrerMoteur(pourcentage);
    moteurGauche_.demarrerMoteur(pourcentage);
}

/***************************************************************************
 * Fonction              : tournerGauche
 * Description           : Cette fonction permet au robot de tourner a gauche.
 *                         Elle appelera deux fonctions pour chaque moteur.
 *                         Le moteur droit ira dans la direction avant.
 *                         Le moteur gauche ira dans la direction arriere.
 *                         La vitesse est precisee en parametre, et chaque  
 *                         moteur fera appel a la fonction demarrerMoteur
 *                         avec la vitesse en parametre.
 * Parametres d'entree   : 
 * 		- pourcentageGauche (const uint8_t) :
 *                         Specifie le pourcentage auquel le moteur gauche
 *                         doit fonctionner.
 *      - pourcentageDroite (const uint8_t) :
 *                         Specifie le pourcentage auquel le moteur droit
 *                         doit fonctionner.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Robot::tournerGauche(const uint8_t pourcentageGauche, const uint8_t pourcentageDroite) {
    moteurDroite_.modifierDirection(AVANT);
    moteurGauche_.modifierDirection(ARRIERE);
    
    moteurDroite_.demarrerMoteur(pourcentageDroite);
    moteurGauche_.demarrerMoteur(pourcentageGauche);
}

/***************************************************************************
 * Fonction              : allumerDel
 * Description           : Cette fonction permet au robot d'allumer une DEL.
 *                         Le numero de cette DEL est specifiee en parametre de
 *                         fonction.  La DEL fera afficher la couleur verte.
 * Parametres d'entree   : 
 * 		- numeroDels (const uint8_t) :
 *                         Specifie le numero de la DEL qui doit etre allume.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Robot::allumerDel(const uint8_t numeroDels){
    listeDels_[numeroDels].afficherVert();
}

/***************************************************************************
 * Fonction              : fermerDel
 * Description           : Cette fonction permet au robot d'eteindre une DEL.
 *                         Le numero de cette DEL est specifiee en parametre de
 *                         fonction.
 * Parametres d'entree   : 
 * 		- numeroDels (const uint8_t) :
 *                         Specifie le numero de la DEL qui doit etre etteinte.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Robot::fermerDel(const uint8_t numeroDels){
	listeDels_[numeroDels].eteindre();
}

/***************************************************************************
 * Fonction              : modifierFrequence
 * Description           : Cette fonction permet au robot de modifier la note
 *                         que le piezo doit jouer.  Elle appelle la fonction
 *                         modifierPiezo de la classe Piezo.
 * Parametres d'entree   : 
 * 		- note (uint8_t) : Specifie la note qui doit etre jouer par le piezo.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Robot::modifierFrequence(uint8_t note){
    piezo_.modifierFrequence(note);
}

/***************************************************************************
 * Fonction              : arretSon
 * Description           : Cette fonction permet au robot d'arreter de faire
 *                         jouer le piezo.  Elle appelle la fonction
 *                         arretSon de la classe Piezo.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Robot::arretSon() const {
    piezo_.arretSon();
}

/***************************************************************************
 * Fonction              : arretSon
 * Description           : Cette fonction permet au piezo de faire jouer
 *                         des notes.  Elle appelle la fonction debutSon
 *                         de la classe Piezo.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Robot::debutSon() const {
    piezo_.debutSon();
}