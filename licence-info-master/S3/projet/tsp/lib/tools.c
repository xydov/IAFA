/// \file tools.c
/// \author Tarek Kunze
/// \date december 2019
/// \brief fonctions diverses

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "tools.h"

long **create_long_mat(int nbRows, int nbCol)
{
    /// \brief crée une matrice de long
    /// \param[in] nbRows : nombre de ligne
    /// \param[in] nbColtance : nombre de colonne
    /// \return un pointeur de pointeur sur tableau de long
    long **mat = malloc(nbRows * sizeof(long *));
    if (mat == NULL)
    {
        printf("Problème d'allocation create_long_mat !");
        exit(1);
    }
    int j;
    for (int i = 0; i < nbRows; i++)
    {
        mat[i] = malloc(nbCol * sizeof(long));
        if (mat[i] == NULL)
        {
            printf("Problème d'allocation create_long_mat !");
            exit(1);
        }
    }
    return mat;
}

void copy_array(int *array_source, int *array_destination, int dimension)
{
    /// \brief copy une array dans une seconde array de même dimension
    /// \param[in] array_source : nombre de ligne
    /// \param[in] array_destination : nombre de colonne
    /// \param[in] dimension : dimension du tableau
    for (int i = 0; i < dimension; i++)
    {
        array_destination[i] = array_source[i];
    }
}

void init_array(int *array, int dimension)
{
    /// \brief initialise une array avec les bon noud de départs
    /// \param[in, out] array : le tableau
    /// \param[in] dimension : dimension du tableau
    for (int i = 0; i < dimension; i++)
    {
        array[i] = i;
    }
}

double array_distance(int *node_array, instance_t reference_instance)
{
    /// \brief calcule la distance cyclique d'un tableau de noeud
    /// \param[in] node_array : tableau de noeud
    /// \param[in] reference_instance : instance du problème
    /// \return la distance du problème
    int taille = reference_instance.dimension;
    double distance = 0;
    for (int i = 0; i < taille; i++)
    {
        // printf("indice i: %d | indice in node_array: %d\n", i, node_array[i]);
        // printf("long: %ld\n", reference_instance.tabCoord[node_array[i]][0]);
    }

    for (int i = 0; i < taille - 1; i++)
    {

        distance += euclidean_distance(reference_instance.tabCoord[node_array[i]][0], reference_instance.tabCoord[node_array[i]][1],
                                       reference_instance.tabCoord[node_array[i + 1]][0], reference_instance.tabCoord[node_array[i + 1]][1]);
        // printf("i %d\n", i);
    }
    distance += euclidean_distance(reference_instance.tabCoord[node_array[0]][0], reference_instance.tabCoord[node_array[0]][1],
                                   reference_instance.tabCoord[node_array[taille - 1]][0], reference_instance.tabCoord[node_array[taille - 1]][1]);
    return distance;
}


double euclidean_distance(long x1, long y1, long x2, long y2)
{
    /// \brief calcule la distance euclidienne entre 2 points de coord x, y
    /// \param[in] x1 : x1
    /// \param[in] x2 : x2
    /// \param[in] y1 : y1
    /// \param[in] y2 : y2
    /// \return la distance
    return sqrt((double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int is_in_array(int nb, int *array, int dimension)
{
    /// \brief regarde si un nombre existe dans un tableau
    /// \param[in] nb : nombre a chercher dans le tableau
    /// \param[in] array : tableau de noeud
    /// \param[in] dimension : dimension du tableau
    /// \return 1 si dans le tableau, 0 si non
    for (int i = 0; i < dimension; i++)
    {
        if (array[i] == nb)
        {
            return 1;
        }
    }
    return 0;
}

void swap_2opt(int *tab, int ind1, int ind2)
/// \brief inverse le contenu de ind1 jusqu'a ind2
/// \param[in,out] tab : le tableau
/// \param[in] ind1 : premier indice
/// \param[in] ind2 : deuxième indice
/// \post *tab[ind1]=*TAB[ind2] && *tab[ind2]=*TAB[ind1]
{
    int temp;
    while (ind1 < ind2)
    {
        temp = tab[ind1];
        tab[ind1] = tab[ind2];
        tab[ind2] = temp;
        ind1++;
        ind2--;
    }
}

bool compare_slices(int *array_1, int start_1, int end_1, int *array_2, int start_2, int end_2, int dimension)
{
    /// \brief compare 2 tableau entre des bornes définies
    /// \param[in] array_1 : 1er tableau
    /// \param[in] start_1 : début 1er tab
    /// \param[in] end_1 : fin 1er tab
    /// \param[in] array_2 : 2eme tableau
    /// \param[in] start_2 : début 2eme tab
    /// \param[in] end_2 : fin 2eme tab
    /// \param[in] dimension : dimension du tableau
    /// \return true si tab 1 == tab 2
    bool equal = false;
    while (array_1[start_1] == array_2[start_2] && start_1 <= end_1 && start_2 <= end_2)
    {
        equal = true;
        start_1++;
        start_2++;
    }
    return equal;
}

int *rev_array(int *array, int d, int f)
{
    /// \brief reverse le contenu du tableau entre les indices d et f
    /// \param[in] array : le tableau à modifier
    /// \param[in] d : indice de début
    /// \param[in] f : indice de fin
    /// \return pointeur sur le tableau modifié
    int ind;
    int dim = d - f + 1;

    for (ind = 0; ind < dim / 2; ind++)
    {
        swap(array, d + ind, f - ind);
    }
    return array;
}

int *create_array_int(int dimension)
{
    /// \brief crée une liste d'entier de facon sûre
    /// \param[in] dimension : dimension du tableau
    /// \return pointeur sur tableau
    int *ar = malloc(dimension * sizeof(long *));
    if (ar == NULL)
    {
        printf("Problème d'allocation create_array_int !");
        exit(1);
    }

    return ar;
}

/******************* ***********************/
/******************* ***********************/
/******************* ***********************/

void erreur(char *message)
{
    /// \brief imprime à l'écran un message d'erreur (chaîne de caractères)
    /// \brief le message est sensé être composé du nom du sous-programme+" : "+message d'erreur
    /// \param[in] message : le message à imprimer
    printf("*** ERREUR : %s ***\n", message);
    exit(1);
}

int **creer_mat_int(int nbRows, int nbCol)
{
    int **tab = (int **)malloc(nbRows * sizeof(int *));
    for (int i = 0; i < nbRows; i++)
        tab[i] = (int *)malloc(nbCol * sizeof(int));
    return tab;
}

double **creer_mat_dist(int dimension)
{
    /// \brief crée la matrice carrées des distances = tab dynamique triangulaire
    /// \brief chaque ligne a une case de moins que la précédente
    double **tab = (double **)malloc(dimension * sizeof(double *));
    for (int i = 0; i < dimension; i++)
        tab[i] = (double *)malloc(dimension * sizeof(double));
    dimension--;
    return tab;
}

void swap(int *tab, int ind1, int ind2)
/// \brief inverse le contenu des cases ind1 et ind2 dans tab
/// \param[in,out] tab : le tableau
/// \param[in] ind1 : premier indice
/// \param[in] ind2 : deuxième indice
/// \post *tab[ind1]=*TAB[ind2] && *tab[ind2]=*TAB[ind1]
{
    int temp;
    temp = tab[ind1];
    tab[ind1] = tab[ind2];
    tab[ind2] = temp;
}
