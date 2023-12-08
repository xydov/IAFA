#include <stdio.h>
//<>

#define TAILLE_MAX 1024

int main() {
    char charControle[2]; // SIGNATURE

    int nbColsMax;
    int nbRowsMax;
    unsigned char MaxNvxGris;
    unsigned char tableau[TAILLE_MAX][TAILLE_MAX];

    scanf("%s", &charControle); //oook
    scanf("%d", &nbColsMax); //ok
    scanf("%d", &nbRowsMax);// ok
    scanf("%hhu", &MaxNvxGris); // ok

    for(int i = 0; i < nbRowsMax; i++)  //OK
    {
        for(int j = 0; j < nbColsMax; j++)
        {
            scanf("%hhu", &tableau[i][j]);
        }
    }
    printf("%s\n", charControle); //ok
    printf("%d %d\n", nbColsMax, nbRowsMax); //ok
    printf("%hhu\n", MaxNvxGris);//ok

    for(int i = 0; i < nbRowsMax; i++) // ok
    {
        for(int j = 0; j < nbColsMax; j++)
        {
            printf("%hhu ", tableau[i][j]);
        }
        printf("\n");
    }
    return 0;
}