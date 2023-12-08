#ifndef TOOLS_H
#define TOOLS_H

#include "tspstat.h"

long **create_long_mat(int nbRows, int nbCol);
void copy_array(int* array_source, int* array_destination, int dimension);
void init_array(int *array, int dimension);
double array_distance(int *node_array, instance_t reference_instance);
double euclidean_distance(long x1, long y1, long x2, long y2);
int is_in_array(int nb, int *array, int dimension);
void swap_2opt(int *tab, int ind1, int ind2);
bool compare_slices(int *array_1, int start_1, int end_1, int *array_2, int start_2, int end_2, int dimension);
int *rev_array(int *array, int d, int f);
int *create_array_int(int dimension);



void erreur(char *message);
double **creer_mat_dist(int dimension);
void swap(int *tab, int ind1, int ind2);/// \brief inverse le contenu des cases ind1 et ind2 dans tab

#endif