/****************************************************************
*  Lecture de variables de configuration à partir d'un fichier *
*                                                              *
* E. Lavinal - Université de Toulouse III - Paul Sabatier      *
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

#define LIGNE_MAX 80

int lecture_fichier_conf(char * param_conf, char * valeur_conf) {

    FILE *fichier = NULL;
    char ligne[LIGNE_MAX];
    int trouve = 0;

    fichier = fopen(FICHIER_CONF, "r");
    if (fichier == NULL) {
        perror("[Config] Problème ouverture fichier de configuration.\n");
        exit(1);
    }

    /* fgets(char[] dest, int size, FILE* stream); */
    while ( !trouve && fgets(ligne, sizeof(ligne), fichier) ) {

        if (ligne[0] != '#') {
            /* printf("ligne : %s", ligne); */
            if ( strncmp(ligne, param_conf, strlen(param_conf)) == 0 ) {
                strcpy(valeur_conf, &ligne[strlen(param_conf)+1]);
                /* on supprime le '\n' à la fin de la chaine : */
                valeur_conf[strlen(valeur_conf)-1] = '\0';
                trouve = 1;
            }
        }
    }
    fclose(fichier);

    return trouve;
}

void conf_fichier_emission(char * fichier_emission) {

    if ( !lecture_fichier_conf(FICHIER_IN, fichier_emission) )
    /* nom de fichier par défaut... */
    strcpy(fichier_emission, "in.txt");
}

void conf_fichier_reception(char * fichier_reception) {

    if ( !lecture_fichier_conf(FICHIER_OUT, fichier_reception) )
        /* nom de fichier par défaut... */
        strcpy(fichier_reception, "out.txt");
}

float conf_proba_perte(int role) {

    char valeur_config[8];
    int succes;
    float proba = 0;

    if (role == 0) /* emission */
        succes = lecture_fichier_conf(PROBA_PERTE_E, valeur_config);
    else /* reception */
        succes = lecture_fichier_conf(PROBA_PERTE_R, valeur_config);

    if (succes) proba = atof(valeur_config);

    return proba;
}

float conf_proba_erreur(int role) {

    char valeur_config[8];
    int succes;
    float proba = 0;

    if (role == 0) /* emission */
        succes = lecture_fichier_conf(PROBA_ERREUR_E, valeur_config);
    else /* reception */
        succes = lecture_fichier_conf(PROBA_ERREUR_R, valeur_config);

    if (succes) proba = atof(valeur_config);

    return proba;
}
