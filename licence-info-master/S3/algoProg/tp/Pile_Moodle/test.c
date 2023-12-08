/*
 * 26 09 2011
 * Utilisation de la pile statique d'entier.
 */


#include <stdio.h>
#include <stdbool.h>

/* includes "application" */
#include "test.h"
#include "pile.h"

/**
 * Entrer une pile au clavier.
 * @param p		Pile à saisir.
 */
void saisir_pile(pile_t *p) {
	int i;
	int nb;
    
    /* entrer le nombre d'éléments */
	printf("Taper le nombre d'elements de la pile :\n");
	scanf("%d", &nb);
	
	/* entrer les éléments de la pile */
	for(i = 0; i < nb; i = i + 1) {
		int x;
		printf("élément %d:\n", i);
		scanf("%d", &x);
		empiler(p, x);
	}
}

/**
 * Programme principal.
 */
int main(void) {
	INIT_TEST;
	
	pile_t p;
	init_pile(&p);

	TEST(pile_vide(&p));
	
	empiler(&p, 111);
	TEST(!pile_vide(&p));
	TEST(sommet(&p) == 111);
	
	depiler(&p);
	TEST(pile_vide(&p));

	empiler(&p, 0);
	TEST(!pile_vide(&p));
	TEST(sommet(&p) == 0);
	empiler(&p, 1);
	TEST(!pile_vide(&p));
	TEST(sommet(&p) == 1);
	depiler(&p);
	TEST(!pile_vide(&p));
	TEST(sommet(&p) == 0);
	depiler(&p);
	TEST(pile_vide(&p));	
	
	empiler(&p, 0);
	TEST(!pile_vide(&p));
	TEST(sommet(&p) == 0);
	empiler(&p, 1);
	TEST(!pile_vide(&p));
	TEST(sommet(&p) == 1);
	empiler(&p, 2);
	TEST(!pile_vide(&p));
	TEST(sommet(&p) == 2);
	depiler(&p);
	TEST(!pile_vide(&p));
	TEST(sommet(&p) == 1);
	empiler(&p, 3);
	TEST(!pile_vide(&p));
	TEST(sommet(&p) == 3);
	depiler(&p);
	TEST(!pile_vide(&p));
	TEST(sommet(&p) == 1);
	depiler(&p);
	TEST(!pile_vide(&p));
	TEST(sommet(&p) == 0);
	depiler(&p);
	TEST(pile_vide(&p));	
	
	for(int i = 0; i < PILE_TAILLE; i++)
		empiler(&p, i);
	TEST(!pile_vide(&p));
	TEST(pile_pleine(&p));
	TEST(sommet(&p) == PILE_TAILLE - 1);
	for(int i = 0; i < PILE_TAILLE; i++)
		depiler(&p);
	TEST(pile_vide(&p));
	TEST(!pile_pleine(&p));
	
	FIN_TEST;
	return(0);
}














