#include <stdio.h>

int main() {
  int nbrVal, temp, plusGrand, plusPetit;
  int i = 0;
  int oneTime = 1;
  int reponse;
  printf("Nombre de valeurs que vous souhaitez rentrez: ");
  scanf("%d", &nbrVal);

  printf("Souhaitez vous stockez les valeurs dans un tableau? 1: oui // 0: non\n");
  scanf("%d", &reponse);

  if (reponse == 1) {
    printf("ON STOCKE\n");
  }
  else {
    printf("NON ON STOCKE PAS\n");
  }
  for (i = 0; i < nbrVal; i++)
  {
    scanf("%d", &temp);
    if (oneTime)
    { //s'execute 1 fois initialise plusGrand et plusPetit
      oneTime --;
      plusGrand = temp;
      plusPetit = temp;
    }
    if (temp > plusGrand)
    {
      plusGrand = temp;
    }
    if (temp < plusPetit) {
      plusPetit = temp;
    }
    // on stocke dans un tableau a taille adaptative
    if (reponse == 1)
    {
      /* code */
    }
  }
  printf("Plus petit = %d, et plus grand = %d\n",plusPetit, plusGrand );
  return 0;
}
