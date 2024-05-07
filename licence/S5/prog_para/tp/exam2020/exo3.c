#include <omp.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int n = 1000;
    int C[n + 1][n + 1];
    memset(C, 0, sizeof(C[0][0]) * (n+1) * (n+1));

    #pragma omp parallel for num_threads(4)
    for (int i = 0; i <= n; i++)
    {
        C[i][0] = 1;
        C[i][i] = 1;
    }
    // #pragma omp parallel for num_threads(4)
    for (int i = 0; i <= n; i++)
    {
        #pragma omp parallel for num_threads(8)
        for (int j = 1; j < i; j++)
        {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%5d | ", C[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}