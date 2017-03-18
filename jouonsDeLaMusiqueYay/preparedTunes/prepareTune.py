#usr/bin/bash

import sys, os.path
import binascii
from math import pow

def showUsage():
	print("usage: python prepareTune.py <path to wav file>\n")

if len(sys.argv) != 2: #test du nombre d'arguments
	showUsage()
	sys.exit(2)

filepath = sys.argv[1]
filename = os.path.basename(filepath)
if not filename.lower().endswith('.wav'): #test du type de fichier
	showUsage()
	print("Not a wav file: {0}\n".format(filename))
	sys.exit(3)

if not os.path.isfile(filepath): #test de l'existence sur fichier
	showUsage()
	print("File does not exist\n")
	sys.exit(4)

#ouverture des fichiers
fileIn = open(filepath, 'r+b')
print("File {0} opened".format(filename))
fileSize = os.path.getsize(filepath)
print("Original file size: {0} bytes, Hex: {1}".format(fileSize, hex(fileSize)))
preparedFilename = ''.join(filename.split(".")[0:-1]) + "_prepared.wav"
fileOut = open(preparedFilename, 'w+b')
print("File {0} opened".format(preparedFilename))

#on insert la taille sur 32 bits au debut du fichier
taille = fileSize-44
chaine = '{:08x}'.format(taille)
tab = (chaine[0:2], chaine[2:4], chaine[4:6], chaine[6:8])
for i in range(4):
	temp = binascii.unhexlify(tab[i])
	fileOut.write(temp)

#on copie tout le fichier sauf les 44 premiers octets
fileIn.seek(44, 0)
for byte in fileIn:
	fileOut.write(byte)

#on ferme les fichiers
fileIn.close()
fileOut.close()
print("Files closed")

#on mesure la taille du fichier final
preparedFileSize = os.path.getsize(preparedFilename)
print("Prepared file size: {0} bytes, Hex: {1}".format(preparedFileSize, hex(preparedFileSize)))
	
fileIn.close()
fileOut.close()
