#include <stdio.h>

const int NBMINH = 60;

// Convertir en h, m et s, une duree (en secondes) passee en parametre
// Passage par adresse pour modifier les parametres resultats
void convertir (int uneDuree, int *h, int *m, int *s) {
  *h = uneDuree / (NBMINH * NBMINH);
  uneDuree = uneDuree % (NBMINH * NBMINH);
  *m = uneDuree / NBMINH;  
  *s = uneDuree % NBMINH;  
}


int main (void) {
  int duree, enHeures, enMin, enSec;
  int termine = 0;

  while (! termine) {
    printf("Convertir quelle duree ? (0 pour arreter)");
    scanf("%d", &duree);

    if (duree == 0)
      termine = 1;
    else {
      convertir(duree, &enHeures, &enMin, &enSec);	    
      printf("%d = %d h %d m %d s\n", duree, enHeures, enMin, enSec);
    }
  }
  return (0);
}
