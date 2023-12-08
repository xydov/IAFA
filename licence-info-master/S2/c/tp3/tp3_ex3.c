#include <stdio.h>

#define MAX_CARA 80

int main()
{
    char tableau[MAX_CHARA]; // if \n (espace) stop 
    for(int i = 0; i < MAX_CHARA; i++)
    {
        scanf("%c", &tableau[i]);
    }

    for (int i = 0; i < MAX_CHARA; i++)
    {
        printf("%c", tableau[i]);
    }
       
    return 0;
}