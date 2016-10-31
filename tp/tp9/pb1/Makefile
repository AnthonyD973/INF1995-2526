# -------------------
# |    VARIABLES    |
# |   UTILISATEUR   |
# -------------------

# Nom du projet.
PRJ_NAME=NotreSuperProgramme

# Fichiers à compiler.
PRJ_SRC=main.cpp


OPT_LVL=s

# ------------------- 
# |    VARIABLES    |
# |     LOCALES     |
# -------------------

CC=g++
CC_FLAGS=-Wall

LD=ld
LD_FLAGS=

OBJDEPS=$(strip $(filter %.o, %.cpp, $(PRJSRC)) )

#-------------------
#|      CIBLES     |
#-------------------

.PHONY: all install clean auto

# Compilation
all:
echo ---ALL FAIT---

# Distribution
install:
echo ---INSTALL FAIT---

# Nettoyage
clean:
echo ---CLEAN FAIT---

# "all of above"
auto: all install clean
echo ---AUTO FAIT---