#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct Tab {
  int *tab; //tableau dynamique
  int n;    //nb valeurs
};

struct Tab genTabValAleatoire(int tailleTableau) {

  struct Tab tableau;

  tableau.n = tailleTableau;
  tableau.tab = malloc(tailleTableau * sizeof(int));

  for (int i = 0; i < tailleTableau; i++) {
    tableau.tab[i] = rand()%101;
  }
  return tableau;
}



struct Tab void hm(struct Tab tabPara) {

  struct Tab t7;

  int i = 0;

  while (i < tabPara.n) {
    if(tabPara.tab[i] % 7 == 0) {
      t7.tab[j] = tabPara.tab[i];
      j ++;
      tabPara.tab[i] = tabPara.tab[tabPara.n - 1];
      tabPara.n --;
    } else {

    }
  }
}



int main(void) {
  srand(time(NULL));
  int tailleTableau;

  printf("taille du tableau: \n");
  scanf("%d", &tailleTableau);

  struct Tab newTab = genTabValAleatoire(tailleTableau);

  for (int i = 0; i < tailleTableau; i++) {
    printf("%d, ", newTab.tab[i]);
  }
  printf("\n");

  // passe le tableau dans hm
  

  return 0;
}
