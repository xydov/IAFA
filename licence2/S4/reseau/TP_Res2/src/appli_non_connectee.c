/************************************************************
*      APPLICATION de transfert de fichiers                *
*                                                          *
*  --> L'application s'appuie sur les services de          *
*      transmission de la couche transport en mode         *
*      non connecté                                        *
*                                                          *
* E. Lavinal - Univ. de Toulouse III - Paul Sabatier       *
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "application.h"
#include "config.h"

#define LECTURE_MAX 96

static FILE *fichier = NULL;

/*
* Lecture de données émanant de la couche application.
* Paramètres (en sortie):
*  - donnees : message devant être envoyé (issu de la couche application)
*  - taille_msg : nombre d'octets de données à émettre (0 si pas de données)
*/
void de_application(unsigned char *message, int *taille_msg)
{
    /* test état fichier */
    if (fichier == NULL) {
        /* fichier non ouvert, ouverture en lecture */
        char nom_fichier[30];
        conf_fichier_emission(nom_fichier);
        fichier = fopen(nom_fichier, "r");
        if (fichier == NULL) {
            perror("[APP] Problème ouverture fichier en lecture !\n");
            exit(1);
        }
    }

    if ( !feof(fichier) ) {
        /* lecture du fichier, au max LECTURE_MAX données */
        /* fread(void *restrict ptr, size_t size, size_t nitems,
        *       FILE *restrict stream); */
        *taille_msg = fread(message, 1, LECTURE_MAX, fichier);
        printf("\n[APP] Lecture fichier.\n");
    }
    else {
        *taille_msg = 0;
        printf("[APP] Fin du fichier.\n");
        fclose(fichier);
    }
}

/*
* Remise de données à la couche application.
* Paramètres (en entrée):
*  - donnees : données à remonter à l'application
*  - taille_msg : taille des données
* Renvoie :
*    -> 1 si le récepteur n'a plus rien à écrire (fichier terminé)
*    -> 0 sinon
*/
int vers_application(unsigned char *message, int taille_msg)
{
    /* test état fichier */
    if (fichier == NULL) {
        /* fichier non ouvert, ouverture en écriture */
        char nom_fichier[30];
        conf_fichier_reception(nom_fichier);
        fichier = fopen(nom_fichier, "w");
        if (fichier == NULL) {
            perror("[APP] Problème ouverture fichier en écriture !\n");
            exit(1);
        }
    }

    /* écriture des données dans le fichier */
    printf("[APP] Ecriture fichier.\n\n");
    fwrite(message, 1, taille_msg, fichier);
    fflush(fichier);

    if (taille_msg < LECTURE_MAX) {
        /* c'etait la derniere partie du fichier car taille message < LECTURE_MAX */
        /* ATTENTION HYPOTHESE FORTE...
        --> problème si LECTURE_MAX est un multiple de la taille du message */
        fclose(fichier);
        printf("[APP] Fichier fermé.\n");
        return 1;
    }
    return 0;
}
