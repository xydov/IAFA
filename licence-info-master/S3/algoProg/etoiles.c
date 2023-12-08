#include <stdio.h>

// return pyr descendante d'étoile (rec)

void etoileDesc(int n) {
  if (n == 0){
    printf("end");

  }else {
    for(int i = n; i > 0; --i) {
      printf("*");
    }
    printf("\n");
    n --;
   etoileDesc(n);
  }
}

void etoileAsc(int n) {
  if(n > 0) {
    etoileAsc(n --);
    for(int i = n; i > 0; i++) {
      printf("*");
    }
    printf("\n");
  }
}

int main(void) {
  //  etoileDesc(5);
  etoileAsc(5);
  return 0;
}
