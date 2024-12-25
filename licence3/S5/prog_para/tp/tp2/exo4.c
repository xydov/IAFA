#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define MAX_NUM_OBJ 1000
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define NB_THREADS 4

int num_obj = 0;
int capacity;
int weight[MAX_NUM_OBJ];
int utility[MAX_NUM_OBJ];

void read_problem(char *filename)
{
    char line[256];

    FILE *problem = fopen(filename, "r");
    if (problem == NULL)
    {
        fprintf(stderr, "File %s not found.\n", filename);
        exit(-1);
    }

    while (fgets(line, 256, problem) != NULL)
    {
        switch (line[0])
        {
        case 'c': // capacity
            if (sscanf(&(line[2]), "%d\n", &capacity) != 1)
            {
                fprintf(stderr, "Error in file format in line:\n");
                fprintf(stderr, "%s", line);
                exit(-1);
            }
            break;

        case 'o': // graph size
            if (num_obj >= MAX_NUM_OBJ)
            {
                fprintf(stderr, "Too many objects (%d): limit is %d\n", num_obj, MAX_NUM_OBJ);
                exit(-1);
            }
            if (sscanf(&(line[2]), "%d %d\n", &(weight[num_obj]), &(utility[num_obj])) != 2)
            {
                fprintf(stderr, "Error in file format in line:\n");
                fprintf(stderr, "%s", line);
                exit(-1);
            }
            else
                num_obj++;
            break;

        default:
            break;
        }
    }
    // fclose(problem);
    if (num_obj == 0)
    {
        fprintf(stderr, "Could not find any object in the problem file. Exiting.");
        exit(-1);
    }
}

/**
 * @brief Create a matrix of int
 * 
 * @param yaxis |
 * @param xaxis ---
 * @return int** pointer to the matrix (pointer array)
 */
int **create_matrix(int yaxis, int xaxis)
{
    int **matrix = calloc(yaxis, sizeof(int *));

    for (int i = 0; i < yaxis; i++)
    {
        matrix[i] = calloc(xaxis, sizeof(int));
    }

    return matrix;
}

/**
 * @brief Construction du tableau S
 * 
 * @return int** pointeur sur le tableau construit
 */
int **matrix_s()
{
    int **S = create_matrix(num_obj, capacity + 1);
    //  S[0]
    #pragma omp parallel for num_threads(NB_THREADS)
    
    for (int j = 0; j < (capacity + 1); j++)
    {
        if (weight[0] > j)
        {
            S[0][j] = 0;
        }
        else if (weight[0] <= j)
        {
            S[0][j] = utility[0];
        }
    }
    // S[1 -- N]
    for (int i = 1; i < num_obj; i++)
    {
        #pragma omp parallel for num_threads(NB_THREADS)
        for (int j = 0; j < (capacity + 1); j++)
        {
            if ( weight[i] <= j )
            {
                S[i][j] = MAX(S[i - 1][j], (S[i - 1][j - weight[i]] + utility[i]));
            }
            else
            {
                S[i][j] = S[i - 1][j];
            }
        }
    }

    return S;
}

int *get_E_from_S(int **S)
{
    int *E = calloc(num_obj, sizeof(int));

    int start_i = num_obj - 1;
    int start_j = capacity;

    while (start_i != 0 && start_j != 0)
    {
        if (S[start_i][start_j] == S[start_i - 1][start_j])
        {
            // case i-1 j
            E[start_i] = 0;
        } else
        {
            E[start_i] = 1;
            start_j -= weight[start_i];
        }
        start_i --;
    }
    
    // handle start_i == 0
    E[start_i] = S[start_i][start_j] == utility[start_i];

    return E;
}

/**
 * @brief affiche la matrice (ici S)
 * 
 * @param S la matrice a afficher (S pour le moment)
 */
void print_mat(int **S)
{
    printf("==START PRINT MAT\n");
    for (int i = 0; i < num_obj; i++)
    {
        for (int j = 0; j < (capacity + 1); j++)
        {
            printf("| %d |", S[i][j]);
        }
        printf("\n");
    }
    printf("==END PRINT MAT\n\n");
}

int main(void)
{
    int best;
    int somme = 0;

    double start, stop;

    read_problem("./p2");
    //---------------------------
    start = omp_get_wtime();
    
    int **S = matrix_s();
    int *E = get_E_from_S(S);

    stop = omp_get_wtime();
    printf("1)Time n_threads(%d) = %f\n", NB_THREADS, stop - start);
    start = stop = 0;    

    //---------------------------
    best = S[num_obj - 1][capacity];

    printf("Best utility = %d\n", best);

    for (int i = 0; i < num_obj; i++)
    {
        if (E[i] == 1)
        {
            somme += utility[i];
        }
    }
    if (somme == best)
    {
        printf("[OK] Utilité maximale (%d) == somme des utilités (%d)\n", best, somme);
    }
    else
    {
        printf("[FAIL] Utilité maximale (%d) != somme des utilités (%d)\n", best, somme);
    }

    // free
    for (int i = 0; i < num_obj; i++)
    {
        free(S[i]);
    }
    free(S);
    free(E);

    return 0;
}