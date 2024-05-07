#define _POSIX_C_SOURCE 1

#include "ex.h"

int close_file(int desc)
{
    int status = close(desc);
    if (status == -1)
    {
        perror("Error closing file");
        return ERROR_CLOSING;
    }
    return 0;
}

void saisirFiche(Infos *i)
{
    int age;
    int nbEnf;
    char nom[LONG_MAX_NOM + 1];

    printf("Le nom: \n");
    scanf("%s", nom);

    printf("L'age: \n");
    scanf("%d", &age);

    printf("Le nombre d'enfants: \n");
    scanf("%d", &nbEnf);

    i->Age = age;
    i->nbEnfants = nbEnf;
    strcpy(i->Nom, nom);
}

void printFiche(Infos i)
{
    printf("le nom: %s\n", i.Nom);
    printf("l'age': %d\n", i.Age);
    printf("le nombre d'enfants: %d\n", i.nbEnfants);
}

int creation(char *NomFichier)
{
    int desc;
    int nb_fiches;
    Infos fiche1;
    ssize_t s;

    desc = open(NomFichier, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (desc == -1)
    {
        perror(NomFichier);
        return ERROR_READING;
    }
    printf("nombre de fiches à entrer: ");
    scanf("%d", &nb_fiches);

    for (int i = 0; i < nb_fiches; i++)
    {

        /* Saisie FIche */
        saisirFiche(&fiche1);
        /* affichage DEBUG de la fiche */
        /* printFiche(fiche1); */

        /* Ecriture dans le fichier */
        s = write(desc, &fiche1, sizeof(Infos));
        /* write retourne le nb d'octets effectif écrits */

        if (s == -1)
        {
            /* Erreur tout court */
            perror("Erreur ecriture fichier");
            if (close_file(desc) == ERROR_CLOSING)
            {
                return ERROR_CLOSING;
            }
            return ERROR_READING;
        }
        else if (sizeof(Infos) != s)
        {
            /* Erreur, pas toute la structure a été écrite */
            perror("Erreur ecriture structure");
            if (close_file(desc) == ERROR_CLOSING)
            {
                return ERROR_CLOSING;
            }
            return ERROR_FICHES;
        }
        //  Affichage DEBUG du nb d'octets écrits
        /* printf("Nb octets écrits = %ld\n", s); */
        printf("====== ======\n");
    }
    close_file(desc);

    return 0;
}

int consultation(char *NomFichier)
{
    int desc;
    int n_fiche;
    off_t nb_fiches;

    int ctnue;

    Infos fiche;

    /* Ouverture du fichier */
    desc = open(NomFichier, O_RDONLY);
    if (desc == -1)
    {
        perror(NomFichier);
        exit(ERROR_READING);
    }

    /* Affichage nombre de fiches dans le ficher */
    nb_fiches = lseek(desc, 0L, SEEK_END);
    nb_fiches /= sizeof(Infos);
    printf("Nombre de Fiches = %d\n", (int)nb_fiches);

    // rewind to the start
    lseek(desc, 0L, SEEK_SET);

    /* consultation en boucle : */

    do
    {
        /* saisie numéro fiche */
        printf("Numero de la fiche a consulter: ");
        scanf("%d", &n_fiche);

        if (n_fiche > nb_fiches)
        {
            fprintf(stderr, "Erreur, nombre de fiche est plus petit que %d", n_fiche);
            return ERROR_FICHES;
        }

        /* positionnement début fiche */
        lseek(desc, (n_fiche - 1) * sizeof(Infos), SEEK_CUR);

        /* lecture fiche */
        if (read(desc, &fiche, sizeof(Infos)) == -1)
        {
            perror("Numero de fiche : n_fiche");
            return ERROR_READING;
        }
        /* affichage contenu fiche */
        printFiche(fiche);
        /* back to start */
        lseek(desc, 0L, SEEK_SET);

        /* Continue?? */
        printf("Voulez vous consulter une autre fiche? 1 = oui | 0 = non: ");
        scanf("%d", &ctnue);
    } while (ctnue);

    /* Fermeture fichier */

    if (close(desc) == -1)
    {
        perror(NomFichier);
        return ERROR_CLOSING;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int code_retour = 0;
    if (argc != 2)
    {
        fprintf(stderr, "Nombre de parametres incorrect, taper -h pour l'aide\n");
        exit(3);
    }

    if (!strcmp(argv[1], "-h"))
    {
        printf("Les options ne sont pas cumulables\n");
        printf("-e      pour rentrer une ou plusieures fiches\n");
        printf("-c      pour consulter une ou plusieures fiches\n");
        printf("-h      pour afficher l'aide\n");
    }
    else if (!strcmp(argv[1], "-e"))
    {
        code_retour = creation("fiches");
    }
    else if (!strcmp(argv[1], "-c"))
    {
        code_retour = consultation("fiches");
    }

    return code_retour;
}

/*
perror quand la fct a prévue que ce soit une error
*/