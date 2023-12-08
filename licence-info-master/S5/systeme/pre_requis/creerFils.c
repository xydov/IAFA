// Creer un processus fils

#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>  // pour le fork, getpid...

// En globale, cette variable est connue (visible) de ce qui suit
// Mais, elle n'est pas partagee !!!
int nbFois;

void traitementDuPere (void) {
  for (int i = 0; i < nbFois; i++) {
    printf("Je suis le pere, mon pid est %d\n", getpid());	  
  }	  
}

void traitementDuFils (void) {
  for (int i = 0; i < nbFois; i++) {
    printf("\tJe suis le fils, mon pid est %d\n", getpid());	  
  }	  
  // Terminaison normale
  exit(0);
}

int main (int argc, char *argv[]) {

  // Verifier que l'utilisation de la commande est correcte
  if (argc != 2) {
    fprintf(stderr, "Usage : %s <Nb de boucles>\n", argv[0]);
    exit(1);    
  }
  nbFois = atoi(argv[1]);

  // Creer le fils, qui heritera de la valeur nbFois
  // positionnee par son pere
  // On pourrait aussi declarer nbFois en local au main()
  // et passer cette valeur en parametre de la fonction du fils
  switch (fork()) {
    case -1 : // Erreur du fork (plus assez de ressources)
              perror("Echec fork");
              exit(2);
    case 0 : // fork() retourne 0 dans le contexte du fils
             // On place ici le code execute par le fils
	     traitementDuFils();

    default : // fork() retourne une valeur positive
	      // dans le contexte du pere
	      // On place le code execute par le pere ici
	      // Ou apres la fin du switch
	      traitementDuPere();
  }
  // Attention : si le fils ne fait pas exit(), il execute
  // aussi le code qui se trouve ici, le code est commun 
  // au pere et a ses fils...
  
  return (0);
}
