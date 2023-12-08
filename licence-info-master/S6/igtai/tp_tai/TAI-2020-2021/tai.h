#ifndef __tai_h_
#define __tai_h_

#include <stddef.h>
#include "limace.h"

/*
* Inversion d'une image
 * Entrée : image initiale (binaire, niveaux de gris ou couleur)
 * Sortie : image résultat
 */
extern Image Inversion(Image Im);

/*
 * Étalement de la dynamique d'une image de niveaux de gris
 * Entrée : image initiale en niveaux de gris
 * Sortie : image résultat
 */
extern Image Etalement(Image Im);

/*
 * Binarisation d'une image de niveaux de gris par seuillage global
 * Entrées : image de niveaux de gris initiale et seuil
 * Sortie : image binaire
 */
extern Image Binarisation(Image Im, unsigned char Seuil);

/*
 * Filtrage moyen d'une image de niveaux de gris
 * Entrées : image initiale en niveaux de gris
 *           taille du voisinage (Taille x Taille)
 * Sortie : image résultat
 */
extern Image Moyen(Image Im, int Taille);

/*
 * Filtrage médian d'une image de niveaux de gris
 * Entrées : image initiale en niveaux de gris
 *           taille du voisinage (Taille x Taille)
 * Sortie : image résultat
 */
extern Image Median(Image Im, int Taille);

#define ES_NOT_ODD 1
#define ES_NOT_INT 2
#define ES_NOT_BIN 3
/*
 * Vérification de la validité d'une matrice représentant un élément structurant
 * Entrée : matrice représentant un élément structurant
 * Sortie : 0 si la matrice est valide,
            ES_NOT_ODD si son nombre de lignes ou de colonnes n'est pas impair
            ES_NOT_INT si elle ne contient pas que des entiers
            ES_NOT_BIN si elle ne contient pas que des 0 et des 1
*/
extern int InvalideES(Matrix ElementStructurant);

/*
 * Érosion d'une image binaire
 * Entrées : image binaire initiale et élément structurant (matrice de int
 * contenant uniquement des 0 et des 1)
 * Sortie : image binaire erodée
 */
extern Image Erosion(Image Im, Matrix ElementStructurant);

/*
 * Dilatation d'une image binaire
 * Entreés : image binaire initiale et élément structurant (matrice de int
 * contenant uniquement des 0 et des 1)
 * Sortie : image binaire dilatée
 */
extern Image Dilatation(Image Im, Matrix ElementStructurant);


#endif /* !__tai_h_ */
