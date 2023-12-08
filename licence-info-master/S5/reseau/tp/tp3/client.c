/* =================================================================== */
// Progrmame Client à destination d'un joueur qui doit deviner la case
// du trésor. Après chaque coup le résultat retourné par le serveur est
// affiché. Le coup consite en une abcsisse et une ordonnée (x, y).
/* =================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

//////////////////////////////////////////////////////////////
#define N 10
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"

/* ====================================================================== */
/*                  Affichage du jeu en mode texte brut                   */
/* ====================================================================== */
void afficher_jeu(int jeu[N][N], int res, int points, int coups) {

    printf("\n************ TROUVEZ LE TRESOR ! ************\n");
    printf("    ");
    for (int i=0; i<10; i++)
        printf("  %d ", i+1);
    printf("\n    -----------------------------------------\n");
    for (int i=0; i<10; i++){
        printf("%2d  ", i+1);
        for (int j=0; j<10; j++) {
            printf("|");
            switch (jeu[i][j]) {
                case -1:
                    printf(" 0 ");
                    break;
                case 0:
                    printf(GREEN " T " RESET);
                    break;
                case 1:
                    printf(YELLOW " %d " RESET, jeu[i][j]);
                    break;
                case 2:
                    printf(RED " %d " RESET, jeu[i][j]);
                    break;
                case 3:
                    printf(MAGENTA " %d " RESET, jeu[i][j]);
                    break;
            }
        }
        printf("|\n");
    }
    printf("    -----------------------------------------\n");
    printf("Pts dernier coup %d | Pts total %d | Nb coups %d\n", res, points, coups);
}


///////////////////////////////////////////////////////////////


#define SERVER_PORT 5555
#define SERVER_ADDRESS "127.0.0.1"
// #define SERVER_ADDRESS "146.59.237.169"

void close_socket(int * socket_id)
{
    if(close(*socket_id) == -1)
    {
        perror("[CLIENT] - Erreur lors de la fermeture de la connexion distante");
        exit(EXIT_FAILURE);
    }
}

void create_socket(int * socket_id)
{
    // 1. creation
    (*socket_id) = socket(AF_INET, SOCK_STREAM, 0);
    if ( (*socket_id) == -1 )
    {
        perror("[CLIENT] - Erreur lors de la creation du socket");
        exit(EXIT_FAILURE);
    }
    // 2. binding done automatically with tcp
    // struct sockaddr_in sk_addr;

    // 3. connect to a distant server
    struct sockaddr_in distant_server;
    memset(&distant_server, 0, sizeof(distant_server));
    distant_server.sin_family = AF_INET;
    distant_server.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_ADDRESS, &(distant_server.sin_addr));
    if( connect(*socket_id, (struct sockaddr*)&distant_server, sizeof(distant_server)) == -1 )
    {
        perror("[CLIENT] - Erreur lors de l'etablissement de la connexion avec le serveur distant");
        close_socket(socket_id);
        exit(EXIT_FAILURE);
    }
    printf("[log] - Etablissement de la connexion reussite\n");
}

void send_receive_loop(int * socket_id, int argc, char **argv)
{
    int jeu[N][N];
    int lig, col;
    char buffer[8];

    int res = -1, points = 0, coups = 0; 
    /* Init jeu */
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            jeu[i][j] = -1;
        }
    }

    /* Tentatives du joueur : stoppe quand tresor trouvé */
    do {
        afficher_jeu(jeu, res, points, coups);
        printf("\nEntrer le numéro de ligne : ");
        scanf("%d", &lig);
        printf("Entrer le numéro de colonne : ");
        scanf("%d", &col);

        //  prepare data
        sprintf(buffer, "%d %d", lig, col);
        /*-----------------------------*/
        /* connected to distant / local server*/
        // send and receive loop
        send(*socket_id, buffer, sizeof(buffer), 0);
        // read(*socket_id, buffer, sizeof(buffer));

        recv(*socket_id, buffer, sizeof(buffer), 0);
        /*-----------------------------*/
        sscanf(buffer, "%d", &res);

        /* Mise à jour */
        if (lig>=1 && lig<=N && col>=1 && col<=N)
            jeu[lig-1][col-1] = res;
        points += res;
        coups++;

    } while (res);

    /* Terminaison du jeu : le joueur a trouvé le tresor */
    afficher_jeu(jeu, res, points, coups);
    printf("\nBRAVO : trésor trouvé en %d essai(s) avec %d point(s)"
            " au total !\n\n", coups, points);
}


/* ====================================================================== */
/*                    Fonction principale                                 */
/* ====================================================================== */
int main(int argc, char **argv) {

    int socket_id;

    create_socket(&socket_id);
    send_receive_loop(&socket_id, argc, argv);
    close_socket(&socket_id);

    return 0;
}

/*

- etablissement de la connexion
- transfert de données
- terminaison de la connexion

- establishing con:
    while !=0
    -> send
    <- receive
- closing connexion


send lig col
*/