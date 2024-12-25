/**-------------------------------------------------------------------------
  TP1 - Squelette code exercice 1-V1
  Compilation : gcc tp1_exo1-v1_base.c -o exo1b -Wall
--------------------------------------------------------------------------**/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define NB_FILS_MAX 10
#define NB_FOIS 10

/*------------------------------------------------------------------------
 * Affichage de l'identite de l'appelant 
  ------------------------------------------------------------------------*/
void afficher(int rang, pid_t pid)
{
	printf("Je suis le processus de rang %d, mon identificateur est %d\n", rang, pid);
}

/*------------------------------------------------------------------------
 Fonction d'affichage d'une erreur selon la cause de l'echec d'une primitive
 Arret du processus avec retour valant codeRetour
  ------------------------------------------------------------------------*/
void erreur(char *msg, int codeRetour)
{
	perror(msg);
	exit(codeRetour);
}

/*------------------------------------------------------------------------
 Code execute par chaque processus fils 
  ------------------------------------------------------------------------*/
void fils(int rang, int nbAffichages)
{
	int i;
	/* A completer . . . */
	pid_t pid = getpid();

	for (i = 0; i < nbAffichages; i++)
	{
		afficher(rang, pid);
	}

	exit(0);
}

/*------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	int i, nbFils, nbAffichages;
	pid_t pids[NB_FILS_MAX];

	if (argc != 2)
	{
		printf("Usage : %s <Nb Fils>\n", argv[0]);
		exit(1);
	}
	nbFils = atoi(argv[1]);
	if (nbFils > NB_FILS_MAX)
		nbFils = NB_FILS_MAX;

	printf("Combien d'affichages du message ?\n");
	scanf("%d", &nbAffichages);

	/* Creation des fils */
	for (i = 0; i < nbFils; i++)
	{
		switch (pids[i] = fork())
		{
		case -1:
			erreur("Echec fork", 1);

		case 0:
			fils(i, nbAffichages);

			/* default : break; */
		}
	}
	/* Attendre la fin des fils (eventuellement)  */
	while (wait(NULL) != -1)
		;

	return 0;
}
