#include <stdio.h>

int revRec(int n) {
  int a = n;
  int b = 0;
  while (a > 0){
    b = b * 10 + a % 10;
    a = a / 10;
  }
  return b;
}
