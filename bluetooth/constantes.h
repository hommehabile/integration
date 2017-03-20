#ifndef CONSTANTES_H
#define CONSTANTES_H

//frequence
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <util/twi.h>

//ports
enum Ports {A, B, C, D};

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

#endif
