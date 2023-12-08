#include <stdio.h>

#include <stdlib.h>
#include <time.h>

#define N_MAX 1000

struct Tab {
  int tab[N_MAX]; //tableau statique
  int n;          //Nombre de Valeurs
};


struct Tab nRandFiller(int nbVal) {
  struct Tab newStruct;
  //fill each slot with random values
  for (int i = 0; i < nbVal; i++) {
    newStruct.tab[i] = rand(); //random value
  }

  // add the amount of values added to the array
  newStruct.n = nbVal;
  return newStruct;
}


void tabCleaner(struct Tab structTo) {
// if .tab[i] % 7 == 0: del and .n --
  int amoutOfMoved = 0; // incrment each time %7==0 to swithc with last value always
  for(int i = 0; i < structTo.n; i++) {
    if(structTo.tab[i] % 7 == 0) {
      
    }
  }
}

int main(void) {
  srand(time(NULL));
  struct Tab rrr;
  int nbVal;

  printf("nombre de valeurs: ");
  scanf("%d", &nbVal);

  rrr = nRandFiller(nbVal);

  // test loop
  for (int i = 0; i < rrr.n; i++) {
    printf("%d\n", rrr.tab[i]);
  }
  return 0;
}
