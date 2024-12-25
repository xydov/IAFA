/// \file test.c
/// \author Tarek Kunze
/// \date december 2019
/// \brief quelques fonction de test

#include "test.h"

bool is_array_random(int *nodes, int dimension)
{
    /// \brief teste si un tableau de noeuds contient uniquement des valeurs uniques
    /// \param[in, out] nodes : tableau des noeuds
    /// \param[in] instance : dimension du tableau
    /// \return true si le tableau est correct, 0 sinon
    for (int i = 0; i < dimension - 1; i++)
    {
        for (int j = i + 1; j < dimension; j++)
        {
            if (i != j && nodes[i] == nodes[j])
            {
                return false;
            }
        }
    }
    return true;
}