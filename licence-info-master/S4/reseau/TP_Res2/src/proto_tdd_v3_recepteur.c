/*************************************************************
* proto_tdd_v3 -  recepteur                                  *
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
/* Programme principal - récepteur */
/* =============================== */
int main(int argc, char *argv[])
{
    unsigned char message[MAX_INFO]; /* message pour l'application */
    paquet_t paquet;                 /* paquet utilisé par le protocole */
    paquet_t p_controle;             /* paquet de controle */
    int fin = 0;                     /* condition d'arrêt */

    int seq_attendu = 0;

    init_reseau(RECEPTION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* tant que le récepteur reçoit des données */
    while (!fin)
    {
        de_reseau(&paquet);

        if (verifier_controle(paquet) == ACK)
        {
            if (paquet.num_seq == seq_attendu)
            {
                for (int i = 0; i < paquet.lg_info; i++)
                {
                    message[i] = paquet.info[i];
                }
                p_controle.type = ACK;
                p_controle.num_seq = paquet.num_seq;
                p_controle.lg_info = 0;
                p_controle.somme_ctrl = generer_controle(p_controle);

                seq_attendu = inc(seq_attendu);
                fin = vers_application(message, paquet.lg_info);
                vers_reseau(&p_controle);
            }
        }
    }

    printf("[TRP] Fin execution protocole transport.\n");
    return 0;
}