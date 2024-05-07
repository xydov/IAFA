#define _POSIX_C_SOURCE 1

#include "ex.h"

int afficherInfoFichier(char *nom_fichier)
{
    struct stat s;

    if (stat(nom_fichier, &s) == -1)
    {
        perror(nom_fichier);
        return ERROR_STAT;
    }

    /* Nom */
    printf("%-20s: ", nom_fichier);

    /* Type (fichier, repertoire) */
    if (S_ISREG(s.st_mode) != 0)
    {
        printf("fichier");
    }
    else if (S_ISDIR(s.st_mode))
    {
        printf("repertoire");
    }
    else
    {
        printf("autre");
    }

    /* taille octets */
    printf("%10ld octets  ", s.st_size);

    /*** DERNIERE MODIFICATION ***/
    /* jour, mois, date, annee */
    printf("%s", ctime(&s.st_mtime));

    return 0;
}

int parcours_repertoire(char *nom_repertoire)
{
    //wait()
    DIR *rep;
    struct dirent *rep_courant;

    if ((rep = opendir(nom_repertoire)) == NULL)
    {
        perror(nom_repertoire);
        return ERROR_OPENDIR;
    }

    while ((rep_courant = readdir(rep)) != NULL)
    {
        afficherInfoFichier(rep_courant->d_name);
    }

    if (closedir(rep) == -1)
    {
        perror(rep_courant->d_name);
        return ERROR_CLOSINGDIR;
    }

    /*
    perror(nom_repertoire);
    return ERROR_READDIR;
    */
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        /* Affiche info sur tout fichiers et rep du rep courant */
        parcours_repertoire(".");
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            /* affichage des infos du fichier argv[i] */
            afficherInfoFichier(argv[i]);
        }
    }

    return 0;
}

/* use readdir after opendir */