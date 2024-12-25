#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "limace.h"
#include "tai.h"

#define DEBOGAGE

#ifdef DEBOGAGE
#define DEBUG fprintf(stderr, "Fichier %s, ligne %d\n", __FILE__, __LINE__);
#else
#define DEBUG
#endif

#define AFAIRE(fonction)                              \
    fprintf(stderr, "Corps de la fonction " #fonction \
                    " à écrire.\n");                  \
    return NULL;

/*
 * Inversion d'une image
 * Entrée : image initiale (binaire, niveaux de gris ou couleur)
 * Sortie : image résultat
 */
Image Inversion(Image Im)
{
    ImageType type = ImType(Im);
    int nbcols = ImNbCol(Im);
    int nbrows = ImNbRow(Im);
    if (type == BitMap)
    {
        // b & w

        // le pixel (0,0) de la première image (chenille) vaut 1
        // alors que le pixel (0,0) de la seconde image vaut 0
        unsigned char **image_matrix;
        image_matrix = ImGetI(Im);
        for (int i = 0; i < nbrows; i++)
        {
            for (int j = 0; j < nbcols; j++)
            {
                if (image_matrix[i][j] == 0)
                {
                    image_matrix[i][j] = 1;
                }
                else
                {
                    image_matrix[i][j] = 0;
                }
            }
        }
    }
    else if (type == GrayLevel)
    {
        // niveaux de gris

        // le pixel (0,0) de la première image (chenille) vaut 61
        // alors que le pixel (0,0) de la seconde image vaut 194
        unsigned char **image_matrix;
        image_matrix = ImGetI(Im);
        for (int i = 0; i < nbrows; i++)
        {
            for (int j = 0; j < nbcols; j++)
            {
                image_matrix[i][j] = 255 - image_matrix[i][j];
            }
        }
    }
    else if (type == Color)
    {
        // couleur

        // le pixel (0,0) de la première matrice (chenille) vaut (61,63,55)
        // alors que le pixel (0,0) de la seconde matrice vaut (194,192,200)
        unsigned char **red_channel;
        unsigned char **green_channel;
        unsigned char **blue_channel;
        red_channel = ImGetR(Im);
        green_channel = ImGetG(Im);
        blue_channel = ImGetB(Im);
        if (red_channel == NULL || green_channel == NULL || blue_channel == NULL)
        {
            fprintf(stderr, "[tai.c - Inversion] - Erreur lors de l'accés aux channels RGB\n");
            exit(1);
        }
        for (int i = 0; i < nbrows; i++)
        {
            for (int j = 0; j < nbcols; j++)
            {
                red_channel[i][j] = 255 - red_channel[i][j];
                green_channel[i][j] = 255 - green_channel[i][j];
                blue_channel[i][j] = 255 - blue_channel[i][j];
            }
        }
    }
    return Im;
}

/*
  * Étalement de la dynamique d'une image de niveaux de gris
  * Entrée : image initiale en niveaux de gris
  * Sortie : image résultat
  */
Image Etalement(Image Im)
{
    // min -> to -> 0
    // max -> to -> 255
    ImageType type = ImType(Im);
    int nbcols = ImNbCol(Im);
    int nbrows = ImNbRow(Im);
    if (type == GrayLevel)
    {
        // niveaux de gris
        unsigned char **image_matrix;
        image_matrix = ImGetI(Im);
        int min = 255;
        int max = 0;
        // get min and max
        for (int i = 0; i < nbrows; i++)
        {
            for (int j = 0; j < nbcols; j++)
            {
                if (image_matrix[i][j] > max)
                {
                    max = image_matrix[i][j];
                }
                if (image_matrix[i][j] < min)
                {
                    min = image_matrix[i][j];
                }
            }
        }
        // printf("[tai.c - Etalement] - min = %d| max = %d\n", min, max);
        // modif
        // unsigned char f = image_matrix[i][j];
        // assert(min <= f && f <= max);
        unsigned char *Debut, *Fin, *p;
        Debut = *(image_matrix);       // recuperation de l’adresse de début de la zone, memoire contenant les niveaux de gris
        Fin = Debut + nbrows * nbcols; /// calcul de l’adresse de fin de la zone
        for (p = Debut; p < Fin; *p++ = roundf(255 * ((float)(*p) - (float)min) / ((float)max - (float)min)));
    }
    else
    {
        fprintf(stderr, "[tai.c - Etalement] - Erreur, l'image n'est pas en niveau de gris\n");
        exit(1);
    }
    return Im;
}

/*
 * Binarisation d'une image de niveaux de gris par seuillage global
 * Entrées : image de niveaux de gris initiale et seuil
 * Sortie : image binaire
 */
Image Binarisation(Image Im, unsigned char Seuil)
{
    AFAIRE(Binarisation);
}

/*
 * Filtrage moyen d'une image de niveaux de gris
 * Entrées : image initiale en niveaux de gris
 *           taille du voisinage (Taille x Taille)
 * Sortie : image résultat
 */
Image Moyen(Image Im, int Taille)
{
    AFAIRE(Moyen);
}

/*
 * Filtrage médian d'une image de niveaux de gris
 * Entrées : image initiale en niveaux de gris
 *           taille du voisinage (Taille x Taille)
 * Sortie : image résultat
 */
Image Median(Image Im, int Taille)
{
    AFAIRE(Median);
}

/*
 * Vérification de la validité d'une matrice représentant un élément structurant
 * Entrée : matrice représentant un élément structurant
 * Sortie : 0 si la matrice est valide,
            ES_NOT_ODD si son nombre de lignes ou de colonnes n'est pas impair
            ES_NOT_INT si elle ne contient pas que des entiers
            ES_NOT_BIN si elle ne contient pas que des 0 et des 1
*/
int InvalideES(Matrix ElementStructurant)
{
    int **ES, NbLig, NbCol, i, j;

    if (MatType(ElementStructurant) != Int)
        return ES_NOT_INT;
    NbLig = MatNbRow(ElementStructurant);
    if ((NbLig % 2) != 1)
        return ES_NOT_ODD;
    NbCol = MatNbCol(ElementStructurant);
    if ((NbCol % 2) != 1)
        return ES_NOT_ODD;
    ES = MatGetInt(ElementStructurant);
    for (i = 0; i < NbLig; i++)
        for (j = 0; j < NbCol; j++)
            if (ES[i][j] != 0 && ES[i][j] != 1)
                return ES_NOT_BIN;
    return 0;
}

/*
 * Érosion d'une image binaire
 * Entrées : image binaire initiale et élément structurant (matrice de int
 * contenant uniquement des 0 et des 1)
 * Sortie : image binaire erodée
 */
Image Erosion(Image Im, Matrix ElementStructurant)
{
    AFAIRE(Erosion);
}

/*
 * Dilatation d'une image binaire
 * Entreés : image binaire initiale et élément structurant (matrice de int
 * contenant uniquement des 0 et des 1)
 * Sortie : image binaire dilatée
 */
Image Dilatation(Image Im, Matrix ElementStructurant)
{
    AFAIRE(Dilatation);
}
