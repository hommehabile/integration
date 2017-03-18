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
preparedFilename = ''.join(filename.split(".")[0:-1]) + "NoMetadata.wav"
fileOut = open(preparedFilename, 'w+b')
print("File {0} opened".format(preparedFilename))

#on trouve la fin des finMetadata
nb = 2000
fileStart = fileIn.read(nb)
finMetadata = fileStart.find('\x64\x61\x74\x61') 
if finMetadata is -1:
    print("End of metadata not in the first {0} bytes".format(nb))
    sys.exit(5)
finMetadata += 4 #pour etre a la fin
print("Number of bytes of metadata: {0}".format(finMetadata))

#on copie tout le fichier sauf les matadata
fileIn.seek(finMetadata, 0)
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
