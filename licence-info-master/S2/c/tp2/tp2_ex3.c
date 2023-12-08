#include <stdio.h>

#define NOTE_MAX 20

int main()
{
    int nombreDeValeur = 0, valeurInter, sommeDesValeurs = 0;
    printf("Nombre de valeur dont la moyenne sera calculée: ");
    scanf("%d", &nombreDeValeur);
    for(int i = 0; i < nombreDeValeur; i++)
    {
        printf("Entrer la %i eme valeur: ", i+1);
        scanf("%d", &valeurInter);   

        while(valeurInter > NOTE_MAX){
            printf("erreur de saisie la note doit etre inférieur a 20\n");
            printf("entrer une valeur valide: ");
            scanf("%d", &valeurInter);
        }
        sommeDesValeurs += valeurInter;      
    }
    sommeDesValeurs /= nombreDeValeur;
    printf("La moyenne est de : %d\n", sommeDesValeurs);
    return 0;
}