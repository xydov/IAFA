#include stdio.h
#include <stdio.h>


void etoile(int n) {
  if(n == 0) {
      } else {
    for(int i = n; i > 0; i--) {
      printf("*");
    }
    printf("\n");
    etoile(n - 1);
  }
}

int main(void) {
  etoile(5);
  return 0;
}

/*
void etoileInv(int n) {
  if(n==0){
    
  }else {
  etoile(n - 1);
    for(int i = n; i > 0; i--) {

    printf("*");
    }
    printf("\n");
  }
}
*/
