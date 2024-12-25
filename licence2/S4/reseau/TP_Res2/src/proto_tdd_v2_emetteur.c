/*************************************************************
* proto_tdd_v2 -  émetteur                                   *
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
/* Programme principal - émetteur  */
/* =============================== */
int main(int argc, char *argv[])
{
    unsigned char message[MAX_INFO]; /* message de l'application */
    int taille_msg;                  /* taille du message */
    paquet_t paquet;                 /* paquet utilisé par le protocole */
    paquet_t p_controle;             /* paquet de controle */

    int n_tempo;
    int code_retour;
    int num_sequence = 0;

    init_reseau(EMISSION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* lecture de donnees provenant de la couche application */
    de_application(message, &taille_msg);

    /* tant que l'émetteur a des données à envoyer */
    while (taille_msg != 0)
    {
        n_tempo = 0;

        /* construction paquet */
        for (int i = 0; i < taille_msg; i++)
        {
            paquet.info[i] = message[i];
        }
        paquet.lg_info = taille_msg;
        paquet.type = DATA;
        // ajout n° de séquence
        paquet.num_seq = num_sequence;
        /* generation du controle */
        paquet.somme_ctrl = generer_controle(paquet);
        
        /* remise à la couche reseau */
        do
        {
            vers_reseau(&paquet);
            depart_temporisateur(n_tempo, 200);
            code_retour = attendre();
            n_tempo ++;
        } while (code_retour != PAQUET_RECU && n_tempo <= 31);

        do
        {
            code_retour = attendre();
            de_reseau(&p_controle);
        } while (p_controle.num_seq != paquet.num_seq);

        if (code_retour == PAQUET_RECU && p_controle.num_seq == paquet.num_seq)
        {
            arreter_temporisateur(n_tempo-1);
            /* lecture des donnees suivantes de la couche application */
            de_application(message, &taille_msg);
        }
        num_sequence ++;
    }

    printf("[TRP] Fin execution protocole transfert de donnees (TDD).\n");
    return 0;
}
