#include "sudoku.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>

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

/* Utilise pour comparer les solution (y compris intermediaires) de reference avec les solutions des etudiants : renvoie 1 ssi les deux sudokus sont identiques */
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
  int note_locale = 0;
  FILE* f, *fpre, *f1;

  

    printf("\n==================================================================\n");
    printf("Regle R1\n");
    f=fopen("sols/solR1.txt","r");
    fpre = fopen("sols/solPrecomputedR1.txt", "r");
    T_sudoku sudokuSol,sudokuEtudiant[100];
    int i,j,test;
    // FIXME not 100 anymore, depends on the precomputed amount
    for(i=0;i<100;i++){
      for(j=0;j<81;j++){
        sudokuEtudiant[i].grille[j].val=tests[i][j];
      }

      // use the pre-computed solutions which admits some differences using R1
      //initialiserSudoku(&(sudokuEtudiant[i]));
      sudokuEtudiant[i] = chargerSudokuComplet(fpre);
      sudokuSol=chargerSudokuComplet(f);
      R1_sudoku(&(sudokuEtudiant[i]));
      test=comparerSudokus(&(sudokuEtudiant[i]),&sudokuSol);
      if(test==81){
        note_locale+=1;
      }
      else{
        printf("\nErreur sur le sudoku : %d, case : %d",i,test);
      }
    }
    printf("\n\nTotal: %d/100\n", note_locale);
    note+=note_locale;
    fclose(f);
    fprintf(stderr,"%d",note_locale);
    return 0;
}

