#include <stdio.h>
#include "sudoku.h"
//#include "grilles.h"


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

int main(){
  int note = 0;
  FILE* f, *f1;
  printf("\n==================================================================\n");
  printf("Max candidats\n");

  /* Chargement des solutions */
  f=fopen("solQ1.txt","r");
  int maxCand[100][9];
  int poub;
  for(int i = 0; i < 100; i++){
    fscanf(f, "Sudoku %d: ", &poub);
    for(int j = 0; j < 9; j++){
      fscanf(f,"\tmax region %d = %d ", &poub, &maxCand[i][j]);
    }
  }

  /* Chargement des grilles initiales */
  f1=fopen("solPrecomputedR1.txt", "r");
  T_sudoku grilles[100];
  for(int i = 0; i < 100; i++){
    grilles[i]=chargerSudokuComplet(f1);
  }

  /* Application de la fonction et test */
  for(int i = 0; i < 100; i++){
    for(int j = 0; j < 9; j++){
      if(maxCandidatRegion(grilles[i], j) == maxCand[i][j]){
	note ++;
      }
    }
  }
  
  fprintf(stderr,"%d", note);
  return 0; 
}
