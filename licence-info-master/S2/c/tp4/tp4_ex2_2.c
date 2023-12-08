#include <stdio.h>
//<>

#define TAILLE_MAX 1024

int main() {
    char charControle[2]; // SIGNATURE

    int nbColsMax;
    int nbRowsMax;
    unsigned char MaxNvxGris;
    unsigned char tableau[TAILLE_MAX][TAILLE_MAX];
    unsigned char tableauRota[TAILLE_MAX][TAILLE_MAX];

    scanf("%s", &charControle); //oook
    scanf("%d", &nbColsMax); //ok
    scanf("%d", &nbRowsMax);// ok
    scanf("%hhu", &MaxNvxGris); // ok

    for(int i = 0; i < nbRowsMax; i++)  //OK
    {
        for(int j = 0; j < nbColsMax; j++)
        {
            scanf("%hhu", &input);
            tableau[i][j] = input;
            tableauRota[j][nbColsMax-i] = input;
        }
    }
    printf("%s\n", charControle); //ok
    printf("%d %d\n", nbRowsMax, nbColsMax); //ok
    printf("%hhu\n", MaxNvxGris);//ok

    for(int i = 0; i < nbColsMax; i++)
    {
        for(int j = 0; j < nbRowsMax; j++)
        {
            printf("%hhu ", tableau[j][nbColsMax-i]);
        }
        printf("\n");
    }
    
    return 0;
}