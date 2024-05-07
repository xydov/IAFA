#include <stdio.h>

const int TAILLE_MAX = 60;


// Saisir le contenu d'un tableau
// Un tableau est une adresse, le contenu est donc modifie
void saisirTableau (int leTab[], int laTaille) {
  for (int i = 0; i < laTaille; i++) {
    printf("Valeur %d ?", i+1);
    scanf("%d", &leTab[i]);    
  }
}

// Afficher le contenu d'un tableau
void afficherTableau (int leTab[], int laTaille) {
  for (int i = 0; i < laTaille; i++) {
    printf("%3d", leTab[i]);    
  }
  printf("\n");
}

// Trier un tableau de taille donnee, par ordre croissant
// Tri (pas le plus efficace) par insertion
void trierTableau (int leTab[], int laTaille) {
  int j;
  for (int i = 0; i < laTaille; i++) {
    int courant = leTab[i];
    for (j = i; j > 0 && leTab[j-1] > courant; j--) {
      leTab[j] = leTab[j-1];
    }
    leTab[j] = courant;
  }
}

int main (void) {
  int tab[TAILLE_MAX];	
  int nbElts;

  printf("Nombre d'elements du tableau (<= %d) ?", TAILLE_MAX);
  scanf("%d", &nbElts);
  if (nbElts < 0)
    nbElts = 0;
  if (nbElts > TAILLE_MAX)
    nbElts = TAILLE_MAX;

  saisirTableau(tab, nbElts);
  trierTableau(tab, nbElts);
  afficherTableau(tab, nbElts);

  return (0);
}
