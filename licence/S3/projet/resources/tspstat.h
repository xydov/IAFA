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
#define MAXBUF 256 // taille du buffer de lecture des fichiers
#define NIL -1 // indique l'échec dans une fonction
#define NB_BALISES 12 // nombre max de balises de la ligne de commabde
// liste des codes pour les balises
#define BAL_F 0 // -f
#define BAL_T 1 // -t
#define BAL_V 2 // -v
#define BAL_O 3 // -o
#define BAL_PPV 4 //-ppv
#define BAL_BF 5 // -bf
#define BAL_BFM 6 // -bfm
#define BAL_RW 7 // -rw
#define BAL_2OPT 8 // -2opt
#define BAL_GA 9 // -ga
#define BAL_H 10 //-h
#define BAL_ZERO 11 // -nz no zéro

// SD pour lire le fichier d'instance TSPLIB
typedef struct instance_s {
   char name[TAILLENOM]; // nom de l'instance
   char type[TAILLENOM]; // type de l'instance
   int dimension; // nombre de sommets dans l'instance
   char EDGE_TYPE[TAILLENOM];
   double length; // longueur de la tournée (calcul)
   int **tabCoord; // tableau des coordonnées (x,y,marque=0 pas vu, n° ordre)
   double **matDist; // demie matrice des distances euclidiennes (calcul)
   int *tabTour; // tableau des villes formant la tournée (dans l'ordre) (calcul)
} instance_t;

// SD pour lire le fichier "tour" de TSPLIB
typedef struct tour_s {
  char name[TAILLENOM]; // nom de l'instance
  int dimension; // nombre de sommets dans l'instance
  double length; // longueur du tour (calculée ou lue)
  int *tour; // liste des noeuds de la tournée lus dans le fichier tour
} tour_t;

// variables externes
// permet d'éviter de se trainer les mêmes paramètres dans les sous-programmes
extern FILE * logfp; // fichier log
extern FILE * resfile; // fichier de résultats (CSV)
extern bool verbose_mode; // mode bavard
extern bool sans_zero; // avec ou sans zéro

// prototypes des sp en vrac à classer
void erreur(char * message); // affiche me message et fait un exit
int random_node(int min,int max); // donne un nb aléatoire entre min et max
void init_instance(instance_t *instance);
double dist_euclidienne(instance_t instance, int v1, int v2);
double tour_length_mat(instance_t instance,int *tabTour);
void swap (int *tab,int ind1,int ind2);
void renverse_tab(int *tab,int prem,int der);
void affiche_tab_int(int *tab,int dim, FILE *logfp);
void affiche_tab_char_hex(char *tab,int dim, FILE *logfp);
void affiche_tab_char(char *tab,int dim, FILE *logfp);
bool prefix(char *motif,char *buf);
int ** creer_mat_int(int nbRows,int nbCol);
int * creer_tab_int(int dim);
double ** creer_mat_dist(int dimension);
void dump_tour(tour_t tour);
void analyse_balises(int argc,char ** argv,int tab_arg[NB_BALISES]);
void hard_copy_tour(tour_t *t1,tour_t t2);
bool next_permutation(int *tab,int dim);
bool nextPermutation(int *array,int dim);
double tour_length(instance_t instance,int *tabTour,bool sans_zero);
int lecture_fichier(char * filename,instance_t *instance);
void compute_dist(instance_t *instance);
double brute_force_tsp(instance_t instance, tour_t *tournee, tour_t *pire,bool use_mat);
bool node_in_tour(int node,tour_t tour);
void init_tour(tour_t *tour);
void add_tail(int som,tour_t *tournee);
double init_tour_random(instance_t instance, int ville_depart, tour_t *tournee);
double swap_2opt(instance_t instance, tour_t *tournee,int ind1,int ind2);
double improve_2opt_syst(instance_t instance,tour_t *tournee,int ind1);
double all_2opt(instance_t instance,tour_t *tournee);
void verify_dist(instance_t instance);
double dist_mat(instance_t instance, int node1, int node2);
void print_help();
bool villes_adjacentes(tour_t tournee,int ind1,int ind2);
double init_tour_ppv(instance_t instance, int depart, tour_t *tournee);
void dump_instance(instance_t instance);
void dump_matrice_dist(instance_t instance);
void print_solution(char * methode,instance_t instance,tour_t t,double longueur,double tps);
#endif

