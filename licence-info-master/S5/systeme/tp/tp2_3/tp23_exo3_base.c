/*
 * TP3 - Squelette exercice 3 - Rendez-vous entre N threads
 * Objectif de la synchronisation : que les threads s'attendent
 * pour passer un point de leur code
 *
 * Pour tester avec la temporisation par usleep, il faut definir
 * la constante lors de la compilation grace a l'option -D :
 * gcc tp23_exo3_base.c -oexo3b -DTEMPO -lpthread -Wall
 * Rappel : Votre synchronisation doit marcher avec ou sans cette
 * temporisation
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

int nbThreads;

// global mutex
sem_t var_acces;
int thread_at_barrier;
sem_t wait_at_barrier;

//---------------------------------------------------------------------
// Afficher un message d'erreur en fonction du code erreur obtenu
// codeErr = code de retour de la fonction testee
// codeArret = adresse de l'information retournee lors du pthread_exit
// Mettre NULL si cette information n'a pas d'importance
void thdErreur(int codeErr, char *msgErr, void *codeArret)
{
	fprintf(stderr, "%s: %d soit %s \n", msgErr, codeErr, strerror(codeErr));
	pthread_exit(codeArret);
}

//---------------------------------------------------------------------
// Fonction pour perdre un peu de temps
void attenteAleatoire(void)
{
#ifdef TEMPO
	usleep(rand() % 100);
#endif
}

//---------------------------------------------------------------------
// Pour simplifier l'utilisation des semaphores et avoir un code qui
// ressemble a ce qui a ete ecrit en TD, on peut implanter l'equivalent
// des operations P et V pour les reutiliser dans les solutions
// Ou reprendre ce qui a ete fait pour l'exercice 1
//
// Implanter l'operation P
void P(sem_t * sem)
{
	/* En cas d'erreur, un message est affiche et l'execution avortee */
	int e;
	if ((e = sem_wait(sem)) != 0)
	{
		thdErreur(e, "Erreur sem_wait", NULL);
	}
}

// Implanter l'operation V
void V(sem_t * sem)
{
	/* En cas d'erreur, un message est affiche et l'execution avortee */
	int e;
	if ((e = sem_post(sem)) != 0)
	{
		thdErreur(e, "Erreur sem_post", NULL);
	}
}

void barrier()
{
	P(&var_acces);
	thread_at_barrier ++;
	if (thread_at_barrier == nbThreads)
	{
		// tout les threads sont arrivé au point de rendez vous
		// i = 1 , on débloque n-1 thread et non n thread
		for (int i = 1; i < nbThreads; i++)
		{
			// ajout de N-1 tickets pour débloquer tout les threads en attente
			V(&wait_at_barrier);
		}
		thread_at_barrier = 0;
		V(&var_acces);
	}
	else
	{
		V(&var_acces);
		P(&wait_at_barrier);
	}
}

//---------------------------------------------------------------------
// Synchronisation a completer pour realiser le RdV
//
void passerRdV(int num)
{
	printf("Thread %d (%lu) : Je passe le point de RdV\n", num, pthread_self());
}

//---------------------------------------------------------------------
// Fonction executee par les threads
void *thd_rdv(void *arg)
{
	int monNum = *(int *)arg;

	srand(pthread_self());

	printf("Thread %d (%lu) : J'effectue un traitement en parallele avec les autres\n", monNum, pthread_self());
	attenteAleatoire();

	printf("Thread %d (%lu) : J'arrive au RdV\n", monNum, pthread_self());
	// wait until all thread arrived here
	barrier();
	passerRdV(monNum);

	printf("Thread %d (%lu) : Je continue un traitement en parallele avec les autres\n", monNum, pthread_self());
	attenteAleatoire();

	pthread_exit((void *)NULL);
}

#define NB_MAX_THREADS 30

//---------------------------------------------------------------------
int main(int argc, char *argv[])
{
	pthread_t idThds[NB_MAX_THREADS];
	int rangs[NB_MAX_THREADS];
	int i, etat;

	if (argc != 2)
	{
		printf("Usage : %s nombreDeThreads\n", argv[0]);
		exit(1);
	}

	nbThreads = atoi(argv[1]);
	if (nbThreads > NB_MAX_THREADS)
		nbThreads = NB_MAX_THREADS;

	// Initialiser le(s) semaphore(s) utilise(s)
	// init a 1 pour un acces unique a la variable protegee
	sem_init(&var_acces, 0, 1);
	sem_init(&wait_at_barrier, 0, 0);
	thread_at_barrier = 0;

	// Lancer les threads
	for (i = 0; i < nbThreads; i++)
	{
		rangs[i] = i;
		if ((etat = pthread_create(&idThds[i], NULL, thd_rdv, &rangs[i])) != 0)
			thdErreur(etat, "Creation thd ", NULL);
	}

	// Attendre leur fin
	for (i = 0; i < nbThreads; i++)
	{
		if ((etat = pthread_join(idThds[i], NULL)) != 0)
			thdErreur(etat, "Join thread 1", NULL);
	}

	// Detruire le(s) semaphore(s) utilise(s)
	/* A completer */

	printf("\nFin de l'execution du thread principal \n");
	return 0;
}
