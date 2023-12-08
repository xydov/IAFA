/*
 * Interface d'une pile statique.
 * Copyright (c) 2009-10 - Universit� Paul Sabatier
 * 
 * Vincent Dugat 2009-2010
 * H. Cass�, 2018
 */

/* Pour �viter les inclusions multiples */
#ifndef PILE_H
#define PILE_H

#include <stdbool.h>

#define PILE_TAILLE	100 /// taille maximale de la pile statique


/* ----------------------------------
        D�claration des types
   --------------------------------*/
typedef struct pile_t {
    int elts[PILE_TAILLE];
    int tete;
} pile_t;

  
/* ----------------------------------
            Constructeurs
   --------------------------------*/

/**
 * Cr�e une pile vide.
 * @param p	Pile � initializer.
 */
void init_pile(pile_t *p);

/**
 * Empile un �l�ment dans la pile.
 * La pile ne doit pas �tre pleine.
 * @param p		Pile o� empiler.
 * @param e		El�ment � empiler.
 */
void empiler(pile_t *p, int e);


/**
 * D�pile l'�l�ment en t�te de pile.
 * La pile ne doit pas �tre vide !
 * @param p	Pile � d�piler.
 */
void depiler(pile_t *p);


/* ----------------------------------
            Accesseurs
   --------------------------------*/

/**
 * R�cup�re le sommet de pile.
 * La pile ne doit pas �tre vide !
 * @param p		Pile � acc�der.
 * @return		El�ment en t�te de pile.
 */
int sommet(const pile_t *p);

/**
 * Teste si la pile est vide.
 * @param p		Pile � tester.
 * @return		TRUE si la pile est vide, FALSE sinon.
 */
bool pile_vide(const pile_t *p);

/**
 * Test si la pile est elle pleine.
 * @param p		Pile � etster.
 * @return		TRUE si la pile est pleine, FALSE sinon.
 */
bool pile_pleine(const pile_t *p);

/**
 *  Affiche le contenu de la pile sur la stortie standard.
 * @param p		Pile � afficher.
 */
void afficher_pile(const pile_t *p);

#endif /* PILE_H */
