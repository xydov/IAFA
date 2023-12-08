/**-------------------------------------------------------------------------
  TP1 - Squelette code exercice 2
--------------------------------------------------------------------------**/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define NB_THREADS_MAX 10


/*------------------------------------------------------------------------
 * Structure contennant les arguments
  ------------------------------------------------------------------------*/
struct s_args
{
	int rang;
};

struct s_exit_args
{
	pthread_t id;
	int val_retour;
};


/*------------------------------------------------------------------------
 * Affichage de l'identite de l'appelant 
  ------------------------------------------------------------------------*/
void afficher(int rang, pthread_t thdId, int valeurDeRetour)
{
	printf("Thread compagnon de rang %d, identifié par %lu, je mourrai en retournant %d\n", rang, thdId, valeurDeRetour);
}

/*------------------------------------------------------------------------
 Fonction d'affichage d'une erreur selon la cause de l'echec d'une primitive
 Arret du thread si arret positionne a 1
  ------------------------------------------------------------------------*/
void thdErreur(char *msg, int cause, int arret)
{
	printf("%s : %s \n", msg, strerror(cause));
	if (arret)
	{
		pthread_exit(NULL);
	}
}

/*------------------------------------------------------------------------
	Code execute par chaque thread 
-----------------------------------------------------------------------*/

void *thd_afficher(void *arg)
{
	int rang = (((struct s_args *)arg)->rang);

	// struct containing the values returned byt he thread
	struct s_exit_args * ea = malloc(sizeof(struct s_exit_args));
	ea->id = pthread_self();
	ea->val_retour = rand() % 100;
	
	afficher( rang, ea->id, ea->val_retour );
	
	// struct used, can be freed now
	free(arg);
	pthread_exit(ea);
}



/*------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
	// init pseudo random gen
	srand(time(NULL));
	int i, nbThreads, etat;
	pthread_t idThreads[NB_THREADS_MAX];

	if (argc != 2)
	{
		printf("Usage : %s <Nb Threads>\n", argv[0]);
		exit(1);
	}
	nbThreads = atoi(argv[1]);
	if (nbThreads > NB_THREADS_MAX)
	{
		nbThreads = NB_THREADS_MAX;
	}
	
	/* Creation des threads */
	for (i = 0; i < nbThreads; i++)
	{
		struct s_args * arguments = malloc(sizeof(struct s_args));
		arguments->rang = i;
		if ((etat = pthread_create(&idThreads[i], NULL, thd_afficher, (void *)(arguments))) != 0) // explicit cast to voids, creating a copy
		{
			thdErreur("Echec create", etat, 0);
			// free struct if thread creation fails
			free(arguments);
		}
		// 	do not free structure here, 
		//	can lead to structure freed while thd_afficher() did not finished accessing the data
	}

	struct s_exit_args ** ea = malloc(nbThreads * sizeof(struct s_exit_args *));
	int total = 0;
	/* Attendre la fin des threads  */
	for (i = 0; i < nbThreads; i++)
	{
		if ((etat = pthread_join(idThreads[i], (void**)&ea[i])) != 0)
		{
			thdErreur("Echec join", etat, 0);
		}
		printf("Thread principal %lu : valeur retourné par le thread %lu  = %d\n", pthread_self(), ea[i]->id, ea[i]->val_retour);
		total += ea[i]->val_retour;
		free(ea[i]);
	}
	printf("Thread principal %lu : somme des valeurs reçues = %d\n", pthread_self(), total);

	free(ea);
	return 0;
}
