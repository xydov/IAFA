#include<stdio.h>

int main(void) {
  int a, b, temp;
  scanf("%d",&a);
  scanf("%d",&b);
  temp = a;
  a = b;
  b = temp;
  printf("Premiere entree: %d  deuxieme entree: %d\n",a ,b);
  return 0;
}
