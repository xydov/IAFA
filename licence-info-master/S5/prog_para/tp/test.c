#include<stdio.h>

#include<stdlib.h>

#include<omp.h>

int main (int argc, char const *argv[]){
    int n;

    #pragma omp parallel for
    for(n = 0; n < 8; n++)
    {
        printf("Element %d traité par le thread %d \n", n, omp_get_thread_num());
    }

    return EXIT_SUCCESS;
}