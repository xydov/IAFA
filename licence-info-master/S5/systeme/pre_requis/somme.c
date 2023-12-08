// Compilation : gcc somme.c -o somme
// Execution : ./somme entier1 entier2 entier3 [....]

 #include <stdio.h>
 #include <stdlib.h> // pour exit()

int main (int argc, char *argv[]) {
  int somme = 0;

  // Verifier que l'utilisation de la commande est correcte
  if (argc == 1) {
    fprintf(stderr, "usage : %s entier1 entier2 [...]\n", argv[0]);
    exit(1);    
  }

  // Et si c'est OK, traiter les parametres
  // printf("Il y a %d parametres (y compris le nom de la commande)\", argc);
  for (int i = 1; i < argc; i++) 
    somme += atoi(argv[i]); // Transformer une chaine en int
 
  printf("Somme des parametres = %d\n", somme);

  return (0);
}
