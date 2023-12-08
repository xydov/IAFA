#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void afficher (void) {
  printf("Processus (fils) de pid %d : Je boucle...\n", getpid());
  sleep(1);
}

int main(void)
{
  while (1)
  {
    afficher();
  }
  return 0;
}