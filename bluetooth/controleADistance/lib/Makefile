########       AVR Project Makefile   	  ########
#####                                        #####
#####	   Makefile produit et ecrit par     #####
#####	Simon Barrette & Jerome Collin pour  #####
#####		 INF1995 - 2016		     #####
#####					     #####
#####	      Inspire de Pat Deegan -        #####
#####  Psychogenic Inc (www.psychogenic.com) #####
##################################################

# Ce Makefile vous permet de compiler des projets
# pour les microcontroleurs Atmel AVR sur 
# Linux ou Unix, en utilisant l'outil AVR-GCC. 
# Ce Makefile supporte C & C++

include ../makefile-common/makefile_common

#####      Details specifique a la cible       #####
#####  Vous devez les adapter a votre projet   #####

# Nom de la librairie
LIBNAME=libprojet6771
TRGDIR=./
PROJECTNAME=$(LIBNAME)

# Fichiers sources
# (Listez tous les fichiers a compiler, ex: 'tp1.c, tp2.cpp'):
# Utilisez le suffixe .cpp pour les fichiers C++
PRJSRC= constantes.h can.cpp bouton.cpp del.cpp minuterie.cpp moteur.cpp piezo.cpp cytron.cpp

# Inclusions additionnels (ex: -I/path/to/mydir)
INC=

# Libraires a lier (ex: -lmylib)
LIBS=


####################################################
#####         Configuration terminee           #####
#####                                          #####
#####  Le reste de cette section contient les  #####
##### details d'implementation vous permettant #####
##### de mieux comprendre le fonctionnement de ##### 
#####   ce Makefile en vue de sa modification  #####
####################################################


####### Options de compilation #######

# Flags pour le compilateur en C
CFLAGS= -I. -c -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall

# Flags pour le compilateur de la librairie  
ARFLAGS = crs                                      


####### Cible (Target) #######

#Nom des cibles par defaut
LIBTRG=$(TRGDIR)$(LIBNAME).a
HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex


####### Creation des commandes du Makefile ####### 

# Creation des cibles Phony (Phony Target)
# En plus de la commande make qui permet de compiler
# votre projet, vous pouvez utilisez les commandes
# make all, make install et make clean
.PHONY: all install clean 

# Make all permet simplement de compiler le projet
#
all: $(LIBTRG)

# Implementation de la cible
$(LIBTRG): $(OBJDEPS)
	$(AR) $(ARFLAGS) -o $(LIBTRG) $(OBJDEPS) 

# Production des fichiers object
# De C a objet
%.o: %.c
	$(CC) $(CFLAGS) -c $<
# De C++ a objet
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

# Verification des dependances (header dependencies)
-include *.d

# Pour plus d'information sur cette section, consulter:
# http://bit.ly/2580FU8

# Production des fichiers hex a partir des fichiers elf
%.hex: %.out
	$(OBJCOPY) -j .text -j .data \
		-O $(HEXFORMAT) $< $@

# Make clean permet d'effacer tout les fichiers generes
# lors de la compilation
clean:
	$(REMOVE) $(OBJDEPS) *.d

# Pour plus d'information sur les phony target, consulter:
# http://bit.ly/1WBQe61

# De plus, pour mieux comprendre les makefiles et 
# leur fonctionnement, consulter la documentation de GNU Make:
# http://bit.ly/23Vpk8s

# Finalement, ce tutoriel en ligne constitut une bonne 
# introduction au Makefile:
# http://bit.ly/1XvxsN3

#####                    EOF                   #####
