#define _POSIX_C_SOURCE 1

#include "ex.h"

int afficher_taille_fichier(char *chemin_fichier)
{
    struct stat s;

    if (stat(chemin_fichier, &s) == -1)
    {
        perror(chemin_fichier);
        return ERROR_STAT;
    }

    printf("%-20s", chemin_fichier);
    printf(": %8ld octets\n", s.st_size);
    return 0;
}

int recherche_sous_rep(char *chemin)
{
    /* on passe sur tout les fichier du rep
        si un d'entre eux est un rep, on recursive dessus,
        si on arrive a la fin, on met le des au début et on repasse
        cette fois avec la fonction afficher info du fichier + total
        /!\ attenton a bien vérifier a chaque fois
        que c'est bien un fichier ou un rep
     */
    DIR *rep;
    struct dirent *rep_courant;
    struct stat s;
    long somme_taille = 0;

    if ((rep = opendir(chemin)) == NULL)
    {
        perror(chemin);
        return ERROR_OPENDIR;
    }

    while ((rep_courant = readdir(rep)) != NULL)
    {
        if (stat(chemin, &s) == -1)
        {
            perror(chemin);
            return ERROR_STAT;
        }
        if (S_ISDIR(s.st_mode) != 0 && strcmp(rep_courant->d_name, "..") && strcmp(rep_courant->d_name, "."))
        {
            sprintf(chemin, "%s/%s", chemin, rep_courant->d_name);
            recherche_sous_rep(chemin);
        }
    }
    rewinddir(rep);
    /* files in the current dir */
    while ((rep_courant = readdir(rep)) != NULL)
    {
        if (stat(chemin, &s) == -1)
        {
            perror(chemin);
            return ERROR_STAT;
        }
        if (S_ISREG(s.st_mode))
        {
            afficher_taille_fichier(chemin);
            somme_taille += s.st_size;
        }
    }

    printf("\tTOTAL TEST  : %8ld\n", somme_taille);


    if (closedir(rep) == -1)
    {
        perror(rep_courant->d_name);
        return ERROR_CLOSINGDIR;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Nombre de paramètres incorrect\n");
        return 1;
    }

    recherche_sous_rep(argv[1]);
    
    return 0;
}