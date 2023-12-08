#include <stdio.h>
#include "sudoku.h"
#include "solQ2.h"
#include "tests.h"

void initialiserSudoku(T_sudoku* s){
  int i,j;
  for(i=0;i<81;i++){
    if(s->grille[i].val==0){
      s->grille[i].n_candidats=9;
      for(j=1;j<10;j++){
	s->grille[i].candidats[j-1]=j;
      }
    }
    else{
      s->grille[i].n_candidats=0;
      for(j=1;j<10;j++){
	s->grille[i].candidats[j-1]=0;
      }
    }
  }
}

int main(){
  int note = 0;
  int local = 0;
  /* Chargement des grilles de test */
  T_sudoku s[100];
  for(int i=0; i<100; i++){
    for(int j = 0; j < 81; j++){
      s[i].grille[j].val = tests[i][j];
    }
    initialiserSudoku(&s[i]);
  }

  /* Application de la fonction et test */
  for(int i = 0; i<100; i++){
    transposerSudoku(&s[i]);
    local=0;
    for(int j = 0; j < 81; j++){
      if(s[i].grille[j].val==sol[i][j]){
	local++;
      }
    }
    if(local==81){
      note++;
    }
  }

  fprintf(stderr,"%d",note);

  return 0;
  
}
