#include <stdio.h>
// a finir, ne marche pas

void MinMax(int Tab[], int NbElt, int *pMin, int *pMax)
{
    int varIntMin = Tab[0];
    int varIntMax = Tab[0];
    for(int i = 0; i < NbElt - 1; i++)
    {
        if (varIntMin > Tab[i + 1]) // inférieur
        {
            varIntMin = Tab[i + 1];
            pMin = &Tab[i + 1];
        }

        if (varIntMax < Tab[i + 1]) // supérieur
        {
            varIntMax = Tab[i + 1];
            pMax = &Tab[i + 1];
        }
    }
    printf("inf:%p sup:%p\n", *pMin, *pMax);
}
/*
void MinMaxAdresse()
{
    return void;
}
*/
int main(void)
{
    int tab[] = {1, 3, 6, 0};
    int min, max;// *pMin, *PMax;

    MinMax(tab, 4, min, max);
    //MinMaxAdresse(tab, NbElt, &pMin, &pMax);
    return 0;
}