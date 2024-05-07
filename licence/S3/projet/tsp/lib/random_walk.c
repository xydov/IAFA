/// \file random_walk.c
/// \author Tarek Kunze
/// \date december 2019
/// \brief implementation de l'algo de random walk

#include "random_walk.h"

int next_random(instance_t *instance, int *nodes, int zeiger)
{
    /// \brief génère un nombre random, différent de celui de la liste des noeuds
    /// \param[in] instance : instance du problème
    /// \param[in, out] nodes : tableau des noeuds
    /// \param[in] zeiger : indice de l'élément a ne pas traiter
    /// \return un nombre random
    int random_node;
    do
    {
        random_node = rand() % instance->dimension;
    } while (is_in_array(random_node, nodes, instance->dimension) || random_node == nodes[zeiger]);

    return random_node;
}

double random_walk(instance_t *inst, int *nodes)
{
    /// \brief exécute l'algo de random walk
    /// \param[in] inst : instance du problème
    /// \param[in, out] nodes : tableau des noeuds
    /// \return la distance trouvée
    int dimension = inst->dimension;

    double current_distance;

    nodes[0] = 0;
    for (int i = 0; i < dimension - 1; i++)
    {
        nodes[i + 1] = next_random(inst, nodes, i);
    }
    if (is_array_random(nodes, dimension))
    {
        printf("[TEST] - Array is Random\n");
    }

    current_distance = array_distance(nodes, *inst);

    return current_distance;
}