#ifndef _EX_H_
#define _EX_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h> /* types implémentés différemment selon la version d’Unix */
#include <sys/stat.h> /* constantes symboliques pour les droits d’accès */
#include <fcntl.h> /* constantes symboliques pour les différents types d’ouverture */

#define LONG_MAX_NOM 20

/* Code de retour d'erreur */
#define ERROR_READING 2
#define ERROR_CLOSING 3
#define ERROR_FICHES  4

typedef struct 
{
    char Nom[LONG_MAX_NOM + 1];
    int Age;
    int nbEnfants;
}Infos;

int creation(char *NomFichier);

#endif