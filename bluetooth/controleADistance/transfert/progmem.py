#!/usr/bin/python

import os.path
import sys
import getopt
import binascii

def showUsage():
	print("Usage: python3 progmem.py [-o sortie] <fichier>")
	sys.exit(2)

def main():
	#definition des opcades
	opcodes = {
		"dbt": 0b00000001,
		"att": 0b00000010,
		"dal": 0b01000100,
		"det": 0b01000101,
		"sgo": 0b01001000,
		"sar": 0b00001001,
		"mar": 0b01100001, ########################lequel prendre pour mar??
		"mav": 0b01100010,
		"mre": 0b01100011,
		"trd": 0b01100100,
		"trg": 0b01100101,
		"dbc": 0b11000000,
		"fbc": 0b11000001,
		"fin": 0b11111111
	}

	#utilisation du module getopt pour parse les arguments
	try:
		opts, args = getopt.getopt(sys.argv[1:], "ho:")
	except getopt.GetoptError:
		showUsage()

	if(len(args) != 1):
		showUsage()

	nomOutput = ""
	for opt, arg in opts:
		print(opt)
		print(arg)
		if opt == "-h":
			showUsage()
		elif opt == "-o":
			nomOutput = arg

	#ouverture du fichier a lire
	nomInput = args[0]
	fichierIn = open(nomInput, 'r')

	#ouverture du fichier a ecrire
	if(nomOutput == ""):
		nomOutput = nomInput + ".bin"
	fichierOut = open(nomOutput, 'w+b')

	#introduction
	print("\n    MNEM    BYTECODE    DONNEE    LIGNE")
	print("    -----------------------------------")
	erreur = False
	compteurLigne = 1
	tableauEcriture = []
	#boucle principale de lecture
	for ligne in fichierIn:
		####format du tableau mots[]: 0:mnemonique 1:operande 2:bytecode
		#on enleve les commentaires et caracteres inutiles
		mots = ((ligne.replace(';', ' ').split("//")[0]).split())
		if(len(mots) > 0):
			if(len(mots) < 2):
				mots.append(0)
			if mots[0] in opcodes.keys():
				#on ajoute le bytecode
				mots.append(opcodes[mots[0]])
				#on convertit les valeurs en int
				try:
					mots[1] = int(mots[1])
					mots[2] = int(mots[2])
					#on affiche le tout
					print("  - {}   - 0x{:02x}      - 0x{:02x}    - ligne {}".format(mots[0], mots[2], mots[1], compteurLigne))
					#on ajoute au tableau
					tableauEcriture.append(tuple(mots))
				except ValueError:
					print("  - Erreur ligne {}: operande non-numerique: {}".format(compteurLigne, mots[1]))
			else:
				print("  - Erreurligne {}: mnemonique non-reconnue: {}".format(compteurLigne, mots[0]))
				erreur = True
			
		compteurLigne += 1
	#verification des erreurs de lecture
	if(erreur):
		print("Lecture terminee avec status: Echec")
		sys.exit(3)
	else:
		print("Lecture terminee avec status: Succes")

	#on ecrit la taille
	taille = (len(tableauEcriture) * 2) + 2 #on ajoute 2 pour faire la meme erreur que dans le progmem original
	binTaille = "{:04x}".format(taille) #conversion au format 0x0000
	fichierOut.write(binascii.unhexlify(binTaille[0:2])) #high byte
	fichierOut.write(binascii.unhexlify(binTaille[2:4])) #low byte
	print("    Nombre d'octets dans le fichier binaire produit: {}".format(taille))
	#boucle principale d'ecriture
	for entree in tableauEcriture:
		fichierOut.write((entree[2]).to_bytes(1, byteorder='little')) #bytecode
		fichierOut.write((entree[1]).to_bytes(1, byteorder='little')) #operande

	#on ferme les fichiers
	fichierIn.close()
	fichierOut.close()

if __name__ == "__main__":
    main()