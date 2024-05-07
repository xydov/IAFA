#ifndef DISPLAY_H
#define DISPLAY_H

#include "tspstat.h"
#include "tools.h"

int to_csv_file(char *filename, instance_t instance);
void print_entete(instance_t *instance, char *filename);
void print_instance_csv(instance_t *instance);
void print_methode(bool *al_an, char *m_name, double final_length, double time, int *final_nodes, int dimension);
void print_methode_csv_file(bool *al_an, char *m_name, double final_length, double time, int *final_nodes, int dimension, char *filename);
void print_bf(bool *al_an, double final_length, double time, int *final_nodes, int *worst_nodes, int dimension, instance_t inst);
void print_bf_csv_file(bool *al_an, double final_length, double time, int *final_nodes, int *worst_nodes, int dimension, char *filename, instance_t inst);

#endif