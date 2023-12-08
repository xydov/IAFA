#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_STEPS 1000
#define NUM_OPS 50

int main() {
  int num = 0;
  #pragma omp parallel for num_threads(4)
  for (int i = 0; i < NUM_STEPS; i++)
  {
    for (int j = 0; j < NUM_OPS; j++)
    {
      #pragma omp atomic
      num++;
    }
    for (int j = 0; j < NUM_OPS; j++)
    {
      #pragma omp atomic
      num--;
    }
  }
  printf("num = %d\n", num);
}
