#include <stdio.h>

// Deux manieres de definir des constantes
const int NB_LIG_MAX = 20;
#define NB_COL_MAX 20


// Saisir le contenu d'une matrice
void saisirMatrice (int laMat[][NB_COL_MAX], int leNbLig, int leNbCol) {
  for (int l = 0; l < leNbLig; l++) {
    for (int c = 0; c < leNbCol; c++) {
      printf("Valeur (%d, %d) ?", l+1, c+1);
      scanf("%d", &laMat[l][c]);    
    }
  }
}

// Afficher le contenu d'une matrice
void afficherMatrice (int laMat[][NB_COL_MAX], int leNbLig, int leNbCol) {
  for (int l = 0; l < leNbLig; l++) {
    for (int c = 0; c < leNbCol; c++) {
      printf("%d  ", laMat[l][c]);    
    }
  printf("\n");
  }
}

int main (void) {
  int mat[NB_LIG_MAX][NB_COL_MAX];	
  int nbLignes, nbColonnes;

  printf("Nombre de lignes de la matrice (<= %d) ?", NB_LIG_MAX);
  scanf("%d", &nbLignes);
  // Etre sur de ne pas depasser les tailles maximales
  // Fixer ou saisir a nouveau
  if (nbLignes < 0)
    nbLignes = 0;
  if (nbLignes > NB_LIG_MAX)
    nbLignes = NB_LIG_MAX;

  printf("Nombre de colonnes de la matrice (<= %d) ?", NB_COL_MAX);
  scanf("%d", &nbColonnes);
  if (nbColonnes < 0)
    nbColonnes = 0;
  if (nbColonnes > NB_COL_MAX)
    nbColonnes = NB_COL_MAX;

  saisirMatrice(mat, nbLignes, nbColonnes);
  afficherMatrice(mat, nbLignes, nbColonnes);

  return (0);
}
