import sys
import os
import re

if len(sys.argv) <= 1:
	print('No argument')
	sys.exit(1)

print('Current working directory: ' + os.getcwd())

nomFichier = "Makefile"
nomTemp = "TempMakefile"
if os.path.isfile(nomFichier):
	fin = open(nomFichier, 'r')
else:
	print('Le Makefile est introuvable')
	sys.exit(2)
fout = open(nomTemp, 'w')

for ligne in fin:
	if re.match(r"^PRJSRC=.*", ligne, re.DOTALL):
		print('Ligne trouvee')
		ligne = 'PRJSRC=' + sys.argv[1] + "\n\n"
	fout.write(ligne)
print('Le nouveau Makefile est ecrit')

os.remove(nomFichier)
os.rename(nomTemp, nomFichier)

print('All done m8')
sys.exit(0)
