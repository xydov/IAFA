/***********************************************************
*      Simulation d'une PILE  PHYSIQUE-RESEAU              *
*                                                          *
* (v 1.5, Jan. 2020)                                       *
* P. Torguet & E. Lavinal                                  *
* Université de Toulouse III - Paul Sabatier               *
************************************************************/

#include <stdio.h>
#include <string.h>
#include "config.h"
#include "services_reseau.h"

#define NBR_MAX_TIMERS 32

#if defined(UNIX)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define RED "\x1B[31m"
#define NRM "\x1B[0m"

#else

#include <winsock2.h>

#endif

#include <time.h>

/* Variables cachees */

/* Socket */
#ifndef UNIX
SOCKET physique_socket;
#else
int physique_socket;
#endif

/* Timers */
typedef struct my_timer_t
{
    int num_timer;
    int exp;
} my_timer_t;

my_timer_t timers[NBR_MAX_TIMERS + 1];
int nb_timers = 0;
int physique_initialise = 0;

/* proba de perte */
float physique_proba_perte = 0;
/* proba d'erreurs */
float physique_proba_erreur = 0;

/* perte connexion ou deconnexion */
// int perte_connexion = 0;
// int perte_deconnexion = 0;

/* nom de la machine destination */
char *physique_destination = NULL;
short physique_port_local = 2000;
short physique_port_destination = 2001;

/******************************************************************************
* Initialisation avec un taux de perte
*                        taux d'erreurs et
*                        parametres reseau
*******************************************************************************/
void initialisation(float proba_perte, float proba_erreur,
                    unsigned short port_local, char *destination,
                    unsigned short port_dest)
{

    struct sockaddr_in adr_locale;

#ifndef UNIX
    WSADATA wsaData;
#endif

    physique_initialise = 1;

    physique_proba_perte = proba_perte;
    physique_proba_erreur = proba_erreur;
    physique_destination = strdup(destination);
    physique_port_local = port_local;
    physique_port_destination = port_dest;

    srand((unsigned)time(NULL));

#ifndef UNIX
    if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR)
    {
        printf("WSAStartup() erreur : %d\n", WSAGetLastError());
        WSACleanup();
        exit(1);
    }
#endif

    physique_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (physique_socket < 0)
    {
#ifndef UNIX
        printf("socket() erreur : %d\n", WSAGetLastError());
        WSACleanup();
#else
        perror("socket() erreur : ");
#endif
        exit(1);
    }

    adr_locale.sin_port = htons(physique_port_local);
    adr_locale.sin_family = AF_INET;
    adr_locale.sin_addr.s_addr = INADDR_ANY;

    if (bind(physique_socket, (struct sockaddr *)&adr_locale,
             sizeof(adr_locale)) < 0)
    {
#ifndef UNIX
        printf("bind() erreur : %d\n", WSAGetLastError());
        WSACleanup();
#else
        perror("bind() erreur : ");
        close(physique_socket);
#endif
        exit(1);
    }

    /* initialisation timers : pas de timers */
    nb_timers = 0;
}

/******************************************************************************
 * Initialisation simple avec un sens de communication
 * Si reception == 1 alors côté réception sinon côté émission.
 *****************************************************************************/
void init_reseau(int reception)
{
    float proba_perte = 0;
    float proba_erreur = 0;
    unsigned short port_local;
    unsigned short port_distant;
#ifdef UNIX
    uid_t uid = getuid();
#else
    int uid = 1;
#endif
    if (reception)
    {
        proba_perte = conf_proba_perte(RECEPTION);
        proba_erreur = conf_proba_erreur(RECEPTION);
        // perte_connexion = conf_perte_connexion(PERTE_CONNEXION_REP);
        // perte_deconnexion = conf_perte_connexion(PERTE_DECONNEXION_ACK);
        port_local = (short)(uid % 60000 + 2000);
        port_distant = (short)(uid % 60000 + 3000);
    }
    else
    {
        proba_perte = conf_proba_perte(EMISSION);
        proba_erreur = conf_proba_erreur(EMISSION);
        // perte_connexion = conf_perte_connexion(PERTE_CONNEXION_REQ);
        // perte_deconnexion = conf_perte_connexion(PERTE_DECONNEXION);
        port_local = (short)(uid % 60000 + 3000);
        port_distant = (short)(uid % 60000 + 2000);
    }

    printf("[PHY] On utilise le port local %d et le port distant %d\n",
           port_local, port_distant);

    initialisation(proba_perte, proba_erreur, port_local, "localhost", port_distant);
}

/*******************************************************************************
 * Initialisation en mode réparti (i.e. l'émetteur et le récepteur sont sur des
 * machines distinctes)
 * Si reception == 1 alors côté réception sinon côté émission.
 ******************************************************************************/
void init_reseau_mode_reparti(int reception, unsigned short port_local,
                              char *hote_distant, unsigned short port_distant)
{

    float proba_perte = 0;
    float proba_erreur = 0;

    if (reception)
    {
        proba_perte = conf_proba_perte(RECEPTION);
        proba_erreur = conf_proba_erreur(RECEPTION);
        // perte_connexion = conf_perte_connexion(PERTE_CONNEXION_REP);
        // perte_deconnexion = conf_perte_connexion(PERTE_DECONNEXION_ACK);
    }
    else
    {
        proba_perte = conf_proba_perte(EMISSION);
        proba_erreur = conf_proba_erreur(EMISSION);
        // perte_connexion = conf_perte_connexion(PERTE_CONNEXION_REQ);
        // perte_deconnexion = conf_perte_connexion(PERTE_DECONNEXION);
    }

    printf("[PHY] On utilise le port local %d, l'hote distant %s et le port distant %d\n",
           port_local, hote_distant, port_distant);

    initialisation(proba_perte, proba_erreur, port_local, hote_distant, port_distant);
}

/******************************************************************************
 * Attends un evenement et retourne :
 *    + (-1) si un paquet recu est disponible
 *    + un numero de timer si un timeout a été généré
 *****************************************************************************/
int attendre()
{

    fd_set read_fs;
    struct timeval timeout;
    struct timeval *ptimeout;
    int rep;
    int fini = 0;
    int i;
    int resultat = -1;
    int taille_fd_set;

    if (!physique_initialise)
    {
        printf("Attention, le canal n'etait pas initialise\n");
        initialisation(0.f, 0.f, 2000, "localhost", 2001);
    }

    while (!fini)
    {
        /* voyons s'il n'y a pas un timer expire */
        i = 0;
        while (i < nb_timers)
        {
            if (timers[i].exp == 0)
            {
                int timer = timers[i].num_timer;
                /* ecrasons ce timer */
                for (; i < nb_timers - 1; i++)
                {
                    timers[i].num_timer = timers[i + 1].num_timer;
                    timers[i].exp = timers[i + 1].exp;
                }
                nb_timers--;
                return timer;
            }
            i++;
        }

        if (nb_timers > 0)
        {
            timeout.tv_sec = 0;
            timeout.tv_usec = 100000; /* 100000 us = 100 ms */
            ptimeout = &timeout;
        }
        else
            ptimeout = NULL;

        FD_ZERO(&read_fs);
        FD_SET(physique_socket, &read_fs);

#ifndef UNIX
        taille_fd_set = 1;
#else
        taille_fd_set = physique_socket + 1;
#endif
        // on vérifie les timers toutes les 100 ms (ptimeout)
        rep = select(taille_fd_set, &read_fs, NULL, NULL, ptimeout);
        switch (rep)
        {
        case -1:
#ifndef UNIX
            printf("select() n'a pas fonctionne, erreur : %d\n", WSAGetLastError());
            WSACleanup();
#else
            perror("select() n'a pas fonctionnee : ");
            close(physique_socket);
#endif
            exit(1);
        case 0:
            /* timeout ? */
            i = 0;
            while (i < nb_timers)
            {
                if (timers[i].exp > 0)
                {
                    timers[i].exp -= 100;
                    if (timers[i].exp < 0)
                        timers[i].exp = 0;
                }
                i++;
            }
            break;
        default:
            /* reception possible */
            /* printf ("action de %d descripteur\n", rep); */
            if (FD_ISSET(physique_socket, &read_fs))
            {
                fini = 1;
                resultat = -1;
            }
        }
    }

    return resultat;
}

/*******************************************************************************
 * Recoit un paquet de type paquet_t
 ******************************************************************************/
void de_reseau(paquet_t *paquet)
{

    int l_data;
    if (!physique_initialise)
    {
        printf("Attention, le canal n'était pas initialisé\n");
        initialisation(0.f, 0.f, 2000, "localhost", 2001);
    }

    l_data = recvfrom(physique_socket, (char *)paquet, sizeof(paquet_t), 0, NULL, NULL);
    if (l_data < 0)
    {
#ifndef UNIX
        printf("recvfrom() erreur : %d\n", WSAGetLastError());
        WSACleanup();
#else
        perror("recvfrom() erreur : ");
        close(physique_socket);
#endif
        exit(1);
    }
    printf("[PHY] paquet recu\n");
}

/*******************************************************************************
 * Envoie un paquet de type paquet_t
 ******************************************************************************/
void vers_reseau(paquet_t *paquet)
{

    struct hostent *host;
    struct sockaddr_in adresse_dest;
    int l_adr = sizeof(adresse_dest);
    int l_data;
    paquet_t *new_paquet;

    if (!physique_initialise)
    {
        printf("Attention, le canal n'était pas initialisé\n");
        initialisation(0.f, 0.f, 2001, "localhost", 2000);
    }

    // /* perte demande connexion ? */
    // if (paquet->type == CON_REQ && perte_connexion)
    // {
    //     printf("%s[PHY] perte de paquet%s\n", RED, NRM);
    //     perte_connexion = 0; /* on ne perd qu'une fois */
    //     return;
    // }
    //
    // /* perte reponse connexion ? */
    // if (paquet->type == CON_ACCEPT && perte_connexion)
    // {
    //     printf("%s[PHY] perte de paquet%s\n", RED, NRM);
    //     perte_connexion = 0; /* on ne perd qu'une fois */
    //     return;
    // }
    //
    // /* perte deconnexion ? */
    // if (paquet->type == CON_CLOSE && perte_deconnexion)
    // {
    //     printf("%s[PHY] perte de paquet%s\n", RED, NRM);
    //     perte_deconnexion = 0; /* on ne perd qu'une fois */
    //     return;
    // }
    //
    // /* perte ack deconnexion ? */
    // if (paquet->type == CON_CLOSE_ACK && perte_deconnexion)
    // {
    //     printf("%s[PHY] perte de paquet%s\n", RED, NRM);
    //     perte_deconnexion = 0; /* on ne perd qu'une fois */
    //     return;
    // }

    /* perte ? */
    if (rand() / (float)RAND_MAX < physique_proba_perte)
    {
        printf("%s[PHY] perte de paquet%s\n", RED, NRM);
        return;
    }

    /* copie du paquet (utile si generation d'une erreur) */
    new_paquet = malloc(sizeof(paquet_t));
    memcpy(new_paquet, paquet, sizeof(paquet_t));

    /* erreur ? */
    if (rand() / (float)RAND_MAX < physique_proba_erreur)
    {
        printf("%s[PHY] generation d'une erreur dans la paquet%s\n", RED, NRM);
        /* Complement à 1 du 1er octet du champ info : */
        new_paquet->info[0] = ~(new_paquet->info[0]);
        /* +1 sur le num_seq : */
        new_paquet->num_seq++;
    }

#ifndef UNIX
    /* calcul de l'adresse de destination */
    /* testons voir si ce n'est pas une @ IP en notation décimale (eg 141.115.20.90) */
    adresse_dest.sin_addr.s_addr = inet_addr(physique_destination);
    if (adresse_dest.sin_addr.s_addr == INADDR_NONE)
    {
#endif
        /* ce doit être un nom */
        host = gethostbyname(physique_destination);

        if (host == NULL)
        {
#ifndef UNIX
            printf("gethostbyname() erreur : %d\n", WSAGetLastError());
            WSACleanup();
#else
            perror("gethostbyname() erreur : ");
            close(physique_socket);
#endif
            exit(1);
        }

        memcpy((void *)&(adresse_dest.sin_addr), (void *)host->h_addr_list[0], host->h_length);
#ifndef UNIX
    }
#endif

    adresse_dest.sin_port = htons(physique_port_destination);
    adresse_dest.sin_family = AF_INET;

    l_data = sendto(
        physique_socket,
        (char *)new_paquet, sizeof(paquet_t), 0,
        (struct sockaddr *)&adresse_dest, l_adr);

    if (l_data < 0)
    {
#ifndef UNIX
        printf("sendto() n'a pas fonctionne, erreur : %d\n", WSAGetLastError());
        WSACleanup();
#else
        perror("sendto() n'a pas fonctionnée : ");
        close(physique_socket);
#endif
        exit(1);
    }
    free(new_paquet);
    printf("[PHY] paquet envoyé\n");
}

/**************************************************************************
 * Demarre le timer numero n (0 <= n <= NBR_MAX_TIMERS-1) qui s'arrete    *
 * apres ms millisecondes (ms doit etre un multiple de 100)               *
 **************************************************************************/
void depart_temporisateur(int n, int ms)
{
    int i = 0;
    if (n < 0 || n > NBR_MAX_TIMERS-1)
    {
        printf("%s[PHY] Le num timer (%d) n'est pas correct.%s\n", RED, n, NRM);
        return;
    }

    /* cherche le timer */
    while (i < nb_timers)
    {
        if (timers[i].num_timer == n)
        {
            printf("%s[PHY] Le timer (%d) est deja demarre.%s\n", RED, n, NRM);
            return;
        }
        i++;
    }

    /* ok, il n'est pas deja utilise */
    timers[nb_timers].num_timer = n;
    timers[nb_timers].exp = ms;
    nb_timers++;
}

/*********************************************************
 * Vérification si le timer numéro n est en marche       *
 * Retour :  1 si le timer numéro n est en route         *
 *           0 sinon                                     *
 *********************************************************/
int test_temporisateur(int n)
{
    for (int i = 0; i < nb_timers; i++)
    {
        if (timers[i].num_timer == n)
        {
            return 1;
        }
    }
    return 0;
}

/****************************
 * Arrete le timer numero n *
 ****************************/
void arreter_temporisateur(int n)
{
    int i = 0;

    if (n < 0 || n > NBR_MAX_TIMERS-1)
    {
        printf("%s[PHY] Le num timer (%d) n'est pas correct.%s\n", RED, n, NRM);
        return;
    }

    /* cherche le timer */
    while (i < nb_timers)
    {
        if (timers[i].num_timer == n)
        {
            /* ecrasons ce timer */
            for ( ; i < nb_timers - 1; i++)
            {
                timers[i].num_timer = timers[i + 1].num_timer;
                timers[i].exp = timers[i + 1].exp;
            }
            nb_timers--;
            return;
        }
        i++;
    }

    if (i == nb_timers)
        printf("%s[PHY] Le timer (%d) n'est pas demarre.%s\n", RED, n, NRM);
}

// void depart_temporisateur(int ms)
// {
//     depart_temporisateur_num(1, ms);
// }

// void arreter_temporisateur()
// {
//     arreter_temporisateur_num(1);
// }
