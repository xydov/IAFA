#include <stdio.h>
#include <math.h>

/* Explication:
Ne tient pas compte de la partie décimale
*/

int main(void) {
  unsigned char nbr, nbrAuCarree;
  scanf("%hhu",&nbr);
  nbrAuCarree = sqrt(nbr);
  printf("%hhu\n",nbrAuCarree);
  return 0;
}
