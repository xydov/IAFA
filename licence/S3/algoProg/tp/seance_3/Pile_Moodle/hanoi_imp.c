#include <stdio.h>
#include <stdbool.h>
#include "pile.h"

typedef pile_t Jeu[3];

/**
 * Effectue l'algorithme de Hanoi
 * sur un tableau de pile avec N anneau
 * @param tab	Tableau de pile à accéder.
 * @param n     Nombre d'anneau à déplacer
 */
void hanoi(){}


/**
 * Déplace un anneau et affiche le déplacement effectué
 * @param N     Nombre d'anneau à déplacer
 * @param tours La liste de tour
 */
void deplacerAnneau(Jeu tours, int depart, int arrivee) {
    int sommetTour = sommet(&tours[depart]);
    depiler(&tours[depart]);
    empiler(&tours[arrivee], sommetTour);

    printf("Déplacement de %d vers %d : valeur = %d\n", depart, arrivee, sommetTour);
}


/**
 * Initialise le jeu
 * @param N     Nombre d'anneau à déplacer
 * @param tours La liste de tour
 */
void initialiserJeu(int N, Jeu tours) {
    for(int i = 0; i < 3; i++) {
        init_pile(&tours[i]);
    }
    for(int i = N; i > 0; i --) {
        empiler(&tours[0], i);
    }
}


/**
 * Vérifie si un certain anneau est déplacable
 * @param tours     La liste de tour
 * @param depart    pile de départ
 * @param arrivee   pile d'arrivee
 * @return          Valeur Booleene
*/
bool deplacementPossible(Jeu tours, int depart, int arrivee) {
    return (!pile_vide(&tours[depart])) && (pile_vide(&tours[arrivee])
        || sommet(&tours[depart]) < sommet(&tours[arrivee]));
}


/**
 * Affiche chaque pile sur une ligne
 * @param tours La liste de tour
 */
void afficherJeu(Jeu tours) {
    for(int i = 0; i < 3; i++) {
        afficher_pile(&tours[i]);
    }
}


int main(void) {
    int nbDisques;
    Jeu jeu;

    printf("N = ");
    scanf("%d", &nbDisques);
    

    initialiserJeu(nbDisques, jeu);
    afficherJeu(jeu);
    printf(deplacementPossible(&jeu, 0, 1) ? "Déplacement possible\n" : "/!\\ Deplacement impossible\n");
    deplacerAnneau(jeu, 1, 0);

    //    hanoi(Jeu, nbDisques);
    afficherJeu(jeu);
    return 0;
}