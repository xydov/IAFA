#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define NLIG 10
#define NCOL 10
#define EPSILON 1e-5

//E: L tableau d'entiers contenant au moins n1 cases
//   n1: nombre de cases affichees
//S: affichage des n1 premieres cases de L
void afficher_tab(int L[], int n1)
{
    int i;
    for (i = 0; i < n1; ++i)
        printf("%d ", L[i]);
    printf("\n\n");
}

//...........................................................................................
//E: L tableau de float contenant au moins n1 cases
//   n1: nombre de cases affichées
//S: affichage des n1 premieres cases de L separees par des ,
void afficher_tab_f(float L1[], int n1)
{
    int i;
    printf("(");
    for (i = 0; i < n1; ++i)
        printf("%6.2f   ", L1[i]);
    if (i < n1 - 1)
        printf(",");
    printf(")");
}

//..........................................................................................
//affichage formate d'un systeme lineaire faisant apparaitre le second membre
void afficher_sys(float s[NLIG][NCOL], int nb_lig, int nb_col)
{
    int ligne, colonne;
    printf("\n");
    for (ligne = 0; ligne < nb_lig; ++ligne)
    {
        printf("\n");
        for (colonne = 0; colonne < nb_col; ++colonne)
        {
            if (colonne == nb_col - 1)
                printf(" | ");
            printf("%7.3f ", s[ligne][colonne]);
        }
    }
}

//.........................................................................................
//E: m matrice nb_lig X nb_col
//   i,j entiers
//si possible, permutation des lignes d'indices i et j de la matrice m
//sinon affichage d'erreur
//S: m modifiee (procedure)
void permuter(float m[NLIG][NCOL], int nb_lig, int nb_col, int i, int j)
{
    //  assert(i < nb_lig && j < nb_lig && i >= 0 && j >= 0);
    if (i < nb_lig && j < nb_lig && i >= 0 && j >= 0)
    {
        int temp;
        for (int col = 0; col < nb_col; col++)
        {
            temp = m[i][col];
            m[i][col] = m[j][col];
            m[j][col] = temp;
        }
    }
    else
    {
        printf("!! Permutation impossible !!");
    }
}

//.........................................................................................
//E: m matrice nb_lig X nb_col
//   i  entier corres a la ligne
//   a  reel
//si possible, mutiplie la ligne L(i) de la matrice m par le reel a
//sinon affichage d'erreur
//S: m modifiee (procedure)
void dilater(float m[NLIG][NCOL], int nb_lig, int nb_col, int i, float a)
{

    //A completer
    if (a != 0 && i < nb_lig) // i inf a nb ligne
    {
        for (int col = 0; col < nb_col; col++)
        {
            m[i][col] = a * m[i][col];
        }
    }
    else
    {
        printf("!! Erreur dilatation !!");
    }
}

//..........................................................................................
//E: m matrice nblig X nbcol
//   i1,i2 entiers
//si possible, remplacer la ligne L(i1) par L(i1)+a*L(i2) dans la matrice m
//sinon affichage d'erreur
//S: m modifiee (procedure)
void transvecter(float m[NLIG][NCOL], int nb_lig, int nb_col, int i1, float a, int i2)
{
    if (i1 < nb_lig && i2 < nb_lig && a != 0)
    {
        for (int col = 0; col < nb_col; col++)
        {
            m[i1][col] = m[i1][col] + a * m[i2][col];
        }
    }
    else
    {
        printf("!! Erreur transvection !!");
    }
}

//...........................................................................................
//E: S matrice rectangulaire du systeme:  S=(A|B)
//   nb_lig: nombre de lignes de M
//   nb_col: nombre de colonnes de la matrice A = nombre de variables de S
//S: s matrice resolue issue de M:
//      on normalise les lignes en divisant par les pivots
//      on annule aussi les termes au dessus des pivots
//   L_piv: liste des indices des colonnes des pivots (inconnues principales)
//   nb_piv : nombre de pivots
void matrice_resolue(float s[NLIG][NCOL], int nb_lig, int nb_col, int L_piv[NCOL],
                     int *nb_piv)
{
    int lig = 0; //indice de la ligne courante
    int col = 0; //indice de la colonne courante
    *nb_piv = 0; //initialisation du nombre de pivots
    //On s'arrete des qu'on a traite la derniere ligne ou colonne
    while (lig < 0 && col < 0)
    {
        int pivot;
        for (; lig < nb_lig; lig ++)
        {
            
        }
        if (pivot == 0)
        {
            col ++;
        } else
        {
            permuter(s, nb_lig, nb_col, lig, /*lig_du_pivot*/);
        }
        
        
        
    }

    /* code */

    //A completer
}

//..........................................................................................
//E: S matrice d'un systeme lineaire (A|B)
//   nb_col nombre d'inconnues
//   i entier
//Determine si la ligne d'indice i de A est nulle
//S: renvoie un booleen
bool ligne_ssmb_nulle(float S[NLIG][NCOL], int nb_col, int i)
{
    int j;
    for (j = 0; j < nb_col; ++j) // on ne prend pas en compte le second membre
        if (fabs(S[i][j]) >= EPSILON)
            return false;
    return true;
}

//...........................................................................................
//E: S matrice d'un systeme lineaire (A|B)
//Determine si le systeme est compatible : les equations sans pivots
// situees en fin de systeme doivent etre 0=0
//renvoie un booleen
bool est_compatible(float S[NLIG][NCOL], int nb_lig, int nb_col)
{
    //A completer

    return false;
}
//..........................................................................................
//E: t tableau de N entiers,  x un entier
//Determine si l'entier x est pr�sent dans t[0,N[
//renvoie un booleen
bool est_present(int t[], int N, int x)
{
    int i;
    for (i = 0; i < N; ++i)
        if (x == t[i])
            return true;
    return false;
}

//..........................................................................................
//E: s matrice d'un systeme resolu , normalise et compatible
//Determination d'une solution particuli�re
//S: point :la solution particuli�re de s
void sol_part(float S[NLIG][NCOL], int nb_col, int L_piv[NCOL], int nb_piv,
              float point[NCOL])
{

    //A completer
}

//..........................................................................................
//E: s matrice d'un systeme resolu, normalise et compatible
//Determination d'une base de H
//S: base
void base_H(float S[NLIG][NCOL], int nb_lig, int nb_col, int L_piv[NCOL], int nb_piv,
            int L_inc_indep[NCOL], float base[NCOL][NCOL])
{

    //A completer
}

//..........................................................................................
//E: une solution particuli�re point et la base de H basqe_H
//Affichage des solutions d'un syst�me compatible
//S: --
void affiche_sols(int nb_col, float point[NCOL], float base[NCOL][NCOL],
                  int nb_inc_indep)
{
    printf("L'ensemble des solutions est un espace affine de dimension %d.", nb_inc_indep);
    printf("\nSol={");
    afficher_tab_f(point, nb_col);
    printf("\n   + Vect( ");
    int k;
    for (k = 0; k < nb_inc_indep; k++)
    {
        afficher_tab_f(base[k], nb_col);
        printf("\n          ");
        if (k < nb_inc_indep - 1)
            printf(",");
    }
    printf(")}\n");
}

//..........................................................................................
//E: s matrice d'un systeme resolu et normalise
//Affichage des solutions du systeme s
//S: --
void resout(float s[NLIG][NCOL], int nb_lig, int nb_col)
{

    //A completer
}

/*///////////////////////////////////////////////////////////////////////////*/
int main(void)
{

    //printf("Test de diff:");
    //int L1[]={1,2,3,4,5,6};
    //int n1=6;
    //int L2[]={2,3,5,6};
    //int n2=4;
    //printf("avant:\n");
    //afficher_tab(L1,n1);
    //afficher_tab(L2,n2);
    //diff(L1,L2,&n1,n2);
    //printf("apres:\n");
    //afficher_tab(L1,n1);

    int nb_lig, nb_col;

    printf("\n\nTest de permuter:");
    float m[NLIG][NCOL] = {{1, 1, 1, 1}, {2, 2, 2, 2}, {3, 3, 3, 3}};
    //printf("%d %d %d %d\n",sizeof(m),sizeof(m[1]),sizeof(&(m[1])),sizeof(m[1][0]));
    nb_lig = 3;
    nb_col = 4 - 1;
    afficher_sys(m, nb_lig, nb_col + 1);
    permuter(m, nb_lig, nb_col, 0, 2);
    afficher_sys(m, nb_lig, nb_col + 1);
    /*
    printf("\n\nTest de dilater:");
    dilater(m,nb_lig,nb_col,1,10);
    afficher_sys(m,nb_lig,nb_col);
    dilater(m,nb_lig,nb_col,0, 1.2);
    afficher_sys(m,nb_lig,nb_col);
    */
    //printf("\n\nTest de ajouter:");
    //ajouter(m,nb_lig,nb_col,1,10.,2);
    //afficher_sys(m,nb_lig,nb_col);
    //ajouter(m,nb_lig,nb_col,1,-10,2);
    //afficher_sys(m,nb_lig,nb_col);
    //
    //printf("\n\nTest de est_compatible:");
    //float m1[NLIG][NCOL]={{1,1,1,1},{0,0,0,1}};
    //nb_lig=2;
    //nb_col=3;
    //afficher_sys(m1,nb_lig,nb_col+1);
    //printf("\ncompatible: %d ",est_compatible(m1,nb_lig,nb_col));
    //float m2[NLIG][NCOL]={{1,1,1,0},{0,0,0,0}};
    //nb_lig=2;
    //nb_col=3;
    //afficher_sys(m2,nb_lig,nb_col+1);
    //printf("\ncompatible: %d %d",est_compatible(m2,nb_lig,nb_col));
    //printf("\n..........................................................");

    printf("\n\n\n                             Resolution de systemes\n");

    float s5[NLIG][NCOL] = {{1, 2, 0., 0., 0., 3.}, {0., 0., 2., 3., 1., 6}, {0., 0., 2., 1., -1., 2.}, {0., 0., 0., 2., 3., 5.}, {0, 0, 2, 3, 2, 7}};
    nb_lig = 5;
    nb_col = 6 - 1;
    afficher_sys(s5, nb_lig, nb_col);

    float s51[NLIG][NCOL] = {{1, 2, -1, 1, 1}, {4., -2., -3., 0., 0.}};
    nb_lig = 2;
    nb_col = 5 - 1;
    afficher_sys(s51, nb_lig, nb_col);

    //
    //float s[NLIG][NCOL]={{1.,-1.,2.,5.},{3.,2.,1.,10.},{2.,-3.,-2.,-10.}};
    //nb_lig=3;
    //nb_col=4-1;
    //
    //
    //
    //float s1[NLIG][NCOL]={{1.,-1.,2.,5.},{3.,2.,1.,10.},{2.,-3.,-2.,-10.},
    //{1.,0.,0.,3.}};
    //nb_lig=4;
    //nb_col=4-1;
    //
    //
    //float s2[NLIG][NCOL]={{1.,-1.,2.,1.,3.,5.},{3.,2.,1.,2.,1.,10.}};
    //nb_lig=2;
    //nb_col=6-1;
    //
    //
    //
    //float s3[NLIG][NCOL]={{0.,-1.,2.,5.},{3.,2.,1.,10.},{2.,-3.,-2.,-10.}};
    //nb_lig=3;
    //nb_col=4-1;
    //
    //
    //
    //float s31[NLIG][NCOL]={{1,0,0,1},{0,0,0,1},{0,0,0,0 }};
    //nb_lig=3;
    //nb_col=4-1;
    //
    //
    //
    //float s4[NLIG][NCOL]={{ 4.,4.,0.,2.,4.,5.},{5.,1.,6.,5.,4.,1},
    //{1.,1.,0.,1.,0.,1.},{5.,1.,6.,6.,2.,3.}};
    //nb_lig=4;
    //nb_col=6-1;
    //
    //
    //
    //float s6[NLIG][NCOL]={{1,4,0,-1,0.,7.,-9,3},{2.,8.,-1.,3.,9.,-13,7,9},
    //{0.,0.,2.,-3,-4.,12,-8,1},{-1,-4,2,4,8,-31,37,4 }};
    //nb_lig=4;
    //nb_col=8-1;
    //
    //
    //
    //float s7[NLIG][NCOL]={{0,0,0,0,1,2},{1,1,1,2,0,3}};
    //nb_lig=2;
    //nb_col=6-1;
    //
    //
    //float s8[NLIG][NCOL]={{ 4,4,0,2,10},{5,1.,6.,5.,17},
    //{1.,1.,0.,1.,3},{5.,1.,6.,6.,18}};
    //nb_lig=4;
    //nb_col=5-1;

    return 0;
}
