#define _POSIX_C_SOURCE 1

#include "h.h"

#define NBMOTSMAX 20
/* Construction d'un tableau de pointeurs vers le d�but des mots d'une chaine
 * de caract�res en vue de l'utilisation de la fonction execvp.
 * Retourne le nombre de mots trouves.
 */
int Decoupe(char Chaine[], char *pMots[])
{
    char *p;
    int NbMots = 0;

    p = Chaine; /* On commence par le d�but */
    /* Tant que la fin de la cha�ne n'est pas atteinte et qu'on ne d�borde pas */
    while ((*p) != '\0' && NbMots < NBMOTSMAX)
    {
        while ((*p) == ' ' && (*p) != '\0')
            p++; /* Recherche du d�but du mot */
        if ((*p) == '\0')
            break;           /* Fin de cha�ne atteinte */
        pMots[NbMots++] = p; /* Rangement de l'adresse du 1er caract�re du mot */
        while ((*p) != ' ' && (*p) != '\0')
            p++; /* Recherche de la fin du mot */
        if ((*p) == '\0')
            break; /* Fin de cha�ne atteinte */
        *p = '\0'; /* Marquage de la fin du mot */
        p++;       /* Passage au caract�re suivant */
    }
    pMots[NbMots] = NULL; /* Derni�re adresse */
    return NbMots;
}

/// \brief Lance l'exec des commandes passées en parametres
/// créer un processus fils qui lance l’exécution de la commande grâce à la fonction execvp
/// attendre la fin du fils
/// passer a la commande suivante
int main(int argc, char *argv[])
{
    pid_t fork_pid;
    pid_t p_pere;
    pid_t p_fils;

    int circ;
    char *mots[NBMOTSMAX + 1];

    /* for (int i = 0; i < NBMOTSMAX; i++)
    {
        printf("%s \n", mots[i]);
    } */

    int i = 0;
    while (mots[i] != NULL)
    {
        //FIXME Not working
        printf("nb trouv = %d\n", Decoupe(argv[i], mots));

        switch (fork_pid = fork())
        {
        case -1:
            // ERROR -> to PERE
            printf("\nERROR!\n\n");
            break;

        case 0:
            //  FILS
            p_fils = getpid();
            printf("[%d] Je lance %s\n", p_fils, mots[i]);
            exit(10 + i);

        default:
            //  PERE
            p_pere = getpid();
            printf("[%d] J'ai délégué 'cmd' à %d \n", p_pere, fork_pid);
            if ((p_fils = wait(&circ)) != -1)
            {
                printf("[%d] %d terminé.\n", p_pere, p_fils);
            }
            break;
        }
        i++;
    }

    return 0;
}