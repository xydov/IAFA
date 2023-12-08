/// \file lecture_fichier_tsplib.c
/// \author Tarek Kunze
/// \date december 2019
/// \brief lecture des fichiers .tsp

#include "lecture_fichier_tsplib.h"

bool prefix(char *motif, char *buf)
{
    /// \brief teste si le motif = le buffer avec strcmp()
    /// \param[in, out] motif : motif
    /// \param[in, out] buf : buffer
    return !strcmp(motif, buf);
}

void get_first_word(char *line, char *first_word)
{
    /// \brief récupère le 1er mot d'une ligne
    /// \param[in] line : ligne
    /// \param[in, out] first_word : poiteur sur le tableau contenant le mot
    int i = 0;
    while (line[i] != ' ' && line[i] != '\n')
    {
        first_word[i] = line[i];
        i++;
    }
    first_word[i] = '\0';
}

void get_field_value(char *line, char *field_value)
{
    /// \brief récupère la valeur d'un champ
    /// \param[in] line : ligne
    /// \param[in, out] field_value : poiteur sur le tableau contenant le champ
    int i = 0;
    while (line[i] != ':')
    {
        i++;
    }
    i += 2;
    int j = 0;
    while (line[i] != '\0' && line[i] != '\n' && j < i)
    {
        field_value[j] = line[i];
        i++;
        j++;
    }
    field_value[j] = '\0';
}

int lecture_fichier(char *filename, instance_t *instance)
{
    /// \brief lis le fichier de nom filename
    /// \param[in] filename : nom du fichier a lire
    /// \param[in, out] instance : isntance du problème
    /// \return 1 si fichier bien lu 0 sinon
    FILE *tsp_prob_file = fopen(filename, "r");
    int c = 0;
    int dim = 0;
    char buffer[MAXBUF] = "";

    int poubelle;

    if (tsp_prob_file != NULL)
    {
        while (fgets(buffer, MAXBUF, tsp_prob_file) != NULL)
        {
            char field_type[TAILLENOM];
            char field_value[TAILLENOM];

            get_first_word(buffer, field_type);

            if (prefix(field_type, "NAME"))
            {
                // get field value
                get_field_value(buffer, field_value);
                // fill struct with it
                strcpy(instance->name, field_value);
            }
            else if (prefix(field_type, "COMMENT"))
            {
                //     // get field value
                get_field_value(buffer, field_value);
                //     // fill struct with it
                strcpy(instance->comment, field_value);
            }
            else if (prefix(field_type, "TYPE"))
            {
                // get field value
                get_field_value(buffer, field_value);
                // fill struct with it
                strcpy(instance->type, field_value);
            }
            else if (prefix(field_type, "DIMENSION"))
            {
                // get field value
                get_field_value(buffer, field_value);
                // fill struct with it
                instance->dimension = atoi(field_value);
                if (!sans_zero)
                {
                    instance->dimension += 1;
                }

            }
            else if (prefix(field_type, "EDGE_WEIGHT_TYPE"))
            {
                // get field value
                get_field_value(buffer, field_value);
                // fill struct with it
                strcpy(instance->EDGE_TYPE, field_value);
            }
            else if (prefix(field_type, "NODE_COORD_SECTION"))
            {
                instance->tabCoord = create_long_mat(instance->dimension, 2);
                if (!sans_zero)
                {
                    instance->tabCoord[0][0] = 0;
                    instance->tabCoord[0][1] = 0;
                    for (int i = 1; i < instance->dimension; i++)
                    {
                        fscanf(tsp_prob_file, "%d %ld %ld", &poubelle, &instance->tabCoord[i][0], &instance->tabCoord[i][1]);
                    }
                    fclose(tsp_prob_file);
                }
                if (sans_zero)
                {
                    for (int i = 0; i < instance->dimension; i++)
                    {
                        fscanf(tsp_prob_file, "%d %ld %ld", &poubelle, &instance->tabCoord[i][0], &instance->tabCoord[i][1]);
                    }
                    fclose(tsp_prob_file);
                }
            }
            else if (prefix(field_type, "EOF"))
            {
                fclose(tsp_prob_file);
            }
        }
        fclose(tsp_prob_file);
    }
    else
    {
        printf("Error reading input file\n");
        return NIL;
    }

    return 0;
}