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
#include <sys/wait.h>

#define LG_MAX 80

int tube[2];
int n_messages_envoyer = 0;
int wait_time;
/*-----------------------------
 * Envoyer un message a chaque fois que le delai est ecoule
 * ----------------------------*/
void envoyerMessage(int sigRecu)
{
	if (sigRecu != SIGALRM)
	{
		fprintf(stderr, "Error on signal handling received %d instead of %d", sigRecu, SIGALRM);
	}

	char *monMsg = calloc(LG_MAX, sizeof(char));
	time_t t;
	/* Constituer le message */
	sprintf(monMsg, "%s %d %s %s", "Message numero", n_messages_envoyer, " envoye a ", (time(&t), ctime(&t)));
	/* L'envoyer */
	if (write(tube[1], monMsg, LG_MAX) == -1)
	{
		perror("Erreur écriture message dans le tube");
		exit(EXIT_FAILURE);
	}
	++n_messages_envoyer;
	/* Armer la periode suivante */
	errno = 0;
	alarm(wait_time);
	if (errno != 0)
	{
		perror("Error alarm");
		exit(EXIT_FAILURE);
	}
	free(monMsg);
}

/*-----------------------------*/
void fils()
{
	char leMsg[LG_MAX];
	/* Orienter le tube */
	close(tube[1]);
	/* Boucler pour lire les messages en les affichant */
	while (read(tube[0], leMsg, sizeof(leMsg)) != 0)
	{
		printf("\tFils - Message de mon pere : %s\n", leMsg);
	}

	close(tube[0]);
	time_t t;
	printf("Fils : Je me termine a %s\n", (time(&t), ctime(&t)));
	exit(0);
}

/*-----------------------------*/
int main(int argc, char *argv[])
{
	int n_messages;

	/* Verifier les parametres */
	if (argc != 3)
	{
		printf("Usage : %s <Periode en secondes> <Nb d'envois>\n", argv[0]);
		exit(1);
	}
	/* Recuperer les parametres */
	wait_time = atoi(argv[1]);
	n_messages = atoi(argv[2]);
	/* Creer le tube de communication */
	if (pipe(tube) == -1)
	{
		perror("Erreur création du tube");
		exit(EXIT_FAILURE);
	}
	/* Creer le fils qui herite du tube */
	switch (fork())
	{
	case -1:
		perror("Echec fork");
		exit(3);
	case 0:
		fils();
	default:
		break;
	}
	/* Orienter le tube */
	// père écrit dans le tube[1], donc ferme tube[0]
	close(tube[0]);
	/* Se proteger contre le signal SIGALRM */
	struct sigaction action = {0};

	action.sa_handler = envoyerMessage;
	if(sigemptyset(&action.sa_mask) != 0)
	{
		perror("Error sigemptyset");
		exit(EXIT_FAILURE);
	}
	if(sigaddset(&action.sa_mask, SIGALRM) != 0)
	{
		perror("Error sigaddset");
		exit(EXIT_FAILURE);
	}
	action.sa_flags = 0;
	if (sigaction(SIGALRM, &action, NULL) < 0)
	{
		perror("Erreur sigaction");
		exit(EXIT_FAILURE);
	}
	/* Armer le traitement periodique + traitement d'errer*/
	errno = 0;
	alarm(wait_time);
	if (errno != 0)
	{
		perror("Error alarm");
		exit(EXIT_FAILURE);
	}
	/* Continuer son traitement : Par exemple, boucler sans rien faire */
	while (1 && (n_messages_envoyer < n_messages))
		;

	/* Le pere doit se terminer en dernier */
	close(tube[1]);
	while (wait(NULL) != -1)
        ;
	
	return 0;
}
