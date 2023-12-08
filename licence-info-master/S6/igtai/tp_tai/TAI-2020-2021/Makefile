# L3 Informatique - Informatique graphique, traitement et analyse d'images
# Bases du traitement et de l'analyse d'images
#
# Pour lancer les compilations, tapez :
# make
# Pour effacer tous les fichiers objets et executables, tapez :
# make clean

# Ne pas modifier ce fichier, sauf si l'option -Wpedantic n'est pas acceptée.
# Dans ce cas, la remplacer par -pedantic

CC=gcc
CFLAGS=-g -Wall -Wextra -std=c99 -Wpedantic
LDLIBS=-lm
RM=rm -f

# Fichiers objets
OBJECTS=limace.o \
        erreurs.o \
        tai.o \
        inversion.o \
        etalement.o \
        moyen.o \
        median.o \
        binarisation.o \
        erosion.o \
        dilatation.o \
        comparaison.o

# Fichiers exécutables
EXE=inversion etalement moyen median binarisation erosion dilatation comparaison

# Pour mettre à jour tous les exécutables
.PHONY: all
all: $(EXE)

# Dépendances non implicites des exécutables
OBJ=limace.o erreurs.o tai.o
inversion: $(OBJ)
etalement: $(OBJ)
moyen: $(OBJ)
median: $(OBJ)
binarisation: $(OBJ)
erosion: $(OBJ)
dilatation: $(OBJ)
comparaison: $(OBJ)


# Dépendances non implicites des objets
HEAD=limace.h erreurs.h tai.h
tai.o: $(HEAD)
inversion.o: $(HEAD)
etalement.o: $(HEAD)
moyen.o: $(HEAD)
median.o: $(HEAD)
binarisation.o: $(HEAD)
erosion.o: $(HEAD)
dilatation.o: $(HEAD)
comparaison.o: $(HEAD)

# Pour effacer les objets et les exécutables
clean:
	$(RM) $(OBJECTS) $(EXE)
