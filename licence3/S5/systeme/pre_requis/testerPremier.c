// Compilation : gcc testerPremier.c -o testerPremier -lm
// Execution : ./testerPremier
#include <stdio.h>
#include <math.h> // Compiler avec la biblio maths => -lm

// Tester si l'entier parametre est premier
// Retourne 1 si c'est vrai, O (faux) sinon
int estPremier (int unEntier) {
  // 0 et 1 ne sont pas premiers
  if (unEntier < 2)
    return 0;

  for (int div = 2; div <= sqrt(unEntier); div++) { 
    if (unEntier % div == 0)
      // Divisible donc non premier
      return 0;
  }
  // Si on arrive jusqu'ici, on a prouve qu'il est premier
  return 1;  
}


int main (void) {
  int nbVal, val;

  printf("Combien de valeurs ?");
  scanf("%d", &nbVal);

  for (int i = 0; i < nbVal; i++) {
    printf("Valeur num %d ?", i+1);
    scanf("%d", &val);
    if (estPremier(val)) 
      printf("%d est premier\n", val);
    else    
      printf("%d n'est pas premier\n", val);
  }
  return (0);
}
