#include <stdio.h>

int estPalindrome(int arr[], int l) {

  int i = 0;

  while (i < l/2) { // (arr[i] != arr[l -1 - i]) || i == l/2
    if (arr[i] != arr[l -1 - i]) {
      return 0;// not ideal, to rewrite
    }
    i ++;
  }
  return 1;
}

int main(void) {
  int resu;
  int arr[10]; // = {9, 9, 2, 7, 1, 1, 7, 2, 9, 9};
  int arrLength;

  printf("lenght: ");
  scanf("%d", &arrLength);

  printf("Valeurs: ");

  for (int j = 0; j < arrLength; j++) {
    scanf("%d", arr[j]);
  }

  resu = estPalindrome(arr, arrLength);

  if (resu == 1) {
    printf("Est un palindrome\n");
  } else {
    printf("N'est pas un palindrome :(\n");
  }

  return 0;
}
