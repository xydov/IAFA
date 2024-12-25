#include <stdio.h>
// <>

#define ENT_MAX 10

int main(void)
{
    // stocker tab de mult dans tableau et appeller le tableau de facon linéaire
    printf(" x  |");
    for(int i = 0; i < ENT_MAX + 1; i++)
    {
        printf("%3d", i);
    }
    printf("\n");
    return 0;
}