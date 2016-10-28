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


#####      Details specifique a la cible       #####
#####  Vous devez les adapter a votre projet   #####

# Nom du microcontroleur cible
# (exemple: 'at90s8515')
MCU=atmega324pa

# Nom de votre projet
# (utilisez un seul mot, exemple: 'monprojet')
PROJECTNAME=robot

# Fichiers sources
# (Listez tous les fichiers a compiler, ex: 'tp1.c tp2.cpp'):
# Utilisez le suffixe .cpp pour les fichiers C++
PRJSRC=main.cpp

# Emplacement ou se trouve les fichiers sources (ex: ../src ./main . )
SRCDIR=.

# Emplacement de stockage temporaire des fichiers generes
# lors de la compilation (par defaut, creer un dossier 'gen' dans le
# repertoire courant)
GENDIR=gen

# Inclusions additionnels separes par des espaces
# (L'emplacement des fichiers .h utilises dans les fichers sources)
# (ex: /path/to/mydir /path/to/dir2) (utilisation avec le prefix -I)
INC=../lib

# Librairies a lier (ex: mylib) (utilisation avec le prefix -l dans
# la generation de l'executable final)
LIBS=robot

# Chemins vers les dossiers contenants les librairies
# (ex: /path/to/libdir) (utilisation avec le prefix -L dans
# la generation de l'executable final)
LIBS_PATHS=../lib

# Niveau d'optimization
# Utilisez s (size opt), 1, 2, 3 ou 0 (off)
OPTLEVEL=s

# Programmer ID - Ne pas changer 
# Liste complete des IDs disponible avec avrdude
AVRDUDE_PROGRAMMERID=usbasp



-include ../Makefile_common.txt
