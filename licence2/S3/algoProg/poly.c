#include stdio.h

int puissance(int x, int n) {
  if (n == 0) return 1;
  if (n == 1) return x;
    else {
      return x * puissance (x, --n); // /!\ n-- not working
    }
}

int 
