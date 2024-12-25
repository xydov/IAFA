#include <stdio.h>
#include "sudoku.h"

T_sudoku chargerSudokuComplet(FILE* f){
  int i,j,k;
  T_sudoku s;
  fscanf(f," Sudoku: %d ", &j);
  for(i=0;i<81;i++){
    fscanf(f," Case: %d, val: %d, n_candidats: %d, candidats: ",&j,&((s.grille[i]).val),&((s.grille[i]).n_candidats));
    for(k=0;k<9;k++){
      fscanf(f,"%d ",&((s.grille[i]).candidats[k]));
    }
  }
  return s;
}

int comparerSudokus(T_sudoku* s1, T_sudoku* s2){
  int i,j;
  for(i=0;i<81;i++){
    if((s1->grille[i]).val != (s2->grille[i]).val){
      printf("\nErreur de valeur\n");
      return i;
    }
    if((s1->grille[i]).n_candidats != (s2->grille[i]).n_candidats){
      printf("\nErreur n_candidats\n");
      return i;
    }
    for(j=0;j<(s1->grille[i]).n_candidats;j++){
      if((s1->grille[i]).candidats[j]!=(s2->grille[i]).candidats[j]){
	printf("\nErreur valeur candidat: attendu: %d, obtenu: %d",(s2->grille[i]).candidats[j],(s1->grille[i]).candidats[j]);
	return i;
      }
    }
  }
  return 81;
}

int main(){
  int note = 0;
  int note_courante =0;
  int test =0;
  FILE* fpre = fopen("solPrecomputedR1.txt", "r");
  FILE* fsol = fopen("solQ3.txt","r");
  T_sudoku sudoku, sudokuSol;

  for(int i = 0; i < 100; i++){
    sudoku = chargerSudokuComplet(fpre);
    sudokuSol = chargerSudokuComplet(fsol);
    for(int j = 0; j < 81; j++){
      ajouterCandidat(&(sudoku.grille[j]),4);
    }
    test = comparerSudokus(&sudoku,&sudokuSol);
    note_courante+=test;
  }
  note = (int) (((float) note_courante/81));
  fprintf(stderr,"%d",note);
  return 0;
}
