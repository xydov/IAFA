#include "sudoku.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// list of Sudoku grids with interesting bruteforce solutions
const int interesting_bruteforce[] = {0, 1, 2, 5, 7, 9, 10, 13, 15, 17};


/*
 * Vérification de la validité d'une grille de sudoku.
 * Les valeurs déjà inscrites dans la grille `origin` doivent correspondre.
 */
int sudokuResolu(const T_sudoku *s, const T_sudoku *origin) {
#define grid(x,y) (s->grille[x+y*9].val)
#define valid_or_return(x, y)                                                              \
  {                                                                                        \
    if (grid(x, y) <= 0 || grid(x, y) > 9 || candidates[grid(x, y)-1] == 0) {              \
      printf("\nErreur de valeur, case  (%d, %d), valeur trouvée %d\n", x, y, grid(x, y)); \
      return 0;                                                                            \
    } else                                                                                 \
      candidates[grid(x, y)-1] = 0;                                                        \
  }

  int candidates[9];

  // check columns
  for (int x = 0; x < 9; x++) {
    // init candidate list
    for (int i = 0; i < 9; i++) candidates[i] = 1;
    for(int y = 0; y < 9; y++)
      valid_or_return(x, y);
  }

  // check rows
  for (int y = 0; y < 9; y++) {
    // init candidate list
    for (int i = 0; i < 9; i++) candidates[i] = 1;
    for (int x = 0; x < 9; x++)
        valid_or_return(x, y);
  }

  // check subsquares
  for (int z = 0; z < 9; z++) {
    // init candidate list
    for (int i = 0; i < 9; i++) candidates[i] = 1;
    for (int x = (z%3)*3; x < (z%3)*3+3; x++)
      for (int y = (z / 3) * 3; x < (z / 3) * 3 + 3; x++)
        valid_or_return(x, y);
  }

  if(origin != NULL) {
    for (int i = 0; i < 9 * 9; i++) {
      int origval = origin->grille[i].val;
      if (origval != 0 && s->grille[i].val != origval) {
        printf("\nErreur de valeur, la case (%d, %d) n'a pas la valeur fixée "
               "dans la grille originale.\n",
               i % 9, i / 9);
        return 0;
      }
    }
  }

  return 1;
#undef ok_or_return
#undef grid
}

int main() {
  int note = 0;
  int note_locale = 0;

  printf(
      "\n==================================================================\n");
  printf("Brute force\n");

  printf("Cela peut prendre du temps (quelques minutes) suivant votre algorithme.\n");
  fflush(stdout);

  T_sudoku sudokuOrigin, sudokuEtudiant[100];
  int i, j, test, change = 1;
  int nbInteresting = sizeof(interesting_bruteforce)/sizeof(int);

  // look only at "interesting" solutions
  for (i = 0; i < nbInteresting; i++) {
    int n = interesting_bruteforce[i];

    change = 1;
    for (j = 0; j < 81; j++) {
      sudokuEtudiant[n].grille[j].val = tests[n][j];
    }
    initialiserSudoku(&(sudokuEtudiant[n]));

    // keep a copy for comparison
    memcpy(&sudokuOrigin, &sudokuEtudiant[n], sizeof(sudokuOrigin));
    // try to find and load the good grid
    R1_sudoku(&(sudokuEtudiant[n]));
    while (change) {
      change = 0;
      change += R2_sudoku(&(sudokuEtudiant[n]));
      change += R1_sudoku(&(sudokuEtudiant[n]));
      change += R3_sudoku(&(sudokuEtudiant[n]));
      change += R1_sudoku(&(sudokuEtudiant[n]));
    }

    printf("Application de la force brute sur la grille %d (%d/%d)...", n, i, nbInteresting);
    fflush(stdout);
    bruteForce(&(sudokuEtudiant[n]));
    printf("Done!\n");

    // check sudoku complete and corresponding to the original sudoku to solve
    if (sudokuResolu(&sudokuEtudiant[n], &sudokuOrigin)) {
      note_locale += 1;
    } else {
      printf("\nErreur sur le sudoku : %d\n", n);
    }
  }
  printf("\n\nTotal: %d/10\n", note_locale);
  note += note_locale;
  fprintf(stderr, "%d", note);
  return 0;
}
