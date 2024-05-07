#include <stdio.h>

void conversionEnHeureMinutesSecondes(int dureeSec)
{
    int heures, minutes, secondes;
    float tempo;
    //sec / 3600 = 0.x Heures
    // 0.x x 60 = min
    // |=nb heures
    heures = dureeSec / 3600;
    tempo = ((dureeSec / 3600) - heures) * 60;
    minutes = tempo;
    secondes = tempo / 60;    
    printf("Duree en secondes: %d; heures %d, minutes: %d, secondes, %d\n", dureeSec, heures, minutes, secondes);

}

int main(void)
{
    int dureeSec;
    printf("Entrez une duree en seconde: ");
    scanf("%d", &dureeSec);
    
    conversionEnHeureMinutesSecondes(dureeSec);

    // appell 2
    return 0;
}
