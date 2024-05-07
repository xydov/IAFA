/**-------------------------------------------------------------------------
	TP4 - Squelette code exercice 2-V2
	Compilation : gcc tp45_exo2-v2_base.c -o tp45_exo2-v2 -Wall
--------------------------------------------------------------------------**/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

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
	Traitement associ� � SIGINT
------------------------------------------------------------------------*/
void traiterSIGINT(int sig)
{

	/*   A compl�ter */

	printf(">> Ctrl-C/SIGINT recu par %d\n", getpid());
}

/*------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{

	// Se prot�ger contre Ctrl-C (SIGINT)
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

	printf("Processus (pere) de pid %d : Je vais executer boucle\n", getpid());	
	/* Remplacer son code par celui de l'ex�cutable boucler */
	if ( execl("boucle", "") == -1 )
	{
		perror("exec failed");
		exit(EXIT_FAILURE);
	}

	return 0;
}
