#ifndef OPT_H
#define OPT_H

#include "tspstat.h"
#include "tools.h"

#define max(a, b) (a >= b ? a : b)
#define min(a, b) (a <= b ? a : b)

bool onSegment(int p, int q, int r, instance_t inst, int *nodes);
long orientation(int p, int q, int r, instance_t inst, int *nodes);
bool do_intersect(int p1, int q1, int p2, int q2, instance_t instance, int *nodes);
double two_opt(int *nodes, instance_t instance);

#endif