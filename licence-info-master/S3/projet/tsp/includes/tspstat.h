// header global pour le TSP
// vd-software 2019
#ifndef TSPSTAT_H
#define TSPSTAT_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#define TAILLENOM 32 // les noms sont limités à 32 caractères
#define MAXBUF 256   // taille du buffer de lecture des fichiers
#define NIL -1       // indique l'échec dans une fonction

// SD pour lire le fichier d'instance TSPLIB
typedef struct instance_s
{
  char name[TAILLENOM]; // nom de l'instance
  char comment[TAILLENOM];
  char type[TAILLENOM]; // type de l'instance
  int dimension;        // nombre de sommets dans l'instance
  char EDGE_TYPE[TAILLENOM];
  double length;    // longueur de la tournée (calcul)
  long **tabCoord;   // tableau des coordonnées (x,y,marque=0 pas vu, n° ordre)
  double **matDist; // demie matrice des distances euclidiennes (calcul)
  int *tabTour;     // tableau des villes formant la tournée (dans l'ordre) (calcul)
} instance_t;


extern bool sans_zero;    // avec ou sans zéro

#endif
