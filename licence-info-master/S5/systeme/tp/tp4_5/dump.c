/**-------------------------------------------------------------------------
  TP5 - Squelette code exercice 3
  Compilation : gcc tp45_exo3_base.c -o tp45_exo3 -Wall
--------------------------------------------------------------------------**/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define LG_MAX 80

/*-----------------------------
 * Envoyer un message a chaque fois que le delai est ecoule
 * ----------------------------*/
void envoyerMessage(int sigRecu)
{

  /* Constituer le message */
  sprintf(monMsg, "%s %d %s %s", "Message numero", num, " envoye a ", (time(&t), ctime(&t)));

  /* L'envoyer */

  /* Armer la periode suivante */
}

/*-----------------------------*/
void fils(void)
{
  char leMsg[LG_MAX];

  /* Orienter le tube */

  /* Boucler pour lire les messages en les affichant */

  printf("\tFils - Message de mon pere : %s\n", leMsg);

  exit(0);
}

/*-----------------------------*/
int main(int argc, char *argv[])
{

  int i;
  char c;

  /* Verifier les parametres */
  if (argc != 3)
  {
    printf("Usage : %s <Periode en secondes> <Nb d'envois>\n", argv[0]);
    exit(1);
  }

  /* Recuperer les parametres */

  /* Creer le tube de communication */

  /* Creer le fils qui herite du tube */
  switch (fork())
  {
  case -1:
    perror("Echec fork ");
    exit(3);
  case 0:
    fils();
  default:
    break;
  }

  /* Orienter le tube */

  /* Se proteger contre le signal SIGALRM */

  /* Armer le traitement periodique */

  /* Continuer son traitement : Par exemple, boucler sans rien faire */
  /* Le pere doit se terminer en dernier */

  return 0;
}
