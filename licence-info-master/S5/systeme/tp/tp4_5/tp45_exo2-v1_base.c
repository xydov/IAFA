/**-------------------------------------------------------------------------
  TP4 - Squelette code exercice 2-V1
  Compilation : gcc tp45_exo2-v1_base.c boucler.o -o tp45_exo2-v1 -Wall
--------------------------------------------------------------------------**/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
// #include "boucler.h"

void afficher(void) {
	printf("Processus (fils) de pid %d : Je boucle...\n", getpid());
	sleep(1);
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
	Traitement associe SIGINT
------------------------------------------------------------------------*/
void traiterSIGINT(int sig)
{
	printf(">> Ctrl-C/SIGINT recu par %d\n", getpid());
}

/*------------------------------------------------------------------------
	Code execute par chaque processus fils 
------------------------------------------------------------------------*/
void fils()
{
	while (1)
	{
		afficher();
	}
	exit(0);
}

/*------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	// Se proteger contre Ctrl-C (SIGINT)
	pid_t pfils;
	struct sigaction sa = {0};
	struct sigaction old = {0};

	sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGINT);
    sa.sa_handler = traiterSIGINT;
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, &old) == -1)
    {
        erreur("Error sigaction", 2);
    }

	printf("Processus (pere) de pid %d : protege contre SIGINT\n", getpid());
	pause();
	// sigsuspend()
	switch (pfils = fork())
	{
	case -1:
		erreur("Echec fork", 1);

	case 0:
		fils();
		/* default : break; */
	}

	printf("Processus (pere) de pid %d : j'ai cree un fils de pid %d\n",
		getpid(), pfils);

	/* Attendre eventuellement la fin de son fils */
	wait(NULL);

	return 0;
}
