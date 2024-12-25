#include <stdio.h>

int exposantIt(int x, int n) {
  int r = 1;

  for(int i = 0; i < n; i++) {
    r *= x;
  }
    return r;
}

int exposantRec(int x, int n) {
  if(n == 0) {
    return 1;
  } else {
    return x * exposantRec(x, n - 1);
  }
}

int main(void) {
  int x;
  int n;
  int resu;
  int resu2;

// get x and n from user
  printf("X: ");
  scanf("%d", &x);
  printf("N: ");
  scanf("%d", &n);

  // boucle qui teste pour chaque i: 0 <= i <= N
  for (int i = 0; i <= n; i++) {

    resu = exposantIt(x, i);
    resu2 = exposantRec(x, i);

    if (resu != resu2) {
      return 1;
    }
  }

  printf("ité: %d\n", resu);
  printf("rec: %d\n", resu2);

  return 0;
}
