# Nom de votre projet
# (utilisez un seul mot, exemple: 'monprojet')
PROJECTNAME= libTest

# Fichiers sources
# (Listez tous les fichiers a compiler, ex: 'tp1.c, tp2.cpp'):
# Utilisez le suffixe .cpp pour les fichiers C++
PRJSRC= defaultISR.cpp engine.cpp led.cpp lib.cpp pinPosition.cpp timer.cpp uart.cpp ram.cpp

SUFF = a

#compilateur utilise
CCR=avr-ar rcs

LDFLAGS=

INCL =

LIBS =

EXT =

####### Definition de tout les fichiers objets #######

# Cette fonction permet de differencier les fichiers .c
# des fichiers .cpp
# Fichier C
#CFILES=$(filter %.c, $(PRJSRC))
# Fichier C++
#CPPFILES=$(filter %.cpp, $(PRJSRC))

# Liste de tout les fichiers objet que nous devons creer
#OBJDEPS=$(CFILES:.c=.o) \
#	$(CPPFILES:.cpp=.o)

# Make all permet simplement de compiler le projet
#
#all: $(TRG)

# Implementation de la cible
#$(TRG): $(OBJDEPS)
#	avr-ar rcs $@ $^

# Production des fichiers object
# De C a objet
#%.o: %.c
#	$(CC) $(CFLAGS) -c $<
# De C++ a objet
#%.o: %.cpp
#	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<


-include ../Makefile_common.txt
