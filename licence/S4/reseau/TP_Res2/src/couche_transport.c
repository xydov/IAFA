#include <stdio.h>
#include "couche_transport.h"
#include "services_reseau.h"

/* ************************************** */
/* Fonctions utilitaires couche transport */
/* ************************************** */

/* Ajouter ici vos fonctions utilitaires
 * (generer_controle, verifier_controle...)
 */

uint8_t generer_controle(paquet_t p)
{
    int somme = 0;

    somme^=p.type;
    somme^=p.num_seq;
    somme^=p.lg_info;

    for (int i = 0; i < p.lg_info; i++)
    {
        somme ^= p.info[i];
    }
    return somme;
}

int verifier_controle(paquet_t p)
{
    if (p.somme_ctrl == generer_controle(p))
    {
        return ACK;
    }
    return NACK;
}

/* ======================================================================= */
/* =================== Fenêtre d'anticipation ============================ */
/* ======================================================================= */

/*--------------------------------------*/
/* Fonction d'inclusion dans la fenetre */
/*--------------------------------------*/
int dans_fenetre(unsigned int inf, unsigned int pointeur, int taille) {

    unsigned int sup = (inf+taille-1) % SEQ_NUM_SIZE;

    return
        /* inf <= pointeur <= sup */
        ( inf <= sup && pointeur >= inf && pointeur <= sup ) ||
        /* sup < inf <= pointeur */
        ( sup < inf && pointeur >= inf) ||
        /* pointeur <= sup < inf */
        ( sup < inf && pointeur <= sup);
}


int inc(int value)
{
    return (value + 1) % SEQ_NUM_SIZE;
}
