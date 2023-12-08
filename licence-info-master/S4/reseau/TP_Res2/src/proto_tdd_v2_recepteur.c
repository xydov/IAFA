/*************************************************************
* proto_tdd_v2 -  recepteur                                  *
* TRANSFERT DE DONNEES  v2                                   *
*                                                            *
* Transfert de donnée avec détection d'erreur et contrôle de *
* flux et reprise sur erreur   < Stop-and-wait >             *
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

    int prev_seq_n = -1;

    init_reseau(RECEPTION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* tant que le récepteur reçoit des données */
    while (!fin)
    {

        // attendre(); /* optionnel ici car de_reseau() fct bloquante */
        de_reseau(&paquet);

        p_controle.type = ACK;
        p_controle.num_seq = paquet.num_seq;
        
        if (verifier_controle(paquet) == ACK && paquet.type == DATA && paquet.num_seq != prev_seq_n)
        {
            /* extraction des donnees du paquet recu */
            for (int i = 0; i < paquet.lg_info; i++)
            {
                message[i] = paquet.info[i];
            }
            paquet.type = ACK;
            /* remise des données à la couche application */
            fin = vers_application(message, paquet.lg_info);
        }
        
        // envoie du paquet de controle a l'emetteur
        if (verifier_controle(paquet) == ACK && paquet.type == DATA)
        {
            vers_reseau(&p_controle);
        }

        prev_seq_n = paquet.num_seq;
    }

    printf("[TRP] Fin execution protocole transport.\n");
    return 0;
}