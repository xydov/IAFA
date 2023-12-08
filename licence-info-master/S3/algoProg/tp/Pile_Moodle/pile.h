/*
 * Interface d'une pile statique.
 * Copyright (c) 2009-10 - Université Paul Sabatier
 * 
 * Vincent Dugat 2009-2010
 * H. Cassé, 2018
 */

/* Pour éviter les inclusions multiples */
#ifndef PILE_H
#define PILE_H

#include <stdbool.h>

#define PILE_TAILLE	100 /// taille maximale de la pile statique


/* ----------------------------------
        Déclaration des types
   --------------------------------*/
typedef struct pile_t {
    int elts[PILE_TAILLE];
    int tete;
} pile_t;

  
/* ----------------------------------
            Constructeurs
   --------------------------------*/

/**
 * Crée une pile vide.
 * @param p	Pile à initializer.
 */
void init_pile(pile_t *p);

/**
 * Empile un élément dans la pile.
 * La pile ne doit pas être pleine.
 * @param p		Pile où empiler.
 * @param e		Elément à empiler.
 */
void empiler(pile_t *p, int e);


/**
 * Dépile l'élément en tête de pile.
 * La pile ne doit pas être vide !
 * @param p	Pile à dépiler.
 */
void depiler(pile_t *p);


/* ----------------------------------
            Accesseurs
   --------------------------------*/

/**
 * Récupère le sommet de pile.
 * La pile ne doit pas être vide !
 * @param p		Pile à accéder.
 * @return		Elément en tête de pile.
 */
int sommet(const pile_t *p);

/**
 * Teste si la pile est vide.
 * @param p		Pile à tester.
 * @return		TRUE si la pile est vide, FALSE sinon.
 */
bool pile_vide(const pile_t *p);
 
/**
 * Test si la pile est elle pleine.
 * @param p		Pile à etster.
 * @return		TRUE si la pile est pleine, FALSE sinon.
 */
bool pile_pleine(const pile_t *p);

/**
 *  Affiche le contenu de la pile sur la stortie standard.
 * @param p		Pile à afficher.
 */
void afficher_pile(const pile_t *p);

#endif /* PILE_H */
