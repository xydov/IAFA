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


/* Traduction indice/coordonnees */
T_coordonnees obtenirCoords(int indice);/* Retourne les coordonnees de la case a partir de son indice dans le sudoku */
int obtenirIndice(T_coordonnees coords);/* Retourne l'indice d'une case dans le sudoku a partir de ses coordonnees */
T_coordonnees debutRegion(int indiceRegion);/* Retourne les coordonnees de la premiere case (en haut a gauche) d'une region a partir de l'indice de cette region */
int indiceRegion(T_coordonnees coords);/* Retourne l'indice de la region a laquelle appartient la case ayant ces coordonnees*/

/* Lire une grille et initialiser un sudoku */
T_sudoku lireSudoku(char* chemin);
void initialiserSudoku(T_sudoku* s);

/* Affichage de grilles */
void afficherSudoku(T_sudoku s); /* Afficher un sudoku: 9 lignes de 9 entiers separes par des tabulations (\t)*/

/* Recherche et suppression de candidats dans une case */
int rechercherValeur(int val, T_case c);/* Renvoie l'indice de val dans le tableau de candidats de c. Si l'indice n'est pas present, renvoie c.n_candidats */
void supprimerValeur(int ival, T_case* pc);/* ival est l'indice de la valeur a supprimer, on cosidere que la valeur a supprimer est presente dans les candidats de la case */

/* Implementation des regles */
int R1_case(T_case* pc); /* Applique R1 sur la case */
int R1_sudoku(T_sudoku* ps); /* Applique R1 sur toutes les cases du sudoku, renvoie 1 si une modification a eu lieu, 0 sinon */
int R2_case(int indCase, T_sudoku* ps); /* Applique R2 sur la case. */
int R2_sudoku(T_sudoku* ps); /* Applique R2 sur toutes les cases du sudoku, renvoie 1 si une modification a eu lieu, 0 sinon */
int R3_case(int indCase, T_sudoku* ps); /* Applique R3 sur la case. */
int R3_sudoku(T_sudoku* ps); /* Applique R3 sur toutes les cases du sudoku, renvoie 1 si une modification a eu lieu, 0 sinon */
int bruteForce(T_sudoku* ps);/* Bonus */

/* Verification du resultat */
int valide(T_sudoku s); /* Renvoie 1 si la grille est complete et valide */
int verifResultat(T_sudoku initialS,T_sudoku s); /* Renvoie 1 si le sudoku est correct, et correspond bien au probleme initial */


/* Resolution */
void resoudreSudoku(char* chemin);
void resoudreSudokuCharge(int** ps,int nb);

#endif
