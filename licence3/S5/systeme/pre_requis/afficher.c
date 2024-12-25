#include <stdio.h>
#include <fcntl.h>
#include "afficher.h" 

int afficher (char *nomFic) {
  int  desFic;
  char chaine[BUFSIZ];
  int  nbCarsLus, nbCarsEcrits;

  /* Ouverture du fichier de nom NomFic */
  if ( (desFic = open(nomFic, O_RDONLY)) < 0) {
    fprintf (stderr, "Pb ouverture %s, res = %d ret = %d\n", 
             nomFic, desFic, ERREUR_OUVERTURE_SOURCE);
    return ERREUR_OUVERTURE_SOURCE;
    }

  /* Lecture du fichier par blocs de BUFSIZ caracteres */
  /* Ecriture dans le fichier de descripteur 1 (ecran) des caracteres lus */
  while ( (nbCarsLus = read(desFic, chaine, BUFSIZ)) > 0)
    nbCarsEcrits = write(1, chaine, nbCarsLus);

  close(desFic);

  return SUCCES;
}

