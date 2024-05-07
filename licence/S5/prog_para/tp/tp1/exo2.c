#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20000
#define THREAD_NUMB 8

int main()
{
    srand(time(NULL));

    double t, start, stop;

    long somme = 0;
    int ** matrix = calloc(SIZE, sizeof(int *));

    for (int i = 0; i < SIZE; i++)
    {
        matrix[i] = calloc(SIZE, sizeof(int));
        for (int j = 0; j < SIZE; j++)
        {
            matrix[i][j] = (int)rand() % 2;
        }
    }

    // ------------------------------------------------------//
    //                        1) sequentiel
    // ------------------------------------------------------//
    start = omp_get_wtime();
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            somme += matrix[i][j];
        }
    }
    stop = omp_get_wtime();
    t = stop - start;
    printf("1) time = %f\n", t);
    printf("1) somme = %ld\n\n", somme);
    start = stop = t = somme = 0;

    // ------------------------------------------------------//
    //             2) somme des sommes partielles
    // ------------------------------------------------------//
    long * somme_partielle = calloc(THREAD_NUMB, sizeof(long));
    for (int i = 0; i < THREAD_NUMB; i++)
    {
        somme_partielle[i] = 0;
    }

    start = omp_get_wtime();
    #pragma omp parallel num_threads(THREAD_NUMB)
    {
        int tid = omp_get_thread_num();
        #pragma omp for
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                somme_partielle[tid] += matrix[i][j];
            }
        }
        #pragma omp single
        {
            for (int i = 0; i < THREAD_NUMB; i++)
            {
                somme += somme_partielle[i];
            }
        }
    }
    stop = omp_get_wtime();
    t = stop - start;
    printf("2) time = %f\n", t);
    printf("2) somme = %ld\n\n", somme);
    start = stop = t = somme = 0;
    // free somme_partielle
    free(somme_partielle);

    // ------------------------------------------------------//
    //        3) somme des sommes partielles par thread
    // ------------------------------------------------------//
    start = omp_get_wtime();
    #pragma omp parallel num_threads(THREAD_NUMB)
    {
        long sm = 0;
        #pragma omp for
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                sm += matrix[i][j];
            }
        }
        #pragma omp atomic
        somme += sm;
    }
    stop = omp_get_wtime();
    t = stop - start;
    printf("3) time = %f\n", t);
    printf("3) somme = %ld\n\n", somme);
    start = stop = t = somme = 0;

    // ------------------------------------------------------//
    //                    4) réduction
    // ------------------------------------------------------//
    start = omp_get_wtime();
    #pragma omp parallel for num_threads(THREAD_NUMB) reduction(+:somme)
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            somme += matrix[i][j];
        }
    }
    stop = omp_get_wtime();
    t = stop - start;
    printf("4) time = %f\n", t);
    printf("4) somme = %ld\n\n", somme);
    start = stop = t = somme = 0;



    // free the matrix correctly 
    for (int i = 0; i < SIZE; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}