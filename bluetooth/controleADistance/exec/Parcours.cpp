#include "Parcours.h"

/***************************************************************************
 * Fonction              : Parcours()
 * Description           : Constructeur par defaut de la classe Parcours.
 *                         Initialise les bouttons. 
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
Parcours::Parcours() {
	boutonSelection_ = Bouton(&PINA, 7, true);
	boutonConfirmation_ = Bouton(&PINA, 6, true);
	boutonInterruption_ = Bouton(&PIND, 2, false);
}

/***************************************************************************
 * Fonction              : ligneDroite
 * Description           : Cette fonction permet au robot de suivre une ligne
 *                         noire. Grace a ces capteurs Cytron, il peut detecter
 *                         sa divergence et regler celle-ci en reglant la
 *                         vitesse de ses moteurs  
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :     
 * 		  Aucun.
 ***************************************************************************/
void Parcours::ligneDroite(){
	if(cytron_.tableau(0,0,1,0,0)) {
        robot_.avancer(VITESSE_NORMALE, VITESSE_NORMALE);
    } else if(cytron_.tableau(0,1,2,0,0))  {
        robot_.avancer(VITESSE_SEMI_LENTE,VITESSE_NORMALE);
    } else if(cytron_.tableau(0,0,2,1,0))  {
         robot_.avancer(VITESSE_NORMALE,VITESSE_SEMI_LENTE);
    } else if(cytron_.tableau(1,1,0,0,0)) {
        robot_.avancer(VITESSE_SEMI_LENTE, VITESSE_SEMI_RAPIDE);
    } else if(cytron_.tableau(0,0,0,1,1)) {
        robot_.avancer(VITESSE_SEMI_RAPIDE, VITESSE_SEMI_LENTE);
    } else if(cytron_.tableau(1,0,0,0,0)) {
        robot_.avancer(VITESSE_LENTE, VITESSE_SEMI_RAPIDE);
    } else if(cytron_.tableau(0,0,0,0,1)) {
        robot_.avancer(VITESSE_SEMI_RAPIDE, VITESSE_LENTE);
    }
}

/***************************************************************************
 * Fonction              : tournerDroiteSansDetection
 * Description           : Le robot tournera de 90 degré vers la droite sans
 *                         le detecteur.  Les moteurs seront actionnes, un
 *                         delai sera applique, et ensuite les moteurs seront
 *                         arretes.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :
 * 		  Aucun.
 ***************************************************************************/
void Parcours::tournerDroiteSansDetection(){
	robot_.tournerDroite();
	delai_ms(TEMPS_90_DEGRES);
    robot_.arreter();
}

/***************************************************************************
 * Fonction              : tournerDroiteSansDetection
 * Description           : Le robot tournera vers la droite sans le detecteur
 *                         pendant un temps bien precis, passe en parametre.
 *                         Les moteurs seront actionnes, une delai de temps
 *                         de valeur passe en parametre sera applique, et
 *                         ensuite les moteurs seront arretes.
 * Parametres d'entree   : 
 * 		- temps (uint16_t) :
 *                         Valeur du temps pendant lequel le robot devra
 *                         tourner vers la droite.
 * Parametres de sortie  :
 * 		  Aucun.
 ***************************************************************************/
void Parcours::tournerDroiteSansDetection(uint16_t temps){
	robot_.tournerDroite();
	delai_ms(temps);
    robot_.arreter();
}

/***************************************************************************
 * Fonction              : tournerGaucheSansDetection
 * Description           : Le robot tournera de 90 degré vers la gauche sans
 *                         le detecteur.  Les moteurs seront actionnes, un
 *                         delai sera applique, et ensuite les moteurs seront
 *                         arretes.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :
 * 		  Aucun.
 ***************************************************************************/
void Parcours::tournerGaucheSansDetection(){
	robot_.tournerGauche();
	delai_ms(TEMPS_90_DEGRES);
    robot_.arreter();
}

/***************************************************************************
 * Fonction              : tournerGaucheSansDetection
 * Description           : Le robot tournera vers la gauche sans le detecteur
 *                         pendant un temps bien precis, passe en parametre.
 *                         Les moteurs seront actionnes, une delai de temps
 *                         de valeur passe en parametre sera applique, et
 *                         ensuite les moteurs seront arretes.
 * Parametres d'entree   : 
 * 		- temps (uint16_t) :
 *                         Valeur du temps pendant lequel le robot devra
 *                         tourner vers la gauche.
 * Parametres de sortie  :   
 * 		  Aucun.
 ***************************************************************************/
void Parcours::tournerGaucheSansDetection(uint16_t temps){
	robot_.tournerGauche();
	delai_ms(temps);
    robot_.arreter();
}
  
/***************************************************************************
 * Fonction              : tournerDroiteAvecDetection
 * Description           : Le robot tourne a droite jusqu'à ce qu'il detecte
 *                         une ligne sur son chemin.
 *                        
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :
 * 		  Aucun.
 ***************************************************************************/
void Parcours::tournerDroiteAvecDetection(){
	robot_.tournerDroite();					        //Le robot tounera vers la droite.
	while(!(cytron_.tableau(2,2,2,1,2))) {}			//Tant que le capteur sera false, le robot tournera.
	robot_.arreter();						        //Le robot s'immobilisera.
}

/***************************************************************************
 * Fonction              : tournerGaucheAvecDetection
 * Description           : Cette fonction permet au robot de tourner a gauche
 *                         jusqu'a ce qu'il detecte une ligne dans le capteur
 *                         de centre droit
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  : 
 * 		  Aucun.
 ***************************************************************************/
void Parcours::tournerGaucheAvecDetection(){
	robot_.tournerGauche();					        //Le robot tounera vers la gauche.
	while(!(cytron_.tableau(2,1,2,2,2))) {}			//Tant que le capteur sera false, le robot tournera.
	robot_.arreter();						        //Le robot s'immobilisera.
}

/***************************************************************************
 * Fonction              : suivreLigneDroiteAvecTempsMs
 * Description           : Cette fonction permet au robot de suivre une ligne 
 *                         droite pendant un temps donné de millisecondes.
 * Parametres d'entree   : 
 * 		- tempsMs (uint16_t) :
 *                         Nombre de millisecondes durant lequel le robot devra
 *                         suivre la ligne avec le capteur.
 * Parametres de sortie  :
 * 		  Aucun.
 ***************************************************************************/
void Parcours::suivreLigneDroiteAvecTempsMs(uint16_t tempsMs) {
    for(uint16_t i = 0 ; i < tempsMs ; i++) {
        ligneDroite();
        delai_ms(1);
    }
}

/***************************************************************************
 * Fonction              : assignerCouleurParcours
 * Description           : Cette fonction permet a l'utilisateur de choisir 
 *                         une couleur de parcours que le robot effectuera
 *                         par la suite
 * Parametres d'entree   : bool &changerEtat
 * 		- changerEtat (bool &) :
 *                         Ce parametre est passe en reference.  Il sera mis
 *                         a true si l'etat est change dans cette fonction./
 * Parametres de sortie  :  
 * 		- couleurParcours (CouleurParcours) :
 *                         Retourne la couleur selectionnee, soit rouge ou verte.
 ***************************************************************************/
CouleurParcours Parcours::assignerCouleurParcours(bool &changerEtat) {
    enum EtatCouleur {ETAT_INITIAL, ETAT_VERT, ETAT_ROUGE, ETAT_ATTENTE_VERT, 
    ETAT_ATTENTE_ROUGE, ETAT_CONFIRMATION};
    
    EtatCouleur etat = ETAT_INITIAL;         
    CouleurParcours couleurParcours = PARCOURS_VERT;

    while(true){
        switch(etat){
            case ETAT_INITIAL:                              //Si on pese sur on pese sur le bouton 
                if(boutonInterruption_.etatBouton())       //interrupt on peut choisir l'etape du parcours. Sinon 
                    changerEtat = true;                     //on peut aller vers l'etat vert en pesant sur le bouton
                else if(boutonSelection_.etatBouton())       //de selection.
                    etat = ETAT_ATTENTE_VERT;
                break;
            
            case ETAT_VERT:                                 //La del affiche vert et on attend que
                robot_.allumerDel(0);                       //l'utilisateur modifie ou confirme son choix en pesant
                couleurParcours = PARCOURS_VERT;            //sur le bouton de selection ou confirmation.
                if(boutonConfirmation_.etatBouton())
                    etat = ETAT_CONFIRMATION;
                else if(boutonSelection_.etatBouton())
                    etat = ETAT_ATTENTE_ROUGE;
                break;
            
            case ETAT_ROUGE:                                //La del affiche rouge et on attend que
                robot_.allumerDel(1);                       //l'utilisateur modifie ou confirme son choix en pesant
                couleurParcours = PARCOURS_ROUGE;           //sur le bouton de selection ou confirmation.
                if(boutonConfirmation_.etatBouton())         
                    etat = ETAT_CONFIRMATION;
                else if(boutonSelection_.etatBouton())
                    etat = ETAT_ATTENTE_VERT;
                break;

            case ETAT_ATTENTE_VERT:                         //On attend que l'utilisateur relache 
                if(!boutonSelection_.etatBouton())           //le bouton de selection afin de se rendre
                    etat = ETAT_VERT;                       //a l'etat vert.
                break;

            case ETAT_ATTENTE_ROUGE:                        //On attend que l'utilisateur relache 
                if(!boutonSelection_.etatBouton())           //le bouton de selection afin de se rendre
                    etat = ETAT_ROUGE;                      //a l'etat rouge.
                break;

            case ETAT_CONFIRMATION:                         //Le choix est confirme. On retourne la valeur de
                return couleurParcours;                     //couleurParcours.
         }       
    }
}

/***************************************************************************
 * Fonction              : debutParcours
 * Description           : Cette fonction effectue les operation du parcours 
 *                         du depart jusqu'a ce qu'il se rende sur le segment
 *                         AB.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :   
 * 		  Aucun.
 ***************************************************************************/
void Parcours::debutParcours() {
	delai_ms(2000);							//On attend 2 secondes selon l'enonce
	robot_.tournerDroite();					//Depasser la premiere ligne
	delai_ms(1600);
    tournerDroiteAvecDetection();           //Tourner de 180 degres.

    while(!cytron_.tableau(1,1,1,1,1)){     //Avancer en ligne droite jusqu'a la detection d'une ligne.          
        ligneDroite();
    }
    delai_ms(TEMPS_ATTENTE_VIRAGE);         //Permet de depasser la ligne legerement pour faciliter le tournant.
    tournerGaucheAvecDetection();           //Tourner a gauche jusqu'a la detection d'une ligne (90 degres).

   
    while(!cytron_.tableau(1,1,1,0,0)){     //Avancer en ligne droite jusqu'a la detection d'une ligne.
        ligneDroite();
    }
    delai_ms(TEMPS_ATTENTE_VIRAGE);         //Permet de depasser la ligne legerement pour faciliter le tournant.
    tournerGaucheAvecDetection();           //Tourner a gauche jusqu'a la detection d'une ligne (90 degres).
}

/***************************************************************************
 * Fonction              : stationnementTroisLignes
 * Description           : Cette fonction effectue un des deux stationnement 
 *                         du segment AB du parcours dependamment de la couleur
 *                         de son parcours. Il y a detection de trois lignes 
 *                         et il fait son stationnement vers le sud.
 *
 * Parametres d'entree   :
 * 		- couleur (CouleurParcours) :
 *                         Selon la couleur de ce parametre, le nombre de lignes
 *                         que le robot devra traverser avant de se stationner
 *                         sera different.  La couleur peut etre rouge ou verte.
 * Parametres de sortie  :
 * 		  Aucun.
 ***************************************************************************/
void Parcours::stationnementTroisLignes(CouleurParcours couleur){
    //Declaration des variables utiles a la fonction.
    int nbLignesFranchies = 0;
    int nbLignesNecessaires = 0;
    bool stationnementFini = false;
    bool detection = false;
    
    //Assignation du nombre de lignes devant etre traversee selon la couleur selectionnee.
    switch(couleur){
        case PARCOURS_VERT : 
            nbLignesNecessaires = 3;                        //Pour la couleur verte, le robot franchira 3 lignes.
            break;
        case PARCOURS_ROUGE:
            nbLignesNecessaires = 6;                        //Pour la couleur verte, le robot franchira 6 lignes.
            break;
    }

    //Boucle permettant de franchir le nombre de lignes desirees.
    while (!stationnementFini){
		ligneDroite();
        if(cytron_.tableau(1,1,1,1,1) && !detection) {
            nbLignesFranchies++;
            detection = true;
        }
        if(!cytron_.tableau(1,1,1,1,1))
			detection = false;
        if (nbLignesFranchies >= nbLignesNecessaires)
			stationnementFini = true;
    }

    //A cette etape, le robot se positionne dans la case pour effectuer son stationnement.
    suivreLigneDroiteAvecTempsMs(TEMPS_AVANT_STATIONNEMENT);
    robot_.arreter();
    delai_ms(500);                                          //On laisse le temps au robot de se stabiliser.
    tournerDroiteSansDetection(TEMPS_90_DEGRES);        //Tourner droite pour que le robot soit stationner.

    robot_.arreter();
    delai_ms(500);                                          //On laisse le temps au robot de se stabiliser.

    robot_.reculer(VITESSE_NORMALE, VITESSE_NORMALE);
    delai_ms(800);
    robot_.arreter();
	
    //Le piezo emmettra un son pendant une demie seconde.
    robot_.modifierFrequence(70);
    robot_.debutSon();
    delai_ms(500);
    robot_.arretSon();

    //Tant que l'utilisateur n'appuie pas sur le bouton sur la carte, le robot n'executera aucune action.
    while(!boutonInterruption_.etatBouton()) {}             //Attendre la pesee du bouton.
    
    tournerGaucheAvecDetection();                           //Fin du stationnement.  Tourner gauche pour repartir.

    //Si la couleur selectionnee etait la verte, le robot passera les trois autres lignes.
    if (couleur == PARCOURS_VERT){
        nbLignesFranchies = 0;
        nbLignesNecessaires = 3;
        stationnementFini = false;
        while (!stationnementFini){  
            ligneDroite();
            if(cytron_.tableau(1,1,1,1,1) && !detection) {
                nbLignesFranchies++;
                detection = true;
            }
            if(!cytron_.tableau(1,1,1,1,1))
			    detection = false;
            if (nbLignesFranchies >= nbLignesNecessaires)
			    stationnementFini = true;
        }
    }

	while(!cytron_.tableau(1,1,1,0,0)) { ligneDroite(); }   //Avancement en ligne droite jusqu'a la fin de la ligne.

    //Une fois arrive au bout de la ligne droite, le robot tournera a gauche.
    delai_ms(TEMPS_ATTENTE_VIRAGE);                         //On depasse legerement la ligne pour faciliter le virage.
	tournerGaucheAvecDetection();                           //Tourner gauche avec le capteur.
}
    
/***************************************************************************
 * Fonction              : loiNormale
 * Description           : Le robot suit une ligne et rencontre 5 segments.
 *                         Deux de ces segments se terminent par un bout 
 *                         coloré rouge ou vert. Le robot devra emprunter le 
 *                         segment correspondant à la couleur qui lui a été 
 *                         assignée et se rendre jusqu'au bout pour ensuite 
 *                         faire un virage à 180 degrés, suivre le segment à 
 *                         nouveau et retourner sur le segment BC pour se 
 *                         diriger vers C.
 *                        
 * Parametres d'entree   :
 * 		- couleur (CouleurParcours) : 
 *                         Selon la couleur de ce parametre, le nombre de lignes
 *                         que le robot devra traverser avant de tourner
 *                         sera different.  La couleur peut etre rouge ou verte.
 * Parametres de sortie  :
 * 		  Aucun.
 ***************************************************************************/
void Parcours::loiNormale(CouleurParcours couleur){
    //Declaration des variables utiles pour la fonction.
    bool estVirageComplete = false;                         //Un bool determinant si le virage est fini.
    bool detection = false;                                 //Un bool determinant une detection (selon les circonstances).
    int nbSegmentsPasse = 0;                                //Le nombre de segments passe.
    int nbSegmentsNecessaire = 0;                           //Le nombre de segments necessaire.

    //Le nombre de segments necessaires est determine par la couleur du parcours.
    switch(couleur){
        case PARCOURS_VERT : 
            nbSegmentsNecessaire = 3;
            break;
        case PARCOURS_ROUGE:
            nbSegmentsNecessaire = 5;
            break;
    }

    //On s'ajuste a la ligne pour le pas la detecter par erreur.
    suivreLigneDroiteAvecTempsMs(1000);
                                          	
    while (!estVirageComplete){                             //Tant que le virage n'est pas complete.
        //Nous suivons une ligne droite.  Nous n'utilisons pas la fonction ligne droite puisqu'ici il y a des particularites.
        if(cytron_.tableau(0,0,1,0,0))
	        robot_.avancer(VITESSE_NORMALE, VITESSE_NORMALE);
	    else if(cytron_.tableau(0,1,2,0,0))
	        robot_.avancer(VITESSE_SEMI_LENTE,VITESSE_SEMI_RAPIDE);
	    else if(cytron_.tableau(0,0,2,1,0))
	         robot_.avancer(VITESSE_NORMALE,VITESSE_SEMI_LENTE);
	    else if(cytron_.tableau(0,0,0,1,1))
	        robot_.avancer(VITESSE_SEMI_RAPIDE, VITESSE_SEMI_LENTE);
	    else if(cytron_.tableau(0,0,0,0,1))
	        robot_.avancer(VITESSE_SEMI_RAPIDE, VITESSE_LENTE);

        //Si nous detectons un segment, nous incremontons le nombre de segments passe.								
        if (cytron_.tableau(1,2,2,2,0) && !detection){    
            nbSegmentsPasse++;
            detection = true;
        }

        if (!cytron_.tableau(1,2,2,2,0) && detection)       //Si nous avons detecter tantot, nous avancons pour depasser le segment.
            detection = false;
		
		if (nbSegmentsPasse >= nbSegmentsNecessaire){       //Si nous avons passe le nombre necessaire de segments, nous effectuons un virage.
			tournerGaucheAvecDetection();
			robot_.tournerGauche();
			delai_ms(1200);

            tournerGaucheAvecDetection();	                //Et puis nous pouvons detecter.
            while(!(cytron_.tableau(0,0,0,0,0)))            //Nous pouvons parcourir le segment.
                ligneDroite();
            
            //Nous effectuons un 180 degre dependamment de la couleur du parcours.
            if (couleur == PARCOURS_VERT)
                tournerGaucheAvecDetection(); 
            else if (couleur == PARCOURS_ROUGE)
                tournerDroiteAvecDetection();
                            
            estVirageComplete = true;                       //Le virage est alors complete.
        }   
    }
       
    //Le bout du segment a alors ete atteint.
    while(!cytron_.tableau(1,1,1,1,1)){                     //Nous suivons la ligne jusqu'a temps que nous captons une ligne pleine.
        ligneDroite();
    }
    delai_ms(TEMPS_ATTENTE_VIRAGE);
    tournerGaucheAvecDetection();                           //Tourner a gauche avec detection: de retour vers le segment BC.
    //A ton tour cinqQuarante!							
}

/***************************************************************************
 * Fonction              : cinqQuarante
 * Description           : Il suit la ligne et bifurque a 135 degres vers le 
 *                         nord est. Une fois son centre au milieu de tout les
 *                         lignes, il doit faire une rotation et demi afin de 
 *                         se diriger vers le prochain obstacle. Il doit bien
 *                         suivre la ligne jusqu'au prochain segment.
 *                        
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :
 * 		  Aucun.
 ***************************************************************************/
void Parcours::cinqQuarante() {
    suivreLigneDroiteAvecTempsMs(2500);

    while(!cytron_.tableau(0,0,0,1,2)){
        if(cytron_.tableau(0,0,1,0,0)) {
            robot_.avancer(VITESSE_NORMALE, VITESSE_NORMALE);
        } else if(cytron_.tableau(0,1,2,0,0))  {
            robot_.avancer(VITESSE_SEMI_LENTE,VITESSE_NORMALE);
        } else if(cytron_.tableau(0,0,2,1,0))  {
            robot_.avancer(VITESSE_NORMALE,VITESSE_SEMI_LENTE);
        }
    }
    tournerDroiteAvecDetection();
    suivreLigneDroiteAvecTempsMs(800);

    //On fait le 540.
    robot_.tournerGauche();
    int nbIncrementation = 0;
    bool estSurLigne = false;
    while(nbIncrementation < 9) {
        estSurLigne = cytron_.tableau(1,0,0,0,0);
        if(estSurLigne){
            while(!cytron_.tableau(0,0,0,0,1)) {}
            estSurLigne = false;
            nbIncrementation++;
        }
    }

    //On revient sur la ligne si on a trop tourne.
    while(!cytron_.tableau(0,2,1,2,0))
        robot_.tournerDroite(VITESSE_SEMI_LENTE, VITESSE_LENTE);
    
    while(!cytron_.tableau(0,0,0,0,0)) {
        if(cytron_.tableau(0,0,1,0,0))
            robot_.avancer(VITESSE_SEMI_LENTE, VITESSE_SEMI_LENTE);
        else if(cytron_.tableau(0,1,2,0,0))
            robot_.avancer(VITESSE_LENTE,VITESSE_SEMI_LENTE);
        else if(cytron_.tableau(0,0,2,1,0))
             robot_.avancer(VITESSE_SEMI_LENTE,VITESSE_LENTE);
        else if(cytron_.tableau(1,1,0,0,0))
            robot_.avancer(VITESSE_SEMI_LENTE, VITESSE_SEMI_RAPIDE);
        else if(cytron_.tableau(0,0,0,1,1))
            robot_.avancer(VITESSE_SEMI_RAPIDE, 0);
        else if(cytron_.tableau(1,0,0,0,0))
            robot_.avancer(VITESSE_LENTE, VITESSE_SEMI_RAPIDE);
        else if(cytron_.tableau(0,0,0,0,1))
            robot_.avancer(VITESSE_SEMI_RAPIDE, 0);
    }

    delai_ms(TEMPS_ATTENTE_VIRAGE);
    tournerDroiteAvecDetection();
    while(!cytron_.tableau(0,0,0,0,0)) { ligneDroite(); }
    delai_ms(TEMPS_ATTENTE_VIRAGE);
    tournerGaucheAvecDetection();
    robot_.arreter();
}
    
/***************************************************************************
 * Fonction              : touchdown
 * Description           : À la fin du 540, le robot s'arrete et attend. Il 
 *                         capte la lumière selon ses capteurs qui lui indique
 *                         d'aller a gauche ou a droite quand on pèse sur le
 *                         bouton d'interruption. Il doit suivre la ligne pour 
 *                         par la suite, aller rejoindre le deuxième bout de 
 *                         segement.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  : 
 * 		  Aucun.
 ***************************************************************************/
void Parcours::touchdown(){
    DDRA &= 0xcf;                                           //On met PA4 et PA5 en entree pour le convertisseur analogique numerique.

    //Declaration de variables et d'objets.
    can convertisseur;
    enum Cote {DROITE, GAUCHE};
    Cote coteChoisi;
    const uint8_t seuil = 240;                              //Entre 0 et 255.
    bool selectionne;

    for(uint8_t i = 2; i > 0; i--) {                        //Il y a deux touchdown a faire.
        //On se rend au T.
        while(!cytron_.tableau(1,1,1,1,1)) { ligneDroite(); }
        robot_.arreter();

        //On selectionne un cote.
        selectionne = false;
        while(!selectionne) {
            if(convertisseur.lecture(4) >> 2 >= seuil) {
                coteChoisi = DROITE;
                selectionne = true;
            } else if(convertisseur.lecture(5) >> 2 >= seuil) {
                coteChoisi = GAUCHE;
                selectionne = true;
            }
        }

        //On attend de peser le bouton.
        while(!boutonInterruption_.etatBouton()) {}
        //On suit le trajet.
        if(coteChoisi == GAUCHE) {
            robot_.avancer(VITESSE_LENTE, VITESSE_LENTE);   //On depasse un peu le T.
            delai_ms(800);
            robot_.tournerGauche();                         //On tourne.
            while(!cytron_.tableau(2,2,1,2,2)) {}

            //Boucle principale.
            while(!cytron_.tableau(0,0,0,0,0)) {
                if(cytron_.tableau(2,2,0,2,2)) {
                    if(cytron_.tableau(2,1,0,2,2) || cytron_.tableau(1,2,0,2,2))
                        robot_.avancer(0, VITESSE_SEMI_LENTE);
                    else if(cytron_.tableau(2,2,0,1,2) || cytron_.tableau(2,2,0,2,1))
                        robot_.avancer(VITESSE_SEMI_LENTE, 0);
                    else
                        robot_.avancer(VITESSE_SEMI_LENTE, VITESSE_SEMI_LENTE);
                }
            }

            //On traverse le vide.
            robot_.avancer(VITESSE_NORMALE, VITESSE_SEMI_LENTE);
            while(!cytron_.tableau(2,2,1,2,2)) {}
            while(!cytron_.tableau(2,2,0,2,2)) {}
            delai_ms(600);
            robot_.tournerGauche();
	        while(!(cytron_.tableau(2,2,1,2,2))) {}			//Tant que le capteur sera false, le robot tournera à gauche.
        } else if(coteChoisi == DROITE) {
            
            robot_.avancer(VITESSE_LENTE, VITESSE_LENTE);   //On depasse un peu le T.
            delai_ms(800);
            robot_.tournerDroite();
            while(!cytron_.tableau(2,2,1,2,2)) {}

            //Boucle principale.
            while(!cytron_.tableau(0,0,0,0,0)) {
                if(cytron_.tableau(2,2,0,2,2)) {
                    if(cytron_.tableau(2,1,0,2,2) || cytron_.tableau(1,2,0,2,2))
                        robot_.avancer(0, VITESSE_SEMI_LENTE);
                    else if(cytron_.tableau(2,2,0,1,2) || cytron_.tableau(2,2,0,2,1))
                        robot_.avancer(VITESSE_SEMI_LENTE, 0);
                    else
                        robot_.avancer(VITESSE_SEMI_LENTE, VITESSE_SEMI_LENTE);
                }
            }
            //On traverse le vide.
            robot_.avancer(VITESSE_SEMI_LENTE, VITESSE_NORMALE);
            while(!cytron_.tableau(2,2,1,2,2)) {}
            while(!cytron_.tableau(2,2,0,2,2)) {}
            delai_ms(600);
            //On s'ajuste.
            robot_.tournerDroite();					        //Le robot tounera vers la droite.
	        while(!(cytron_.tableau(2,2,1,2,2))) {}			//Tant que le capteur sera false, le robot tournera.
        }
    }
}
   
/***************************************************************************
 * Fonction              : pointille
 * Description           : Cette fonction effectue la partie pointillee du 
 *                         parcours en emettant un son des qu'il rentre dans un 
 *                         pointille. Le son arrete lorsqu'il n'y a plus de 
 *                         pointille.
 * Parametres d'entree   : 
 * 		  Aucun.
 * Parametres de sortie  :
 * 		  Aucun.
 ***************************************************************************/
void Parcours::pointille(){
    
    //on modifie la frequence du son
    robot_.modifierFrequence(80);
    
    //cette fonction fait effet jusqu'a ce qu'on franchit 5 trous.
    for(int nbTrousFranchis = 0; nbTrousFranchis < 5; nbTrousFranchis++){
        
        //tant qu'on ne voit pas le vide on suit la ligne
        while (!cytron_.tableau(0,0,0,0,0)){
            ligneDroite();
        }
        //un son est joue des qu'on detecte un vide
        robot_.debutSon();
        //on avance en ligne droite jusqu'a ce qu'on detecte quelque chose
        robot_.avancer(VITESSE_NORMALE, VITESSE_NORMALE);
        while(cytron_.tableau(0,0,0,0,0)){}
    }
    robot_.arretSon();
}

/***************************************************************************
 * Fonction              : Stationnement Fin
 * Description           : Comprend la fin du pointillé jusqu'à la fin du 
 *                         parcours ainsi que son stationnement final selon
 *                         selon la bonne couleur. Au bout de la dernière 
 *                         ligne droite (apres les virages a gauche), il 
 *                         s'arrête. Lorsqu'on appuie sur le bouton, il se
 *                         stationne à l'envers dans la case de la bonne 
 *                         couleur.                
 *                        
 * Parametres d'entree   : CouleurParcours couleur
 * 		  Aucun.
 * Parametres de sortie  : void  
 * 		  Aucun.
 ***************************************************************************/

void Parcours::stationnementFin(CouleurParcours couleur){
    // vers le coin et ensuite virage du coin
    while (!(cytron_.tableau(0,0,0,0,0))){ 
		ligneDroite(); 
	}
    delai_ms(TEMPS_ATTENTE_VIRAGE);                             
    tournerGaucheAvecDetection();				                
    
    // vers le milieu et ensuite virage au milieu
    while(!(cytron_.tableau(1,1,1,0,0))){ 
		ligneDroite();
	}               
    delai_ms(1150);
    while(!(cytron_.tableau(0,0,0,0,0))){ 
		robot_.tournerGauche();                 // afin de ne pas detecter directement sur la ligne
	}											 			
    tournerGaucheAvecDetection();
    
    while(!(cytron_.tableau(0,0,0,0,0))){       // nous pouvons parcourir le segment
		ligneDroite();
    }
    robot_.arreter();

    // attente du bouton interrupt pour passer au stationnement final
    while(!boutonInterruption_.etatBouton()) {}         //attendre le pesee du bouton.

    robot_.avancer(VITESSE_NORMALE,VITESSE_NORMALE);
    delai_ms(2900); 
    robot_.arreter();
    delai_ms(500);                
 
    if (couleur == PARCOURS_ROUGE){             
        tournerDroiteSansDetection(TEMPS_90_DEGRES);      
        robot_.arreter();
        delai_ms(500);   
        robot_.avancer(VITESSE_NORMALE, VITESSE_NORMALE);
        delai_ms(1600);                                    
        robot_.arreter();
        delai_ms(500);   
        tournerDroiteSansDetection(TEMPS_90_DEGRES); 
                                            
    }
    else if (couleur == PARCOURS_VERT){        
        tournerGaucheSansDetection(TEMPS_90_DEGRES);
        robot_.arreter();
        delai_ms(500);   
        robot_.avancer(VITESSE_NORMALE, VITESSE_NORMALE);                   // avancer pour se postionner au centre du carre vert
        delai_ms(1600);                      // avec un certain temps (AJUSTER)
        robot_.arreter();
        delai_ms(500);   
        tournerGaucheSansDetection(TEMPS_90_DEGRES);       // ~90 degre vers la droite pour revenir a l'horizontal
                                            // les deux rotations de ~90 degre s'annulent, donc devrait theoriquement revenir a l'orientation du
                                            // debut ( <- )      
    }
    robot_.arreter();
}
