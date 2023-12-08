/*  dynamique
* int N;
* int P;
* int **m = malloc(N*sizeof(int*));
* int i = 0;
* for(i = 0; i < N; i++) {
*   int* m[i] = malloc(P*sizeof(int));
* }
*for(i=0; i < N; i++) {
* free(m[i]);
* }
* free(m);
*/

// probleme de fuite de mémoire: pas de free lors de malloc, prog stoppe instant
// /!\ faire attention lors du free de matrices, pour éviter la perte d'adresse des zones mémoires contenant les tableaux
#include <stdlib.h>
#include <stdio.h>

void demandeDimensions(int *matI1, int *matJ1, int *matI2, int *matJ2) {
  scanf("%s\n", );
  scanf("%s\n", );
  scanf("%s\n", );
  scanf("%s\n", );

  if (matJ1 != matI2) {
    printf("Erreur, dimensions non valides\n");
  }
}

void multiplieMatrice(int[] tab) {
}

int main(void) {
  int matI1;
  int matJ1;
  int matI2;
  int matJ2;

  demandeDimensions(&matI1, &matJ1, &matI2, &matJ2);
  return 0;
}
