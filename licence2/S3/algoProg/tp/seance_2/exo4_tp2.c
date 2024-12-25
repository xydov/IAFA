#include <stdio.h>

int main(void) {
  int T[10] = {1, 2, 5, 9, 18, 27, 34, 46, 62, 89};
  int N = 5;

  int temp;

  for (int i = 0; i < N / 2; i++) {
    temp = T[i];
    T[i] = T[N - 1 - i];
    T[N - 1 -i] = temp;
  }

  for (int i = 0; i < 10; i++) {
    printf("%d : ", T[i]);
  }
  return 0;
}
