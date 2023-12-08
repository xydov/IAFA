// Compilation : gcc permuter.c -o permuter
// Execution : ./permuter
 #include <stdio.h>

// Permuter les valeurs passees en parametre
// Passage par adresse pour modifier les parametres
void permute (int *val1, int *val2) {
  // Utiliser une variable intermediaire pour l'echange
  int tmp;
  tmp  = *val1; // recuperer la valeur situee a l'adresse val1
  *val1 = *val2; // remplacer la valeur situee a l'adresse val2
  *val2 = tmp; // et modifier cella a l'adresse val2 
}


int main (void) {
  int valeur1, valeur2;

  printf("Valeur 1 ?");
  scanf("%d", &valeur1);
  printf("Valeur 2 ?");
  scanf("%d", &valeur2);

  printf("Valeurs saisies : 1) %d 2) %d\n", valeur1, valeur2); 
  // On passe les adresses des variables
  permute(&valeur1, &valeur2);
  printf("Valeurs apres : 1) %d 2) %d\n", valeur1, valeur2); 

  return (0);
}
