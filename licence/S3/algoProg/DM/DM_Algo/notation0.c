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
  FILE* f,*f1;
    /* Test des fonctions d'initialisation et de conversion des indices */
    /* Initialisation */
    printf("\n==================================================================\n");
    printf("Lecture et initialisation d'un sudoku\n");
    T_sudoku s = lireSudoku("sudoku_ex_lecture.txt"),s1;
    initialiserSudoku(&s);
    f1 = fopen("sols/solLecture.txt","r");
    s1=chargerSudokuComplet(f1);
    int test=comparerSudokus(&s,&s1);
    if(test==81){
      note_locale+=1;
    }else{
      printf("\nErreur sur le sudoku sudoku_ex_lecture, case : %d",test);
    }
    printf("\n\nTotal: %d/1\n", note_locale);
    note+=note_locale;
    note_locale=0;
    fclose(f1);
    /* Indices et coordonnees */
    printf("\n==================================================================\n");
    printf("Fonctions de conversion d'indices\n");
    int i;
    T_coordonnees coords;
    for(i=0;i<81;i++){
      coords = obtenirCoords(indices[i]);
      if(i==obtenirIndice(coords)){
	note_locale+=1;
      }else{
	printf("\nErreur avec l'indice: %d",i);
      }
    }
    printf("\n\nTotal: %d/81\n", note_locale);
    note+=note_locale;
    /* Indices et regions */
    note_locale=0;
    int resultat;
    f = fopen("resultatsRegion.txt","r");
    printf("\n==================================================================\n");
    printf("Indice region en fonction des coordonnees\n");
    for(i=0;i<81;i++){
      fscanf(f,"%d ",&resultat);
      if(indiceRegion(obtenirCoords(i))==resultat){
	note_locale+=1;
      }
      else{
	printf("\nErreur avec l'indice: %d",i);
      }
    }

    printf("\n==================================================================\n");
    printf("Coordonnees du debut de region\n");
    int l,c;
    for(i=0;i<9;i++){
      coords=debutRegion(indRegion[i]);
      fscanf(f,"%d,%d ",&l,&c);
      if(coords.ligne==l && coords.colonne == c){
	note_locale+=1;
      }
      else{
	printf("\nErreur avec l'indice: %d",i);
      }
    }
    printf("\n\nTotal: %d/90\n", note_locale);
    note+=note_locale;
    fclose(f);
    fprintf(stderr,"%d",note);
    return 0;
}
