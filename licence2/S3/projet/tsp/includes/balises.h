#ifndef BALISES_H
#define BALISES_H

#include "tspstat.h"

#define NB_BALISES 12 // nombre max de balises de la ligne de commabde

// liste des codes pour les balises
#define BAL_F 0     // -f
#define BAL_T 1     // -t
#define BAL_V 2     // -v
#define BAL_O 3     // -o
#define BAL_PPV 4   //-ppv
#define BAL_BF 5    // -bf
#define BAL_BFM 6   // -bfm
#define BAL_RW 7    // -rw
#define BAL_2OPT 8  // -2opt
#define BAL_GA 9    // -ga
#define BAL_H 10    //-h
#define BAL_ZERO 11 // -nz no zéro


void init_balises(int *balises);
void anhiliation_bal(int ind_bal, int *bal_arr);
void print_help();
int recherche_chaine(int argc, char **argv, char *ch);
void analyse_balises(int argc, char **argv, int tab_arg[NB_BALISES]);
#endif