#include <stdio.h>


int ft(int x, int y)
{
    return x + y;
}


int main (void)
{
    int (*f)(int, int);
    f = ft;

    int i = f(3, 4);
    printf("%d\n", i);

    return 0;
}