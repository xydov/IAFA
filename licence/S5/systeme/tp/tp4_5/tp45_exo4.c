/**
 * @file tp45_exo4.c
 * @author Tarek Kunze
 * @brief 
 * @version 0.1
 * @date 2020-12-06
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h> 


int **tubes;
int NBO = 1;
int NBC = 1;

typedef struct commande_s
{
    int *produit;
    pid_t client_pid;
} commande;

/**
 * @brief Gestion des erreur mettant a jour la variable errno
 * 
 * @param errorString la chaine de caractere decrivant l'erreur
 */
void handleError(char const *errorString)
{
    perror(errorString);
    exit(EXIT_FAILURE);
}

/**
 * @brief définit le comportement d'un processus ouvrier de numéro num
 * - Recoit un packet contenant une array et un client_pid
 * - modifie le packet et l'envoie au suivant
 * - if is_last() then 0 == kill(client->cliend_id, SIGUSR1)
 * 
 * @param num le numéro du processus ouvrier
 */
void ouvrier(int num)
{
    pid_t ouvrier_pid = getpid();
    commande commande_client;
    int err;
    // reception du colis du client
    close(tubes[num][1]);
    while ((err = read(tubes[num][0], &commande_client, sizeof(commande))) > 0)
    {
        printf("Ouvrier %d (%d) : Réception de la commande du client %d\n", num, ouvrier_pid, commande_client.client_pid);
        printf("\t<< Client de pid: %d ", commande_client.client_pid);
        for (int i = 0; i < NBO; i++)
        {
            printf("Infos[%d] = %d ", i, commande_client.produit[i]);
        }
        printf(">>\n");
        // modification du colis
        commande_client.produit[num] = num;
        // Si je suis le dernier ouvrier, Je previens le client avec SIGUSR1
        if (num == (NBO - 1))
        {
            sleep(2);
            printf("[Ouvrier n°%d]Je suis le dernier ouvrier :D\n", ouvrier_pid);
            if(kill(commande_client.client_pid, SIGKILL) == -1)
            {
                handleError("[Ouvrier] - Erreur envoie de SIGUSR1");
            }
            printf("==== Signal sent to client n°%d\n", commande_client.client_pid);
            exit(EXIT_SUCCESS);
        }
        // Sinon: j'envoie le colis au prochain ouvrier
        close(tubes[num + 1][0]);
        write(tubes[num + 1][1], &commande_client, sizeof(commande_client));
    }
    if (err == -1)
    {
        handleError("[Ouvrier] - Erreur lecture dans tube");
    }
    
    printf("[Ouvrier n°%d] - Je me termine\n", ouvrier_pid);
}

int wait_sig = 0;
void setWait(int s)
{
    if(s == SIGUSR1)
    {
        wait_sig = 1;
    }
    printf("****Signal received\n");
}

/**
 * @brief définit le comportement d'un processus client
 * - Envoie du colis a l'ouvrier n°1
 * - attente de la reception du colis [SIGUSR1]
 * - On SIGUSR1 then say("Client num (get_pid()) : Ma commande est arrivée !")
 * @param num le numero du processus client
 */
void client(int num)
{
    /* signaux */
    // creation du colis a envoyer au 1er ouvrier
    commande commande_client = {0};
    commande_client.client_pid = getpid();
    commande_client.produit = calloc(NBO, sizeof(int));
    for (int i = 0; i < NBO; i++)
    {
        commande_client.produit[i] = commande_client.client_pid;
    }
    // envoie du colis
    if(close(tubes[0][0]) == -1)
    {
        handleError("[Client] - Erreur fermeture cote lecture du pipe");
    }
    // printf("[Client n°%d || %d] - pre write...\n", commande_client.client_pid, num);
    if (write(tubes[0][1], &commande_client, sizeof(commande_client)) == -1)
    {
        char err[200];
        sprintf(err, "[Client n°%d] - Erreur lors de l'ecriture des donnees dans le tubes associee au premier ouvrier", commande_client.client_pid);
        handleError(err);
    }
    printf("Client %d (%d) : Commande envoyée à l’ouvrier 0... je vais l’attendre\n", num, commande_client.client_pid);
    // attente de la réception du colis
    pause();
    // sigsuspend(&mask);
    printf("============== Client %d (%d) : Ma commande est arrivée !\n", num, commande_client.client_pid);
    close(tubes[0][1]);
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage : %s <Nombre d'ouvrier> <Nombre de client>\n", argv[0]);
        exit(1);
    }

    /* Recuperation des parametres */
    NBO = atoi(argv[1]);
    NBC = atoi(argv[2]);
    
    /* Initialisation, ouverture des tubes */
    tubes = calloc(NBO, sizeof(int *));
    for (int i = 0; i < NBO; i++)
    {
        tubes[i] = calloc(2, sizeof(int));
        if (pipe(tubes[i]) == -1)
        {
            handleError("Erreur lors de la création de la creation des tubes");
        }
    }

    /* Creation des processus ouvrier */
    for (int i = 0; i < NBO; i++)
    {
        switch (fork())
        {
        case -1:
            handleError("Erreur lors de la creation des processus fils ouvrier");
            break;
        case 0:
            ouvrier(i);
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
        }
    }

    /* Creation des processus client */
    for (int i = 0; i < NBC; i++)
    {
        switch (fork())
        {
        case -1:
            handleError("Erreur lors de la creation des processus fils client");
            break;
        case 0:
            client(i);
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
        }
    }
    while(wait(NULL));
    

    /* free */
    for (int i = 0; i < NBO; i++)
    {
        free(tubes[i]);
    }

    free(tubes);
    return 0;
}