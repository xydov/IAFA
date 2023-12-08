#include <stdio.h>

int main() {
  int tab[5];
  int plusGrand, plusPetit;
  int i = 0;
  for (i=0; i<5; i++) //mise a 0 de tout les éléments
  {
    tab[i] = 0;
  }
  for (i = 0; i < 5; i++)
  { //init tableau
    scanf("%d\n",&tab[i]);
  }
  plusGrand = tab[0];
  plusPetit = tab[0];
  for (i = 1; i < 5; i++)
  {
    if (tab[i] < plusPetit)
    {
      plusPetit = tab[i];
    }
    if (tab[i] > plusGrand)
    {
      plusGrand = tab[i];
    }
  }
  printf("Plus petit = %d, et plus grand = %d\n",plusPetit, plusGrand );
}
