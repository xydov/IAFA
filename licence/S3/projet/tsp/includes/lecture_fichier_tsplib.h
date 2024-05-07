#ifndef LECTUREFICHIER_H
#define LECTUREFICHIER_H

#include "tspstat.h"
#include "tools.h"
#include "display.h"

#define NB_BANIERES 8


bool prefix(char *motif, char *buf);
void get_first_word(char *line, char *first_word);
void get_field_value(char *line, char *field_value);
int lecture_fichier(char *filename, instance_t *instance);


#endif
