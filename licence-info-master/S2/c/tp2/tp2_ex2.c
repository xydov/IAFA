#include <stdio.h>
// issupper()
#define MAX_LETTRES 50
#define NB_VOYELLES 6

int main()
{
    char chaineCara[MAX_LETTRES];
    char voyelles[NB_VOYELLES] = {'a', 'e', 'i', 'o', 'u', 'y'};
    int nombreLettres = 0;
    int nombreVoyelles = 0;
    int i = 0;

    printf("Entrez une chaine de caractères :");
    scanf("%s", &chaineCara);
    while((chaineCara[i] != '#' ) && (i != MAX_LETTRES)){
        printf("%c", chaineCara[i]);
        
        for(int j = 0; j < NB_VOYELLES; j++)
        {
            if (chaineCara[i] == voyelles[j])
            {
                nombreVoyelles ++;
            }
        }
        
        i++;
        nombreLettres ++;
    }
    printf("\n");

    printf("nombre de lettres: %d || et nombre de voyelles: %d\n", nombreLettres, nombreVoyelles);
    return 0;
}