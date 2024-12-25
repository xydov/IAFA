/// \file bruteforce.c
/// \author Tarek Kunze
/// \date december 2019
/// \brief Bruteforce implementation lib

#include <math.h>
#include "bruteforce.h"

double brute_force_tsp(instance_t *instance, bool use_mat, int *nodes, int *worst_nodes)
{
    /// \brief considère toute les permutations de la tournée initiale et garde la plus courte
    /// \brief et la pire, le point n°1 est fixe
    /// \param [in] instance : pour les points et coordonées
    /// \param [in] use_mat : flag pour indiquer si on veut utiliser la matrices des distances
    /// \param [in] nodes : tableau des noeuds

    //  Variables
    int dimension = instance->dimension;

    int best_nodes[dimension];  // best arr
    
    init_array(best_nodes, dimension);
    init_array(worst_nodes, dimension);
    init_array(nodes, dimension);

    double current_distance = array_distance(nodes, *instance);

    double best_distance = current_distance;
    double worst_distance = current_distance;

    if (use_mat)
    {
        printf("Matrices des distances:\n");
    }
    else
    {
        do
        {
            // calcul de la longeur du nvx segments
            current_distance = array_distance(nodes, *instance);

            if (current_distance <= best_distance)
            {
                copy_array(nodes, best_nodes, dimension);
                best_distance = current_distance;
            }
            if (current_distance > worst_distance)
            {
                copy_array(nodes, worst_nodes, dimension);
                worst_distance = current_distance;
            }
            
        } while (next_permutation(nodes + 1, dimension));
    }

    copy_array(best_nodes, nodes, dimension);
    return best_distance;
}

bool next_permutation(int *array, int dim)
{
    /// \brief Computes the next lexicographical permutation of the specified
    /// \brief array of integers in place, returning a Boolean to indicate
    /// \brief whether a next permutation existed. (Returns false when the
    /// \brief argument is already the last possible permutation.)
    /// \param [in] array : tableau des noeuds
    /// \param [in] dim : dimension du tableau
    // Find non-increasing suffix
    dim--;
    if (dim == 0)
    {
        return false;
    }
    size_t i = dim - 1;
    while (i > 0 && array[i - 1] >= array[i])
    {
        i--;
    }
    if (i == 0)
    {
        return false;
    }

    // Find successor to pivot
    size_t j = dim - 1;
    while (array[j] <= array[i - 1])
    {
        j--;
    }
    int temp = array[i - 1];
    array[i - 1] = array[j];
    array[j] = temp;

    // Reverse suffix
    j = dim - 1;
    while (i < j)
    {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        i++;
        j--;
    }
    return true;
}