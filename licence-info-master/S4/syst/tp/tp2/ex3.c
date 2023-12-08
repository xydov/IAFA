#define _POSIX_C_SOURCE 1


#include "h.h"
#include "matrice.h"
#include "traiterLigne.h"


/* #define NB_LIGNES_MAX 10
#define NB_COLONNES_MAX 10 */



int main(void)
{
    //  pid_t fork_pid;

    int matrice[NB_LIGNES_MAX][NB_COLONNES_MAX];
    int vvv;

    initialiserMatrice(matrice, NB_LIGNES_MAX, NB_COLONNES_MAX);
    afficherMatrice(matrice, NB_LIGNES_MAX, NB_COLONNES_MAX);
    for (int i = 0; i < NB_LIGNES_MAX; i++)
    {
        vvv = traiterLigne(matrice[i], NB_COLONNES_MAX, 1, 2);
        
        
        printf("Ligne %d: %d", i, vvv);
    }
    

    /* switch (fork_pid = fork())
    {
    case -1:
            // ERROR -> to PERE
            printf("\nERROR!\n\n");
            perror("ERROR -> to PERE");
            exit(1);
            break;

        case 0:
            //  FILS
            exit(10);

        default:
            
            break;
    } */

    return 0;
}