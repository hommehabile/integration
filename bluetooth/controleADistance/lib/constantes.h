#ifndef CONSTANTES_H
#define CONSTANTES_H

//frequence
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/twi.h>
#include "minuterie.h"

enum CouleurParcours {PARCOURS_VERT = 0,PARCOURS_ROUGE = 1};

//del
#define ETEINTE 0
#define VERTE 1
#define ROUGE 2
#define AMBRE 3

//moteur
#define AVANCER 1
#define RECULER 0
#define ROUE_DROITE 0x80	//PD7
#define ROUE_GAUCHE 0x40	//PD6

/*
 ENUMERATION DES ENUMS DANS LES DIFFERENTS FICHIERS
 moteur.h
    - enum Direction {AVANT, ARRIERE, ARRET};
    - enum Cote {DROITE, GAUCHE};
    - enum Port {A1, B1};

*/

#endif
