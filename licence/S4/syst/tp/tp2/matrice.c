#include <stdio.h>
#include <stdlib.h>

#include "matrice.h"

void initialiserMatrice(int matrice[NB_LIGNES_MAX][NB_COLONNES_MAX],
                        unsigned nbLignes, unsigned nbColonnes)
{
    unsigned indLigne, indColonne;
    srand(NB_COLONNES_MAX);
    for (indLigne = 0; indLigne < nbLignes; indLigne++)
        for (indColonne = 0; indColonne < nbColonnes; indColonne++)
            matrice[indLigne][indColonne] = rand() % nbColonnes;
}

void afficherMatrice(int matrice[NB_LIGNES_MAX][NB_COLONNES_MAX],
                     unsigned nbLignes, unsigned nbColonnes)
{
    unsigned indLigne, indColonne;
    for (indLigne = 0; indLigne < nbLignes; indLigne++)
    {
        printf("%u:", indLigne);
        for (indColonne = 0; indColonne < nbColonnes; indColonne++)
            printf(" %2u", matrice[indLigne][indColonne]);
        printf("\n");
    }
}
