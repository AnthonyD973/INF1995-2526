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
GENDIR=../gen

# Emplacement de la librairie a generer
LIBDIR=../lib

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



####################################################
#####         Configuration terminee           #####
#####                                          #####
#####  Le reste de cette section contient les  #####
##### details d'implementation vous permettant #####
##### de mieux comprendre le fonctionnement de ##### 
#####   ce Makefile en vue de sa modification  #####
####################################################



####### variables #######

#compilateur utilise
CC=avr-gcc
#archiveur utilise
AR=avr-ar
#pour copier le contenu d'un fichier objet vers un autre
OBJCOPY=avr-objcopy
#pour permettre le transfert vers le microcontroleur
AVRDUDE=avrdude
#pour supprimer les fichiers lorsque l'on appel make clean
REMOVE=rm -rf
# HEXFORMAT -- format pour les fichiers produient .hex
HEXFORMAT=ihex


	
####### Variables pour la creation d'une librairie #######

# Ajout du prefix -l pour l'utilisation dans les commandes
LIBSCMD=$(patsubst %,-l%,$(LIBS))

# Ajout du prefix -L pour l'utilisation dans les commandes
LIBSPATHSCMD=$(patsubst %,-L%,$(LIBS_PATHS))

####### Options de compilation #######

# Flags pour le compilateur en C
CFLAGS=-I. -MMD $(patsubst %,-I%,$(INC)) \
	-g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-fpack-struct -fshort-enums \
	-funsigned-bitfields -funsigned-char \
	-Wall

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions

# Linker pour lier les librairies utilisees
LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)

# Flags pour l'archiveur
ARFLAGS=-crs



####### Cible (Target) #######

#Nom des cibles par defaut
TRG=$(GENDIR)/$(PROJECTNAME).out
HEXROMTRG=$(GENDIR)/$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(GENDIR)/$(PROJECTNAME).ee.hex
LIBTRG=$(addprefix lib, $(addsuffix .a, $(PROJECTNAME)))



####### Definition de tout les fichiers objets #######

# Cette fonction permet de differencier les fichiers .c
# des fichiers .cpp
# Fichier C
CFILES=$(strip $(filter %.c, $(addprefix $(SRCDIR)/,$(PRJSRC))))
# Fichier C++
CPPFILES=$(strip $(filter %.cpp, $(addprefix $(SRCDIR)/,$(PRJSRC))))

# Liste de tout les fichiers objet que nous devons creer
OBJDEPS=$(patsubst %.c,$(GENDIR)/%.o,$(strip $(filter %.c, $(PRJSRC)))) \
	$(patsubst %.cpp,$(GENDIR)/%.o,$(strip $(filter %.cpp, $(PRJSRC))))
	
# Pour plus d'information sur cette section, consulter :
# http://bit.ly/257R53E	
# Les fonctions $(filter pattern…,text) &
# $(patsubst pattern,replacement,text) sont pertinentes

####### Creation des commandes du Makefile ####### 

# Creation des cibles Phony (Phony Target)
# En plus de la commande make qui permet de compiler
# votre projet, vous pouvez utilisez les commandes
# make all, make install et make clean
.PHONY: all install clean auto lib

# Make all permet simplement de compiler le projet
#
all: $(TRG)
	echo $(TRG);

# Implementation de la cible
$(TRG): $(GENDIR) $(OBJDEPS)
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) \
	-lm $(LIBSCMD) $(LIBSPATHSCMD)

$(GENDIR):
	mkdir $(GENDIR)

# Production des fichiers object
# De C a objet
$(GENDIR)/%.o: $(SRCDIR)/%.c $(GENDIR)
	$(CC) $(CFLAGS) -c $< -o $@
# De C++ a objet
$(GENDIR)/%.o: $(SRCDIR)/%.cpp $(GENDIR)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

# Verification des dependances (header dependencies)
-include $(GENDIR)/*.d

# Pour plus d'information sur cette section, consulter:
# http://bit.ly/2580FU8

# Production des fichiers hex a partir des fichiers elf
$(GENDIR)/%.hex: $(GENDIR) $(GENDIR)/%.out
	$(OBJCOPY) -j .text -j .data \
		-O $(HEXFORMAT) $< $@

# La cible lib permet de produire une librairie .a
# que l'on peut reutiliser ailleur
lib: $(LIBTRG)

$(LIBTRG): $(GENDIR) $(OBJDEPS)
	$(AR) $(ARFLAGS) $@ $(OBJDEPS)

# Make install permet de compiler le projet puis
# d'ecrire le programme en memoire flash dans votre
# microcontroleur. Celui-ci doit etre branche par cable USB
install: $(HEXROMTRG)
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID) \
	-p $(MCU) -P -e -U flash:w:$(HEXROMTRG)

# Make clean permet d'effacer tout les fichiers generes
# lors de la compilation
clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) $(GENDIR)/*.d $(GENDIR)/* $(GENDIR)
	

# Execute, dans l'ordre, un 'make all' pour compiler ce qu'il
# y a a compiler, un 'make install' pour transferer le programme
# compiles et un 'make clean' pour que les ficher generes ne
# soient pas transferes dans l'entrepot git par erreur.
auto: all install clean

# Construit la librairie puis nettoie
libauto: lib clean

# Pour plus d'information sur les phony target, consulter:
# http://bit.ly/1WBQe61

# De plus, pour mieux comprendre les makefiles et 
# leur fonctionnement, consulter la documentation de GNU Make:
# http://bit.ly/23Vpk8s

# Finalement, ce tutoriel en ligne constitut une bonne 
# introduction au Makefile:
# http://bit.ly/1XvxsN3

#####                    EOF                   #####
