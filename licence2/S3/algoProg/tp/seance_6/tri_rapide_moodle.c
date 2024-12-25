/**
 * \brief Tests sur les tris avec mesure du temps
 * \brief usage : nom_du_prog nom_du_fichier [limite] o� limite dit de ne consid�rer que les limite premiers nombres du fichier �r d�faut limite = 100
 *
 * \author Jean-Paul Bahsoun, Vincent Dugat, Pierre Piccinini
 * \date septembre 2016, septembre 2017
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "pile.h"
#define TMAX 300000 // dimension maximale des tableaux

typedef int tableau[TMAX];

void echanger(int *a,int *b) // swap
{
    int aux=*a;
    *a=*b;
    *b=aux;
}

void afficher_tab( tableau t , int dim)
{
    int i;
    for (i=0;i<dim;i++)
        printf("%4d",t[i]);
    printf("\n");
}

/* remplit le tableau avec les dim entiers d'un fichier
s'il n'y a pas assez d'entiers dans le fichier :  le programme stoppe
*/
void tab_fichier(tableau t,int dim, char *nom)
{
    int i;
    FILE * f_in;
    f_in = fopen(nom,"r") ;
    if (f_in == NULL)
        {  fprintf(stderr,"\n Erreur : Impossible d ouvrir le fichier %s\n",nom) ;    exit(EXIT_FAILURE) ;}
    for (i=0;i<dim;i++)
    {
		fscanf(f_in,"%d",&t[i]) ;
		if (feof(f_in))
        {printf("Erreur: Pas assez d'entiers dans le fichier %s\n",nom);  exit(EXIT_FAILURE);}
    }
    fclose(f_in);
}

// copie de dim �l�ments de T1 dans t2
void initCopieTab(tableau t1, tableau t2, int dim){
    int i;
    for(i=0;i<dim;i++) t2[i]=t1[i]; // copie pour un autre tri
    }

// fonctions et proc�dures de tri

/*renvoie un bool�en vrai ssi t[deb1,fin1]<=val*/
bool inf_eq(tableau t, int deb1, int fin1, int val)
{
	int i;
	for (i=deb1;i<=fin1;++i)
        if (t[i]>val)
            return false;
	return true;
}

/*renvoie un bool�en vrai ssi val<t[deb1,fin1]l*/
bool sup(tableau t, int deb1, int fin1, int val)
{
	int i;
	for (i=deb1;i<=fin1;++i)
        if (t[i]<=val)
        	return false;
	return true;
}

int partitionnerInv(tableau tab, int ind_premier, int ind_dernier) {
	int ind_pivot = ind_premier;
	//	int valPivot = tab[ind_pivot];
	int j = ind_dernier;

  //  INV
  /*
	assert(inf_eq(tab, ind_premier, ind_pivot, tab[ind_pivot])
			&& sup(tab, j + 1, ind_dernier, tab[ind_pivot])
			&&  ind_premier <= ind_pivot && ind_pivot <= j  && j <= ind_dernier);
*/
  // conditiion de sortie, j = i_pivot
	while(j != ind_pivot) {
    //  INV et condition
	/*
    assert(inf_eq(tab, ind_premier, ind_pivot, tab[ind_pivot])
            && sup(tab, j + 1, ind_dernier, tab[ind_pivot])
            &&  ind_premier <= ind_pivot && ind_pivot <= j && j <= ind_dernier
            && j != ind_pivot);
	*/

    if (tab[j] > tab[ind_pivot]) {
		j --;
    } else if (tab[j] <= tab[ind_pivot]) {
		echanger(&tab[j], &tab[ind_pivot + 1]);
		echanger(&tab[ind_pivot], &tab[ind_pivot + 1]);
		ind_pivot ++;
    } else {
		printf("/!\\error\n");
    }


    //  INV
	/*
    assert(inf_eq(tab, ind_premier, ind_pivot, tab[ind_pivot])
            && sup(tab, j + 1, ind_dernier, tab[ind_pivot])
            &&  ind_premier <= ind_pivot && ind_pivot <= j && j <= ind_dernier);
		*/
	}
  //  INV et non cond
  /*
	assert(inf_eq(tab, ind_premier, ind_pivot, tab[ind_pivot])
			&& sup(tab, j + 1, ind_dernier, tab[ind_pivot])
			&&  ind_premier <= ind_pivot && ind_pivot <= j && j <= ind_dernier
			&& j == ind_pivot);
			*/
	return ind_pivot;
}

/* E: tab tableau de N entiers
    0<=d<N  0<=f<N
tri rapide
S:  slice tab[d,f] tri�
*/
void triRapide(tableau tab, int d, int f){
    int ind_pivot;
    if (d<f) {
        ind_pivot = partitionnerInv(tab, d, f);
        triRapide(tab, d, ind_pivot-1);
        triRapide(tab, ind_pivot+1, f);
    }
}

//	Derecursivation
void triRapideIte(tableau tab, int ind_premier, int ind_dernier) {
	int ind_pivot;
	pile_t pile;

	init_pile(&pile);
	empiler(&pile, ind_premier);
	empiler(&pile, ind_dernier);

	while(!pile_vide(&pile)) {
		
		ind_dernier = sommet(&pile);
		depiler(&pile);
		ind_premier = sommet(&pile);
		depiler(&pile);
		
		if (ind_premier < ind_dernier) {
			ind_pivot = partitionnerInv(tab, ind_premier, ind_dernier);

			empiler(&pile, ind_premier);
			empiler(&pile, ind_pivot - 1);

			empiler(&pile, ind_pivot + 1);
			empiler(&pile, ind_dernier);		
		}
	}
}

// tri bulle : nb de comparaisons de l'ordre de dim^2
void tri_bulle(tableau t,int dim)
{
	int i,j;
	for (i=0;i<dim;i++)
		for(j=i+1;j<dim;j++)
			if (t[i]>t[j])
        echanger(&t[i],&t[j]);
}

//	Tri Fusion
void fusionner(tableau tabT, int dp1, int fp1, int dp2, int fp2, tableau tabM) {
	
	for(int i = dp1; i <= fp2; i++) {
		tabM[i] = tabT[i];
	}
	for(int idFin = dp1; idFin <= fp2; idFin ++) {
		if (dp1 <= fp1 && ( dp2 > fp2 || tabM[dp1] <= tabM[dp2])) {
			tabT[idFin] = tabM[dp1];
			dp1 ++;
		} else {
			tabT[idFin] = tabM[dp2];
			dp2 ++;
		}
	}
}

void TriFusion (tableau tabT, int ind_prem, int ind_der, tableau tabM) {
	int ind_milieu;
	if (ind_prem < ind_der) {
		ind_milieu = (ind_prem + ind_der) / 2;
		TriFusion(tabT, ind_prem, ind_milieu, tabM);
		TriFusion(tabT, ind_milieu + 1, ind_der, tabM);
		fusionner(tabT, ind_prem, ind_milieu, ind_milieu + 1, ind_der, tabM);
	}
}

void TrisFusionIte(tableau tabT, int ind_prem, int ind_der, tableau tabM) {
	pile_t pileGauche;
	pile_t pileDroite;
	int ind_milieu;

	int ind_prem_gauche = ind_prem;
	int ind_der_gauche;
	int ind_prem_droit;
	int ind_der_droit = ind_der;

	init_pile(&pileGauche);
	init_pile(&pileDroite);

	while(ind_prem < ind_der) {
		ind_milieu = (ind_prem + ind_der) / 2;
		empiler(&pileGauche, ind_prem_gauche);
		empiler(&pileGauche, ind_der_gauche);
		ind_der
	}

}

// =================== MAIN =================
/* 2 arguments:     le nom du fichier ,   le nombre d'entiers du fichier trait�s*/

int main(int argc,char **argv)
{
    int dim;
    tableau t,t2,t3;
    clock_t now,end; // d�claration de timers
    switch (argc)
    {
		case 1: printf("Usage : commande fichier [dim]\n");return 1;break;
		case 2: dim=100;break;
		case 3: dim=atoi(argv[2]);break;
		default: printf("Erreur ligne de commande: trop d'arguments\n");return 1;break;
    }
    printf("Dim=%d TMAX=%d\n",dim,TMAX);
    tab_fichier(t,dim, argv[1]); // on lit les donn�es dans le 2�me param�tre de la ligne de commande
    //printf("tab 1:");ecriture_tab(t,dim);

    initCopieTab(t,t2,dim); // les tris se feront toujours sur t2 qui sera r�initialis� � chaque fois
	/*
    printf("Tri bulles\n");
    now = clock(); // d�part chrono
    tri_bulle(t2,dim);
    end=clock();
    printf("\nTemps CPU : %.2f secondes \n\n",(double) (end-now)/CLOCKS_PER_SEC); // fin chrono
    //printf("tab 1 trie' ");afficher_tab(t2,dim); // pour v�rifier sur un petit vecteur
    printf("-------------------------------\n");
	*/
    initCopieTab(t,t2,dim); // r�initialisation de t2

    printf("Tri rapide r�cursif\n");
    now = clock(); // d�part chrono
    triRapide(t2,0,dim-1);
    end =clock();
    printf("\nTemps CPU : %.2f secondes \n\n",(double) (end - now) / CLOCKS_PER_SEC); // fin chrono
    //printf("tab 1 trie' ");afficher_tab(t2,dim); // pour v�rifier sur un petit vecteur

	// tri rapide derec
	printf("-------------------------------\n");
	printf("Tri rapide de-recursif\n");
	initCopieTab(t,t2,dim);
	now = clock(); // d�part chrono
    triRapideIte(t2,0,dim-1);
    end =clock();
	printf("\nTemps CPU : %.2f secondes\n\n",(double) (end - now) / CLOCKS_PER_SEC);
	//	printf("tab derec trie' ");afficher_tab(t2,dim);

	// M�me principe pour le tri fusion
	printf("-------------------------------\n");
	printf("Tri Fusion\n");
	initCopieTab(t,t2,dim);
	initCopieTab(t,t3,dim);
	now = clock(); // depart chrono
	TriFusion(t2, 0, dim - 1, t3);
    end =clock();
	printf("\nTemps CPU : %.2f secondes\n\n",(double) (end - now) / CLOCKS_PER_SEC);
	//printf("tab trie par fusion' ");
	//afficher_tab(t2,dim);
    return 0;
}
