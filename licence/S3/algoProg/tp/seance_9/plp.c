#include <stdio.h>
#include <stdbool.h>

#define NMAX 1000

typedef int tab[NMAX];
typedef int mat[NMAX][NMAX];

// ==== Methode 1 ==== //

bool est_palin(tab t, int taille_t, int d, int f)
{
  int k = 0;
  while (t[d + k] == t[f - k] && (k <= (f - d) / 2))
  {
    k++;
  }
  return (k > (f - d) / 2);
}

int plp_brute_force(tab t, int taille)
{
  int plp = 0;
  int taille_pal = 0;

  for (int d = 0; d < taille; d++)
  {
    for (int f = d; f < taille; f++)
    {
      ;
      if (est_palin(t, taille, d, f))
      {
        taille_pal = ((f + 1) - d);
        if (taille_pal > plp)
        {
          plp = taille_pal;
        }
      }
    }
  }
  return plp;
}

// ==== Methode 2 ==== //

void afficherMat(mat m, int taille)
{
  for (int i = 0; i < taille; i++)
  {
    for (int j = 0; j < taille; j++)
    {
      printf("%d  ", m[i][j]);
    }
    printf("\n");
  }
}

void plp_dynamique(tab t, int taille)
{
  mat m;
  for (int i = 0; i < taille; i++)
  {
    //  diagonale de la matrice
    m[i][i] = 1;
  }
  for (int i = 0; i < taille - 1; i++)
  {
    //  diagonale - 1
    m[i][i + 1] = t[i] == t[i + 1];
  }
  // autres cases
  for (int d = 2; d < taille; d++)
  {
    for (int l = 0; l < taille - d; l++)
    {
      m[l][d + l] = t[d + l] == t[l] && m[l + 1][d + l - 1];
    }
  }
  afficherMat(m, taille);
  // diago la plus eloignée avec au moins un 1
}

// ==== Methode 3 ==== //
bool palindrome(tab t, int fin, int taille)
{
  int d = fin - taille + 1;
  int k = 0;
  while (t[d + k] == t[fin - k] && (k <= (fin - d) / 2))
  {
    k++;
  }
  return (k > (fin - d) / 2);
}

int plp_dyn_3(tab t, int taille)
{
  int plp = 0;

}

int main(void)
{
  tab t1 = {0, 0, 0, 0, 0, 0, 0, 0, 1};
  tab t2 = {0, 1, 2, 2, 2, 1, 0, 0, 1};
  int maxBF;
  int maxDyn;

  maxBF = plp_brute_force(t2, 9);
  plp_dynamique(t2, 9);

  printf("Plp = %d", maxBF);
  return 0;
}