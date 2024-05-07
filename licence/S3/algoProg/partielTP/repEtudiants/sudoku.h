#ifndef SUDOKU_H
#define SUDOKU_H
#include <stdio.h>
#include <assert.h>


typedef struct
{
  int val; /* Valeur de la case (0 si vide) */
  int n_candidats; /* Nombre de candidats possibles. Lorsqu'une valeur est choisie pour une case, n_candidat doit etre mis a 0. */
  int candidats[9]; /* Liste de candidats */
} T_case;

typedef struct
{
  T_case grille[81]; /* Vecteur de 81 cases */
} T_sudoku;

typedef struct
{
  int ligne;
  int colonne;
} T_coordonnees;

T_coordonnees coord_debut_region(int n_region);
int num_case(T_coordonnees c);

/* Info */

int maxCandidatRegion(T_sudoku s, int indiceRegion); /* Renvoie le maximum des valeurs des candidats restants dans les cases d'une region */

/* Transposee d'une grille */
void transposerSudoku(T_sudoku* s_initial); /* calcule la transposee de s_initial en place */

void insert_value(T_case *c, int value);
int value_in_cand(T_case *c, int value);
void ajouterCandidat(T_case* s_case, int value); /* Si value n'est pas un candidat pou la case, ajoute val à la liste des candidats. Si la case n'a plus de candidat, remet sa valeur a 0 et ajoute 2 candidats: value ainsi que l'ancienne valeur de la case */


#endif
