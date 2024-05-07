#include <stdlib.h>
#include <stdio.h>

int main(void) {
  int T[5] = {5, 10, 15 ,20, 25};

  int n = 2;

  int *tab = malloc((n * 5) * sizeof(int));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 5; j++) {
      tab[j + (i * 5)] = T[j];
    }
  }

  /*
  for (int i = 0; i < 5 * n; i++) {
    tab[i] = T[i%5]
  }
  */

  for(int r = 0; r < n * 5; r++) {
    printf("tab: %d\n", tab[r]);
  }

  free(tab);

  return 0;
}
