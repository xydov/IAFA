#include<stdio.h>

int main(void) {

  float tempFahrenheit, tempCelcius;
  scanf("%f",&tempFahrenheit);
  tempCelcius = (tempFahrenheit - 32)*5/9;
  printf("La temperature en celcius est de: %f°C\n",tempCelcius);
  return 0;
}
