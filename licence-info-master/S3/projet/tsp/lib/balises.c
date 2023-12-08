/// \file balises.c
/// \author Tarek Kunze
/// \date december 2019
/// \brief recuperation entree utilisateurs

#include <stdio.h>
#include <stdlib.h>
#include "balises.h"
#include "tspstat.h"

void init_balises(int *balises)
{
    /// \brief initialise le tableau des balises a -1
    /// \param[in, out] balises : tableau des balises
    for (int i = 0; i < NB_BALISES; i++)
    {
        balises[i] = NIL;
    }
}

void anhiliation_bal(int ind_bal, int *bal_arr)
{
    /// \brief Si une balises est "utilisés" on remplace sa valeur par -1
    /// \param [in] ind_bal : indice ddde la balise a supprimer
    /// \param[in, out] bal_arr : tableau des balises
    bal_arr[ind_bal] = NIL;
}

void print_help(void)
{
    /// \brief Affiche à l'écran le fichier d'aide de la sélection des balises

    FILE *help_file = fopen("./res/help.txt", "r");
    char buffer[MAXBUF] = "";
    if (help_file != NULL)
    {
        while (fgets(buffer, MAXBUF, help_file) != NULL)
        {
            printf("%s", buffer);
        }
        fclose(help_file);
    }
    else
    {
        printf("Erreur d'ouverture du fichier help.txt\n");
    }
}

int recherche_chaine(int argc, char **argv, char *ch)
{
    /// \brief Cherche une chaine dans le tableau argv
    /// \param[in] argc : Le nombre d'argument dans le tableau argv
    /// \param[in] **argv : listes des arguments
    /// \param[in] *ch : La chaine recherché dans argv
    /// \return l'indice de la chaine recherché dans le tableau argv ou NIL si absente

    int i = 1;
    while (i < argc)
    {
        if (!strcmp(argv[i], ch))
        {
            return i;
        }
        i++;
    }
    return NIL;
}

void analyse_balises(int argc, char **argv, int tab_arg[NB_BALISES])
{
    /// \brief Crée un tableau tab_args dont la dimension est le nombre maximal de balises, initialisé à -1
    /// \brief  si la balise est présente dans la commande, le -1 correspondant est remplacé par son indice dans argv
    /// \param[in] argc : Le nombre d'argument dans le tableau argv
    /// \param[in] **argv : listes des arguments
    /// \param[in, out] tab_arg : Le tableau contenant l'indice des balises utilisés dans argv

    tab_arg[0] = recherche_chaine(argc, argv, "-f");
    tab_arg[1] = recherche_chaine(argc, argv, "-t");
    tab_arg[2] = recherche_chaine(argc, argv, "-v");
    tab_arg[3] = recherche_chaine(argc, argv, "-o");
    tab_arg[4] = recherche_chaine(argc, argv, "-ppv");
    tab_arg[5] = recherche_chaine(argc, argv, "-bf");
    tab_arg[6] = recherche_chaine(argc, argv, "-bfm");
    tab_arg[7] = recherche_chaine(argc, argv, "-rw");
    tab_arg[8] = recherche_chaine(argc, argv, "-2opt");
    tab_arg[9] = recherche_chaine(argc, argv, "-ga");
    tab_arg[10] = recherche_chaine(argc, argv, "-h");
    tab_arg[11] = recherche_chaine(argc, argv, "-nz");
}
