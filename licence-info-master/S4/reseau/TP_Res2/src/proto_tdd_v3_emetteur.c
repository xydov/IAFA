/*************************************************************
* proto_tdd_v3 -  émetteur                                   *
* TRANSFERT DE DONNEES  v3                                   *
*                                                            *
* Transfert de donnée avec fenêtre d'anticipation et reprise *
* sur erreur   < Go-Back-N >                                 *
* T. KUNZE - Univ. de Toulouse III - Paul Sabatier           *
**************************************************************/

#include <stdio.h>
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"

/* =============================== */
/* Programme principal - émetteur  */
/* =============================== */
int main(int argc, char *argv[])
{
    unsigned char message[MAX_INFO]; /* message de l'application */
    int taille_msg;                  /* taille du message */
    
    paquet_t p_controle;             /* paquet de controle */


    int code_controle; 
    int taille_fenetre;
    int borne_inf;
    int curseur;
    int n_tempo = 0;
    int duree_tempo = 100;
    paquet_t tab[SEQ_NUM_SIZE];

    /* 
    printf("Taille de la fenêtre (Inférieur à %d): ", SEQ_NUM_SIZE);
    scanf("%d", &taille_fenetre);
    if ( taille_fenetre >= SEQ_NUM_SIZE )
    {
        fprintf(stderr, "Taille de la fenêtre incorrecte...\n");
        exit(2);
    } */

    init_reseau(EMISSION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    borne_inf = 0;
    curseur = 0;
    taille_fenetre = 4;

    /* tant que l'émetteur a des données à envoyer */
    
    do    
    {
        if (dans_fenetre(borne_inf, curseur, taille_fenetre))
        {
            /* lecture de donnees provenant de la couche application */
            de_application(message, &taille_msg);
            /* construction paquet */
            for (int i = 0; i < taille_msg; i++)
            {
                tab[curseur].info[i] = message[i];
            }
            tab[curseur].num_seq = curseur;
            tab[curseur].lg_info = taille_msg;
            tab[curseur].type = DATA;
            tab[curseur].somme_ctrl = generer_controle(tab[curseur]);
            vers_reseau(&tab[curseur]);

            if (borne_inf == curseur)
            {
                depart_temporisateur(n_tempo, duree_tempo);
            }
            curseur = inc(curseur);
        }
        else
        {
            code_controle = attendre();
            if (code_controle == PAQUET_RECU)
            {
                de_reseau(&p_controle);
                if (verifier_controle(p_controle) && dans_fenetre(borne_inf, p_controle.num_seq, taille_fenetre))
                {
                    // on décale la fenetre
                    borne_inf = inc(p_controle.num_seq);
                    arreter_temporisateur(0);
                    if (borne_inf != curseur)
                    {
                        // il reste des paquets non acquittés, on relance le timer
                        depart_temporisateur(n_tempo, duree_tempo);
                    }
                }
            }
            else
            {
                // Timeout: go-back-n
                int i = borne_inf;
                depart_temporisateur(n_tempo, duree_tempo);
                while (i != curseur)
                {
                    vers_reseau(&tab[i]);
                    i = inc(i);
                }
            }
        }
    } while (taille_msg != 0);


    printf("[TRP] Fin execution protocole transfert de donnees (TDD).\n");
    return 0;
}
