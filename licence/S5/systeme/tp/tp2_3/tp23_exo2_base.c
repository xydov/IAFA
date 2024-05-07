/*
 * TP2 - Squelette exercice 2 - Synchronisation pour restreindre
 * les affichages possibles
 * Ressource partagee = ecran
 * Objectif de la synchronisation : que les threads ne puissent
 * afficher que ACDB ou ADCB a chaque "cycle"
 *  
 * Pour tester avec la temporisation par usleep, il faut definir
 * la constante lors de la compilation grace a l'option -D :
 * gcc tp23_exo2_base.c -oexo2b -DTEMPO -lpthread
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

//---------------------------------------------------------------------
// Semaphores, variables globales
sem_t start_t2_t3;
sem_t start_t1_from_t2;
sem_t start_t1_from_t3;

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
void P(sem_t * s)
{
	/* A completer */
	/* En cas d'erreur, un message est affiche et l'execution avortee */

	if (sem_wait(s) != 0)
	{
		perror("Errer attente sémaphore");
		exit(2);
	}

}

// Implanter l'operation V
void V(sem_t * s)
{
	/* A completer */
	/* En cas d'erreur, un message est affiche et l'execution avortee */

	if (sem_post(s) != 0)
	{
		perror("Errer libération sémaphore");
		exit(3);
	}
}

//---------------------------------------------------------------------
// Synchronisation a completer dans chacun des 3 threads
// en utilisant les operations P et V ecrites
//

//---------------------------------------------------------------------
// Fonction executee par le thread 1 : afficher A puis B
void *thd_1(void *arg)
{

	srand(pthread_self());

	for (;;)
	{
		P(&start_t1_from_t2);
		P(&start_t1_from_t3);
		attenteAleatoire();
		printf("A---\n");

		// give hand to t2 and t3
		V(&start_t2_t3);
		V(&start_t2_t3);

		P(&start_t1_from_t2);
		P(&start_t1_from_t3);
		attenteAleatoire();
		printf("B\n");

		attenteAleatoire();
	}
	pthread_exit((void *)NULL);
}

//---------------------------------------------------------------------
// Fonction executee par le thread 2 : afficher C
void *thd_2(void *arg)
{

	srand(pthread_self());

	for (;;)
	{
		P(&start_t2_t3);
		attenteAleatoire();
		printf("C\n");

		attenteAleatoire();
		// give hand to t1
		V(&start_t1_from_t2);
		V(&start_t1_from_t2);
	}
	pthread_exit((void *)NULL);
}

//---------------------------------------------------------------------
// Fonction executee par le thread 3 : afficher D
void *thd_3(void *arg)
{

	srand(pthread_self());

	for (;;)
	{
		P(&start_t2_t3);
		attenteAleatoire();
		printf("D\n");

		attenteAleatoire();
		// give hand to t1
		V(&start_t1_from_t3);
		V(&start_t1_from_t3);
	}
	pthread_exit((void *)NULL);
}

#define NB_THDS 3

//---------------------------------------------------------------------
int main(void)
{
	pthread_t idThds[NB_THDS];
	int etat;

	// Initialiser le(s) semaphore(s) utilise(s)
	sem_init(&start_t1_from_t2, 0, 1);
	sem_init(&start_t1_from_t3, 0, 1);
	sem_init(&start_t2_t3, 0, 0);

	// Lancer les threads
	if ((etat = pthread_create(&idThds[0], NULL, thd_1, NULL)) != 0)
		thdErreur(etat, "Creation thd 1", NULL);
	if ((etat = pthread_create(&idThds[1], NULL, thd_2, NULL)) != 0)
		thdErreur(etat, "Creation thd 2", NULL);
	if ((etat = pthread_create(&idThds[2], NULL, thd_3, NULL)) != 0)
		thdErreur(etat, "Creation thd 3", NULL);

	// Attendre leur fin
	if ((etat = pthread_join(idThds[0], NULL)) != 0)
		thdErreur(etat, "Join thread 1", NULL);
	if ((etat = pthread_join(idThds[1], NULL)) != 0)
		thdErreur(etat, "Join thread 2", NULL);
	if ((etat = pthread_join(idThds[2], NULL)) != 0)
		thdErreur(etat, "Join thread 3", NULL);

	// Detruire le(s) semaphore(s) utilise(s)
	sem_destroy(&start_t1_from_t2);
	sem_destroy(&start_t1_from_t3);
	sem_destroy(&start_t2_t3);

	printf("\nFin de l'execution du thread principal \n");
	return 0;
}
