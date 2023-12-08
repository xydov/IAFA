#include <stdio.h>
// <>

int main(void)
{
    int nbLignes;
    printf("Entrez le nombre de lignes: ");
    scanf("%d", &nbLignes);
    
    for(int i = 1; i <= nbLignes; i++)
    {
        for(int j = 0; j < nbLignes - i; j++)
        {
            printf(" ");
        }
        for(int k = 0; k < 2 * i - 1; k++)
        {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}