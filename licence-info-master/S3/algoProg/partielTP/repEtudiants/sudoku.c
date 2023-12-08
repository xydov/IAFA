#include "sudoku.h"

/* Partie 1 : Completer l'une OU l'autre des deux fonctions */

//  < >

T_coordonnees coord_debut_region(int n_region)
{
  T_coordonnees coord;
  coord.ligne = 3 * (n_region / 3);
  coord.colonne = 3 * (n_region % 3);
  return coord;
}

int num_case(T_coordonnees c)
{
  return 9 * c.ligne + c.colonne;
}

int maxCandidatRegion(T_sudoku s, int indiceRegion)
{

  /* A completer */
  int maxCandidat = 0;
  int id_el_groupement;
  T_coordonnees coord_case = coord_debut_region(indiceRegion);
  T_coordonnees coord_traitement;

  for (int x = coord_case.ligne; x < (coord_case.ligne + 3); x++)
  {
    for (int y = coord_case.colonne; y < (coord_case.colonne + 3); y++)
    {
      coord_traitement.ligne = x;
      coord_traitement.colonne = y;
      id_el_groupement = num_case(coord_traitement);

      if (s.grille[id_el_groupement].val == 0)
      {

        for (int i_candidat = 0; i_candidat < s.grille[id_el_groupement].n_candidats; i_candidat++)
        {
          if (s.grille[id_el_groupement].candidats[i_candidat] > maxCandidat)
          {
            maxCandidat = s.grille[id_el_groupement].candidats[i_candidat];
          }
        }
      }
    }
  }
  return maxCandidat;
}

void transposerSudoku(T_sudoku *s_initial)
{

  /* A completer */
}

/* Partie 2 : Completer la fonction */

void insert_value(T_case *c, int value)
{
  int ind_insertion = 0;
  while (value > c->candidats[ind_insertion])
  {
    ind_insertion ++;
  }

  int i = c->n_candidats - 1;

  while (i >= ind_insertion)
  {
    c->candidats[i + 1] = c->candidats[i];
    i --;
  }
  c->candidats[ind_insertion] = value;
}

int value_in_cand(T_case *c, int value)
{
  for (int i = 0; i < c->n_candidats; i++)
  {
    if (c->candidats[i] == value)
    {
      return 1;
    }
  }
  return 0;
}

void ajouterCandidat(T_case *s_case, int value)
{
  int temp;
  if (s_case->n_candidats == 0)
  {
    temp = s_case->val;
    s_case->val = 0;
    s_case->candidats[0] = temp;
    s_case->n_candidats ++;    
  }
  

  if (!value_in_cand(s_case, value))
  {
    insert_value(s_case, value);
  }
}
