/* DO NOT USE MALLOC AS SHOWN BELOW

int nbrVal;
int tableau[nbrVal];
*/

#include <stdio.h>

#define MAX_TAB 100

int main() 
{
    int nbrVal;
    int tableau[MAX_TAB];
    float moyenne = 0;

    printf("Nombre de valeur contenu dans le tableau (doit etre inférieur a 100): ");
    scanf("%d", &nbrVal);

    printf("Entrez les valeurs: \n");
    for(int i = 0; i < nbrVal; i++)
    {
        scanf("%d", &tableau[i]);
    }
    
    for(int i = 0; i < nbrVal; i++)
    {
        moyenne = moyenne + tableau[i];
    }

    moyenne = moyenne/nbrVal;
    printf("Moyenne = %.2f\n", moyenne);
    printf("Valeurs au dessus de la moyenne: ");
    for(int i = 0; i < nbrVal; i++)
    {
        if (tableau[i] > moyenne)
        {
            printf("%d\n", tableau[i]);
        }
    }
    return 0;
}