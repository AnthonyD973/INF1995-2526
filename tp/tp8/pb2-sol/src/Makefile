
# Nom de votre projet
# (utilisez un seul mot, exemple: 'monprojet')
PROJECTNAME= linkTest

# Fichiers sources
# (Listez tous les fichiers a compiler, ex: 'tp1.c, tp2.cpp'):
# Utilisez le suffixe .cpp pour les fichiers C++
PRJSRC= main.cpp

TRG=$(PROJECTNAME)

# Inclusions additionnels (ex: -I/path/to/mydir)
INCL= -I../lib -L../lib

# Libraires a lier (ex: -lmylib)
LIBS= -lTest

CCR = avr-gcc

# Linker pour lier les librairies utilisees
LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)

EXT = -o

SUFF = out

# Make all permet simplement de compiler le projet
#
#all: $(TRG)

# Implementation de la cible
#$(TRG): $(PRJSRC)
#	$(CC) $(INC) -o $@ $< $(LIBS)



-include ../Makefile_common.txt


