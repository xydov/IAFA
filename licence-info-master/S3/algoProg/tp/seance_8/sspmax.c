#include <stdio.h>
#include <assert.h>
#include <time.h>

#define NMAX 100000

typedef int tab[NMAX];

/**
 * Calcul du poids d'un sous-séquence
 * @param deb indice du début de la sous-séquence
 * @param fin indice de la fin de la sous-séquence
 * @param t tableau t de taille max NMAX
 * @return poids de la sous-séquence
 */
int poids(int deb, int fin, tab t)
{
    int poidsSousSeq = 0;
    for (; deb <= fin; deb++)
    {
        poidsSousSeq += t[deb];
    }
    return poidsSousSeq;
}

/**
 * Solution naïve O(n³)
 * @param t tableau t de taille max NMAX
 * @param taille taille du tableau
 * @return poids de la sous-séquence de poids max
 */
int f1(tab t, int taille, int *i_deb, int *i_fin)
{
    int max = t[0];

    int somme;

    for (int deb = 0; deb < taille; deb++)
    {
        for (int fin = deb; fin < taille; fin++)
        {
            somme = poids(deb, fin, t);
            if (somme > max)
            {
                max = somme;
                *i_deb = deb;
                *i_fin = fin;
            }
        }
    }
    return max;
}

/**
 * Solution naïve O(n²)
 * @param t tableau t de taille max NMAX
 * @param taille taille du tableau
 * @return poids de la sous-séquence de poids max
 */
int f2(tab t, int taille, int *i_deb, int *i_fin)
{
    int max = t[0];
    int somme;

    for (int deb = 0; deb < taille; deb++)
    {
        somme = 0;
        for (int fin = deb; fin < taille; fin++)
        {
            somme += t[fin];
            if (somme > max)
            {
                max = somme;
                *i_deb = deb;
                *i_fin = fin;
            }
        }
    }
    return max;
}

/**
 * Solution dynamique O(n)
 * @param t tableau t de taille max NMAX
 * @param taille taille du tableau
 * @return poids de la sous-séquence de poids max
 */
int f3(tab t, int taille, int *i_deb, int *i_fin)
{
    int res = t[0];
    int max = t[0];
    int recuperation_i_deb = 0;

    for (int deb = 1; deb < taille; deb++)
    {
        if (res > 0)
        {
            res += t[deb];
        }
        else
        {
            res = t[deb];
            //  *i_deb = deb;
            //  On ne peu 'deviner' le début
        }
        if (res > max)
        {
            max = res;
            *i_fin = deb;
        }
    }
    *i_deb = *i_fin;
    while (recuperation_i_deb != max)
    {
        recuperation_i_deb += t[*i_deb];
        (*i_deb) --;
    }
    (*i_deb) ++;
    
    return max;
}

int main(void)
{
    srand(time(NULL));
    //  int x = rand()%21-10;
    int max, max2, max3;
    int id_deb, id_fin, id_deb2, id_fin2, id_deb3, id_fin3;
    printf("%d", id_deb3);

    clock_t debut = clock();
    clock_t fin = clock();

    tab tableau;
    for (int i = 0; i < 1000; i++)
    {
        tableau[i] = rand() % 21 - 10;
    }
    /*
    debut = clock();
    max2 = f2(tableau, 1000, &id_deb, &id_fin);
    fin = clock();
    printf("F:-:f2: Temps CPU:%.2fsecondes\n", (double)(fin - debut) / CLOCKS_PER_SEC);
    printf("f2: %d\n", max2);
    printf("id deb = %d | id fin = %d\n", id_deb, id_fin);
    id_deb = 0;
    id_fin = 0;
    printf("==================================\n");

    debut = clock();
    max3 = f3(tableau, 1000, &id_deb, &id_fin);
    fin = clock();
    printf("F:-:f3: Temps CPU:%.2fsecondes\n", (double)(fin - debut) / CLOCKS_PER_SEC);
    printf("f3: %d\n", max3);
    printf("id deb = %d | id fin = %d\n", id_deb, id_fin);
    id_deb = 0;
    id_fin = 0;
    printf("==================================\n");

    debut = clock();
    max = f1(tableau, 1000, &id_deb, &id_fin);
    fin = clock();
    printf("F:-:f1: Temps CPU:%.2fsecondes\n", (double)(fin - debut) / CLOCKS_PER_SEC);
    printf("f1: %d\n", max);
    printf("id deb = %d | id fin = %d\n", id_deb, id_fin);
*/
    int nbVal = 1000;
    int nbTest = 200;
    int nbSuccess = 0;

    for (int i = 0; i < nbTest; i++)
    {
        for (int i = 0; i < nbVal; i++)
        {
            tableau[i] = rand() % 21 - 10;
        }
        max3 = f3(tableau, nbVal, &id_deb3, &id_fin3);
        max2 = f2(tableau, nbVal, &id_deb2, &id_fin2);
        max = f1(tableau, nbVal, &id_deb, &id_fin);
    printf("\n");
        if ((id_deb == id_deb2) && (id_deb2 == id_deb3) && (id_fin == id_fin2) && (id_fin2 == id_fin3) && (max == max2) && (max2 == max3))
        {
            printf("Test n°%d: Success\n", i + 1);
            nbSuccess ++;
        }
        else
        {
            printf("Test n°%d: Failed\n", i + 1);
        }
        printf("f1: %d\n", max);
        printf("id deb = %d | id fin = %d\n", id_deb, id_fin);
        printf("==================================\n");
        printf("f2: %d\n", max2);
        printf("id deb = %d | id fin = %d\n", id_deb2, id_fin2);
        printf("==================================\n");
        printf("f3: %d\n", max3);
        printf("id deb = %d | id fin = %d\n", id_deb3, id_fin3);
    }
    printf("\n\nNombre de test reussi = %d/%d", nbSuccess, nbTest);

    return 0;
}