#ifndef GA_H
#define GA_H

#include "tspstat.h"
#include "tools.h"
#include "random_walk.h"
#include "2opt.h"

typedef struct indices_s
{
    int deb;
    int fin;
} indices_t;

typedef struct sub_tour_s
{
    int dimension;
    indices_t *tabIndices;
} sub_tour_t;


typedef struct tour_s
{
    double length;
    int *nodes;
    // char name[TAILLENOM]; // nom de l'instance
    // int dimension;        // nombre de sommets dans l'instance
} tour_t;

typedef struct pool_s
{
    int nodes_dimension;
    int pool_size;
    tour_t *array;
} pool_t;


tour_t *create_array_tour(int dimension);
indices_t *create_array_indices(int dimension);
void two_random_numbers(int *a, int *b, int dimension);
void edge_destruction(tour_t *t_parent1, tour_t *t_parent2, tour_t *tfille, int dimension);
void mutation();
void dpx(int *t_parent1, int *t_parent2, int *tfille, int *tfille_fin, int dimension);
double ga(instance_t instance, float taux_mut, int n_individus, int n_generations);


#endif