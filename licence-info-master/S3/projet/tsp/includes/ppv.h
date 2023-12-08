#ifndef PPV_H
#define PPV_H

#include "tspstat.h"
#include "tools.h"

int is_in_array(int nb, int *array, int dimension);
int next_v(instance_t *instance, int *nodes, int zeiger);
double ppv(instance_t *inst, int *nodes);

#endif