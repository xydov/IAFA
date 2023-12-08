/// \file display.c
/// \author Tarek Kunze
/// \date december 2019
/// \brief affichage a l'ecran

#include "display.h"

int to_csv_file(char *filename, instance_t instance)
{
    /// \brief écrit les résultats dans un fichiers
    /// \param[in] filename : nom du fichier
    /// \param[in] inst : instance du problème
    /// \return si le fichier a bien été créer
    FILE *csv_file;
    csv_file = fopen(filename, "w");
    if (csv_file != NULL)
    {
        fprintf(csv_file, "%s\n", "*** Instance ***");
        fprintf(csv_file, "%s %s\n", "Nom de l'instance ;", instance.name);
        fprintf(csv_file, "%s %d\n", "Nombre de villes (avec (0,0)) ;", instance.dimension);
        fprintf(csv_file, "%s %s\n", "Type", instance.type);
        fprintf(csv_file, "%s\n", "Point ; Abscisse ; Ordonnée");
        for (int i = 0; i < instance.dimension; i++)
        {
            if (sans_zero)
            {
                fprintf(csv_file, "%6d ; %6ld ; %6ld\n", i + 1, instance.tabCoord[i][0], instance.tabCoord[i][1]);
            }
            else
            {
                fprintf(csv_file, "%6d ; %6ld ; %6ld\n", i, instance.tabCoord[i][0], instance.tabCoord[i][1]);
            }
        }
        fprintf(csv_file, "\n");
    }
    else
    {
        printf("Erreur dans la création du fichier: %s, Le nom du fichier ne dois pas être nul\n", filename);
        return NIL;
    }
    fclose(csv_file);
    return 1;
}

void print_entete(instance_t *instance, char *filename)
{
    /// \brief affiche l'en tete
    /// \param[in] inst : instance du problème
    /// \param[in] filename : nom du fichier
    printf("J'ouvre le fichier : %s\n", filename);
    printf("Commentaire : %s\n", instance->comment);
    printf("%d lignes lues\n", instance->dimension + 6);
    printf("EOF\n");
}

void print_instance_csv(instance_t *instance)
{
    /// \brief affiche les resultats sous forme csv
    /// \param[in] inst : instance du problème
    printf("\n*** Instance ***\n");
    printf("Nom de l'instance ; %s\n", instance->name);
    printf("Nombre de villes (avec (0,0)) ; %d\n", instance->dimension);
    printf("Type %s\n", instance->type);
    printf("Point ; Abscisse ; Ordonnée\n");
    for (int i = 0; i < instance->dimension; i++)
    {
        if (sans_zero)
        {
            printf("%6d ; %6ld ; %6ld\n", i + 1, instance->tabCoord[i][0], instance->tabCoord[i][1]);
        }
        else
        {
            printf("%6d ; %6ld ; %6ld\n", i, instance->tabCoord[i][0], instance->tabCoord[i][1]);
        }
    }
    printf("\n");
}

void print_methode(bool *al_an, char *m_name, double final_length, double time, int *final_nodes, int dimension)
{
    /// \brief écrit les résultats de la methode a l'écran en format csv
    /// \param[in] al_an : si cette chaine de caractére a déjà été affiché
    /// \param[in] m_name : nom de la méthode
    /// \param[in] final_length : longeur finale de la méthode
    /// \param[in] time : temps qu'a pris la fonction a s'exécuter
    /// \param[in] final_nodes : tableau des noeuds
    /// \param[in] dimension : dimension du tableau de noeuds

    if (!*(al_an))
    {
        printf("Méthode ; longueur ; Temps CPU (sec) ; Tour\n");
        *al_an = true;
    }
    printf("%s ; %.2f ; %.2f ; ", m_name, final_length, time);

    printf("[");
    for (int i = 0; i < dimension; i++)
    {
        if (sans_zero)
        {
            printf("%d", final_nodes[i] + 1);
        }
        else
        {
            printf("%d", final_nodes[i]);
        }
        if (i < dimension - 1)
        {
            printf(",");
        }
    }
    printf("]\n");
}

void print_methode_csv_file(bool *al_an, char *m_name, double final_length, double time, int *final_nodes, int dimension, char *filename)
{
    /// \brief écrit les résultats de la methode dans le fichier csv
    /// \param[in] al_an : si cette chaine de caractére a déjà été affiché
    /// \param[in] m_name : nom de la méthode
    /// \param[in] final_length : longeur finale de la méthode
    /// \param[in] time : temps qu'a pris la fonction a s'exécuter
    /// \param[in] final_nodes : tableau des noeuds
    /// \param[in] dimension : dimension du tableau de noeuds
    /// \param[in] filename : nom du fichier csv

    FILE *csv_file;
    csv_file = fopen(filename, "a");

    if (csv_file != NULL)
    {
        if (!*(al_an))
        {
            fprintf(csv_file, "Méthode ; longueur ; Temps CPU (sec) ; Tour\n");
            *al_an = true;
        }

        fprintf(csv_file, "%s ; %.2f ; %.2f ; ", m_name, final_length, time);

        fprintf(csv_file, "[");
        for (int i = 0; i < dimension; i++)
        {
            if (sans_zero)
            {
                fprintf(csv_file, "%d", final_nodes[i] + 1);
            }
            else
            {
                fprintf(csv_file, "%d", final_nodes[i]);
            }
            if (i < dimension - 1)
            {
                fprintf(csv_file, ",");
            }
        }
        fprintf(csv_file, "]\n");
    }
    else
    {
        printf("Erreur dans la leture du fichier: %s, Le nom du fichier ne dois pas être nul\n", filename);
    }
    fclose(csv_file);
}

void print_bf(bool *al_an, double final_length, double time, int *final_nodes, int *worst_nodes, int dimension, instance_t inst)
{
    /// \brief écrit les résultats de la methode bruteforce à l'écran
    /// \param[in] final_length : longeur finale de la méthode
    /// \param[in] time : temps qu'a pris la fonction a s'exécuter
    /// \param[in] final_nodes : tableau des noeuds
    /// \param[in] worst_nodes : tableau des pire noeuds
    /// \param[in] dimension : dimension du tableau de noeuds
    /// \param[in] inst : instance de référence

    if (!*(al_an))
    {
        printf("Méthode ; longueur ; Temps CPU (sec) ; Tour\n");
        *al_an = true;
    }

    printf("Meilleure tournée après le passage de la brute ; %.2f ; %.2f ; ", final_length, time);

    printf("[");
    for (int i = 0; i < dimension; i++)
    {
        if (sans_zero)
        {
            printf("%d", final_nodes[i] + 1);
        }
        else
        {
            printf("%d", final_nodes[i]);
        }
        if (i < dimension - 1)
        {
            printf(",");
        }
    }
    printf("]\n");

    final_length = array_distance(worst_nodes, inst);
    printf("Pire tournée ; %.2f ; %.2f ; ", final_length, time);

    printf("[");
    for (int i = 0; i < dimension; i++)
    {
        if (sans_zero)
        {
            printf("%d", worst_nodes[i] + 1);
        }
        else
        {
            printf("%d", worst_nodes[i]);
        }
        if (i < dimension - 1)
        {
            printf(",");
        }
    }
    printf("]\n");
}

void print_bf_csv_file(bool *al_an, double final_length, double time, int *final_nodes, int *worst_nodes, int dimension, char *filename, instance_t inst)
{
    /// \brief écrit les résultats de la methode bruteforce dans le fichier de nom filename
    /// \param[in] final_length : longeur finale de la méthode
    /// \param[in] time : temps qu'a pris la fonction a s'exécuter
    /// \param[in] final_nodes : tableau des noeuds
    /// \param[in] worst_nodes : tableau des pire noeuds
    /// \param[in] dimension : dimension du tableau de noeuds
    /// \param[in] filename : nom du fichier csv
    /// \param[in] inst : instance de référence

    FILE *csv_file;
    csv_file = fopen(filename, "a");

    if (csv_file != NULL)
    {
        if (!*(al_an))
        {
            fprintf(csv_file, "Méthode ; longueur ; Temps CPU (sec) ; Tour\n");
            *al_an = true;
        }

        fprintf(csv_file, "%s ; %.2f ; %.2f ; ", "Meilleure tournée après le passage de la brute", final_length, time);

        fprintf(csv_file, "[");
        for (int i = 0; i < dimension; i++)
        {
            if (sans_zero)
            {
                fprintf(csv_file, "%d", final_nodes[i] + 1);
            }
            else
            {
                fprintf(csv_file, "%d", final_nodes[i]);
            }
            if (i < dimension - 1)
            {
                fprintf(csv_file, ",");
            }
        }
        fprintf(csv_file, "]\n");

        final_length = array_distance(worst_nodes, inst);
        fprintf(csv_file, "%s ; %.2f ; %.2f ; ", "Pire tournée", final_length, time);

        fprintf(csv_file, "[");
        for (int i = 0; i < dimension; i++)
        {
            if (sans_zero)
            {
                fprintf(csv_file, "%d", worst_nodes[i] + 1);
            }
            else
            {
                fprintf(csv_file, "%d", worst_nodes[i]);
            }
            if (i < dimension - 1)
            {
                fprintf(csv_file, ",");
            }
        }
        fprintf(csv_file, "]\n");
    }
    else
    {
        printf("Erreur dans la leture du fichier: %s, Le nom du fichier ne dois pas être nul\n", filename);
    }
    fclose(csv_file);
}