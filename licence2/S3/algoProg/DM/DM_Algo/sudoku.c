#include "sudoku.h"
#include <stdlib.h>
#include <stdio.h>

/* Implanter les fonctions de sudoku.h ici */

/** Retourne les coordonnees de la case a
 * partir de son indice dans le sudoku
 * @param indice indice dans le tableau de 81 cases
 * @return Coordonnees de la case
 */
T_coordonnees obtenirCoords(int indice)
{
  T_coordonnees caseSudoku;
  caseSudoku.ligne = indice / 9;
  caseSudoku.colonne = indice % 9;
  return caseSudoku;
}

/** Retourne l'indice d'une case dans
 * le sudoku a partir de ses coordonnees
 * @param coords coordonnees de la case
 * @return 
 */
int obtenirIndice(T_coordonnees coords)
{
  return 9 * coords.ligne + coords.colonne;
}

/** Retourne les coordonnees de la premiere case (en haut a gauche)
 * d'une region a partir de l'indice de cette region
 * @param indiceRegion indice de la region ciblee (0 à 8)
 * @return coordonnee de la case en haut a gauche
 */
T_coordonnees debutRegion(int indiceRegion)
{
  T_coordonnees coordPremiereCaseRegion;
  coordPremiereCaseRegion.ligne = 3 * (indiceRegion / 3);
  coordPremiereCaseRegion.colonne = 3 * (indiceRegion % 3);
  return coordPremiereCaseRegion;
}

/** Retourne l'indice de la region a laquelle
 * appartient la case ayant ces coordonnees
 * @param coords coordonnes de la case
 * @return indice de la region
 */
int indiceRegion(T_coordonnees coords)
{
  return 3 * (coords.ligne / 3) + (coords.colonne / 3);
}

/** Lire une grille et initialiser un sudoku
 * @param chemin chemin vers le fichier contenant le sudoku
 * @return le T_sudoku du fichier
 */
T_sudoku lireSudoku(char *chemin)
{
  FILE *fichierSudoku;
  T_sudoku sudokuNonInit;

  int caractereActuel = 0;
  int conteur = 0;

  fichierSudoku = fopen(chemin, "r");

  if (fichierSudoku == NULL)
  {
    printf("Fichier Introuvable");
  }
  else
  {
    do
    {
      caractereActuel = fgetc(fichierSudoku);
      if (caractereActuel == '\n' || caractereActuel == ' ' || caractereActuel == EOF)
      {
        continue;
      }
      sudokuNonInit.grille[conteur].val = (int)(caractereActuel - '0') /*(int)caractereActuel*/;
      conteur++;

    } while (caractereActuel != EOF);

    fclose(fichierSudoku);
  }
  return sudokuNonInit;
}

/** Initialise le nombre de candidats et le la valeur
 *  des candidats en fonction de la valeur
 * @param s Le sudoku avec les valeurs du fichier
 */
void initialiserSudoku(T_sudoku *s)
{
  for (int i = 0; i < 81; i++)
  {
    if (s->grille[i].val != 0)
    {
      s->grille[i].n_candidats = 0;

      for (int idCaseCandidats = 0; idCaseCandidats < 9; idCaseCandidats++)
      {
        s->grille[i].candidats[idCaseCandidats] = 0;
      }
    }
    else
    {
      s->grille[i].n_candidats = 9;
      for (int idCaseCandidats = 0; idCaseCandidats < 9; idCaseCandidats++)
      {
        s->grille[i].candidats[idCaseCandidats] = idCaseCandidats + 1;
      }
    }
  }
}

/** Renvoie l'indice de val dans le tableau de candidats de c.
 * Si l'indice n'est pas present, renvoie c.n_candidats
 * @param val valeur dans le tableau de candidats
 * @param c Case dans laquelle on recherche l'id de la valeur
 * @return le nombre de candidats ou 
 * l'indice de la valeur dans le tableau de candidats
 */
int rechercherValeur(int val, T_case c)
{
  for (int i = 0; i < c.n_candidats; i++)
  {
    if (c.candidats[i] == val)
    {
      return i;
    }
  }
  return c.n_candidats;
}

/** ival est l'indice de la valeur a supprimer, on considere
 * que la valeur a supprimer est presente dans les candidats de la case
 * @param ival indice de la valeur a supprimer
 * @param pc pointeur sur la case du sudoku
 */
void supprimerValeur(int ival, T_case *pc)
{
  pc->candidats[ival] = 0;
  for (int i = ival; i < pc->n_candidats - 1; i++)
  {
    pc->candidats[i] = pc->candidats[i + 1];
  }

  pc->n_candidats--;
  for (int i = pc->n_candidats; i < 9 - pc->n_candidats; i++)
  {
    pc->candidats[i] = 0;
  }
}

/** Afficher un sudoku: 9 lignes de 9 entiers
 * separes par des tabulations (\t)
 * @param s Le sudoku a afficher
 */
void afficherSudoku(T_sudoku s)
{
  for (int i = 1; i <= 81; i++)
  {
    printf("%d\t", s.grille[i - 1].val);
    if (i % 9 == 0)
    {
      printf("\n");
    }
  }
}

/* Fonctions personnelles */

/** Affecte une valeur a une case, en mettant le nombre de candidats 
 * et les candidats de cette case a 0
 * @param idValeur indice de la valeur dans candidats[] qui sera affecter
 * @param pc pointeur sur une case
 */
void affectationIndiceValeurACase(int idValeur, T_case *pc)
{
  if (pc->candidats[idValeur] != 0)
  {

    // n_candidats => 0
    // tt cases de candidiats du tableau doivent être mises a 0
    pc->val = pc->candidats[idValeur];
    // remplacer par supprimer ??
    for (int i = 0; i < 9 /*pc->n_candidats*/; i++)
    {
      pc->candidats[i] = 0;
    }
    pc->n_candidats = 0;
  }
}


/* Implementation des regles */

//==================  R1  ==================//

int retireCandidatGroupement(T_sudoku *ps, int indDeComparaison)
{
  int verifSiModification = 0;
  int valeurASupprimer = ps->grille[indDeComparaison].val;
  int indValeurASupprimer;
  int indDansGroupement;
  T_coordonnees coordDebutRegion = debutRegion(indiceRegion(obtenirCoords(indDeComparaison)));

  for (int x = coordDebutRegion.ligne; x < coordDebutRegion.ligne + 3; x++)
  {
    for (int y = coordDebutRegion.colonne; y < coordDebutRegion.colonne + 3; y++)
    {
      T_coordonnees coordValeur = {x, y};
      indDansGroupement = obtenirIndice(coordValeur);
      // on verifie que la case est = 0
      if (ps->grille[indDansGroupement].val == 0 && indDansGroupement != indDeComparaison)
      {
        // on cherche la valeur a supprimer dans le tableau de candidats de indDansGroupement
        indValeurASupprimer = rechercherValeur(valeurASupprimer, ps->grille[indDansGroupement]);
        if (indValeurASupprimer < ps->grille[indDansGroupement].n_candidats)
        {
          supprimerValeur(indValeurASupprimer, &ps->grille[indDansGroupement]);
          verifSiModification = 1;
        }
      }
    }
  }
  if (verifSiModification)
  {
    return 1;
  }
  return 0;
}

int retireCandidatLigne(T_sudoku *ps, int indDeComparaison)
{
  int verifSiModification = 0;
  int valeurASupprimer = ps->grille[indDeComparaison].val;
  int indValeurASupprimer;
  T_coordonnees coordCase = obtenirCoords(indDeComparaison);

  for (int indDansLigne = coordCase.ligne * 9; indDansLigne < coordCase.ligne * 9 + 9; indDansLigne++)
  {
    // on verifie que la case est = 0
    if (ps->grille[indDansLigne].val == 0 && indDansLigne != indDeComparaison)
    {
      // on cherche la valeur a supprimer dans le tableau de candidats de indDansLigne
      indValeurASupprimer = rechercherValeur(valeurASupprimer, ps->grille[indDansLigne]);
      if (indValeurASupprimer < ps->grille[indDansLigne].n_candidats)
      {
        supprimerValeur(indValeurASupprimer, &ps->grille[indDansLigne]);
        verifSiModification = 1;
      }
    }
  }
  if (verifSiModification)
  {
    return 1;
  }
  return 0;
}

int retireCandidatColonne(T_sudoku *ps, int indDeComparaison)
{
  int verifSiModification = 0;
  int valeurASupprimer = ps->grille[indDeComparaison].val;
  int indValeurASupprimer;
  T_coordonnees coordCase = obtenirCoords(indDeComparaison);

  for (int indDansColo = coordCase.colonne; indDansColo <= 72 + coordCase.colonne; indDansColo += 9)
  {
    // on verifie que la case est = 0
    if (ps->grille[indDansColo].val == 0 && indDansColo != indDeComparaison)
    {
      // on cherche la valeur a supprimer dans le tableau de candidats de indDansColo
      indValeurASupprimer = rechercherValeur(valeurASupprimer, ps->grille[indDansColo]);
      if (indValeurASupprimer < ps->grille[indDansColo].n_candidats)
      {
        supprimerValeur(indValeurASupprimer, &ps->grille[indDansColo]);
        verifSiModification = 1;
      }
    }
  }
  if (verifSiModification)
  {
    return 1;
  }
  return 0;
}


/** Applique R1 sur la case 
 * @param pc un pointeur sur une case
 * @return 1 si une modification a eu lieu
 */
int R1_case(T_case *pc)
{
  if (pc->n_candidats == 1)
  {
    affectationIndiceValeurACase(0, pc);
    return 1;
  }
  return 0;
}

/** Applique R1 sur la case
 * @param ps pointeur sur le sudoku
 * @return 1 si il y a eu une modification, 0 sinon
 */
int R1_sudoku(T_sudoku *ps)
{
  int verifSiModification = 0;
  for (int id = 0; id < 81; id++)
  {
    //  Si R1 a été appliqué
    if (R1_case(&ps->grille[id]))
    {
      verifSiModification += retireCandidatLigne(ps, id);
      verifSiModification += retireCandidatColonne(ps, id);
      verifSiModification += retireCandidatGroupement(ps, id);
    }
  }
  if (verifSiModification)
  {
    return 1;
  }
  return 0;
}

//==================  R2  ==================//

/** Mets a jours les n_candidats et candidats de la case
 * correspondant a l'indice passée en parametre, en fonction
 * des valeurs des cases des groupements
 * @param indCase indice de la case sur laquelle on applique R2
 * @param ps poiteur sur un sudoku
 * @return 1 si la regle a ete appliqué, 0 sinon
 */
int R2_case(int indCase, T_sudoku *ps)
{
  //  Ligne :
  int verifSiModification = 0;
  if (ps->grille[indCase].val == 0)
  {

    T_coordonnees coordCase = obtenirCoords(indCase);
    int ind_valeur;
    int val;

    //  parcours la ligne de indCase(9*coordCase.ligne à ...+9)
    for (int x = (9 * coordCase.ligne); x < ((9 * coordCase.ligne) + 9); x++)
    {
      // x: indice de la case de la ligne
      val = ps->grille[x].val;
      if (indCase != x && val != 0)
      {
        ind_valeur = rechercherValeur(val, ps->grille[indCase]);
        if (ps->grille[indCase].n_candidats > ind_valeur)
        {
          supprimerValeur(ind_valeur, &ps->grille[indCase]);
          verifSiModification = 1;
        }
      }
    }

    //  Colonne :

    for (int ind_ele_colo = coordCase.colonne; ind_ele_colo <= 72 + coordCase.colonne; ind_ele_colo += 9)
    {
      // ind_ele_colo: indice de la case de la colonne
      val = ps->grille[ind_ele_colo].val;
      if (indCase != ind_ele_colo && val != 0)
      {
        ind_valeur = rechercherValeur(val, ps->grille[indCase]);
        if (ps->grille[indCase].n_candidats > ind_valeur)
        {
          //  ajoutValeurACase(val, &tableauTemporaire);
          supprimerValeur(ind_valeur, &ps->grille[indCase]);
          verifSiModification = 1;
        }
      }
    }

    // Groupement :
    T_coordonnees coord_debut_region = debutRegion(indiceRegion(coordCase));
    T_coordonnees coordValeur;
    int indElementGroupement;
    for (int x = coord_debut_region.ligne; x < (coord_debut_region.ligne + 3); x++)
    {
      for (int y = coord_debut_region.colonne; y < (coord_debut_region.colonne + 3); y++)
      {
        coordValeur.ligne = x;
        coordValeur.colonne = y;
        indElementGroupement = obtenirIndice(coordValeur);
        val = ps->grille[indElementGroupement].val;

        if (indCase != indElementGroupement && val != 0)
        {
          ind_valeur = rechercherValeur(val, ps->grille[indCase]);
          if (ps->grille[indCase].n_candidats > ind_valeur)
          {
            //  ajoutValeurACase(val, &tableauTemporaire);
            supprimerValeur(ind_valeur, &ps->grille[indCase]);
            verifSiModification = 1;
          }
        }
      }
    }
  }
  return verifSiModification;
}

/** Applique R2 sur toutes les cases du sudoku,
 * renvoie 1 si une modification a eu lieu, 0 sinon
 * @param ps pointeur sur un sudoku
 * @return renvoie 1 si une modification a eu lieu, 0 sinon
*/
int R2_sudoku(T_sudoku *ps)
{
  int verifSiModification = 0;
  for (int i = 0; i < 81; i++)
  {
    if (R2_case(i, ps))
    {
      verifSiModification = 1;
    }
  }
  return verifSiModification;
}

//==================  R3  ==================//

/** Pour une valeur donnée et une cases,
 * recherche si cette valeur est dans les candidats 
 * des cases de la ligne
 * @param valCand valeur a rechercher dans les cases de la ligne
 * @param indice_case_reference indice de la case de référence
 * @param ps pointeur sur le sudoku
 * @return 1 s'il existe valCand dans les cases de la ligne,
 * 0 sinon
 */
int rechercheSiCandidatUniqueDansLigne(int valCand, int indice_case_reference, T_sudoku *ps)
{
  T_coordonnees coordCaseP = obtenirCoords(indice_case_reference);

  int ind_val_dans_cand;
  for (int id_dans_ligne = (9 * coordCaseP.ligne); id_dans_ligne < ((9 * coordCaseP.ligne) + 9); id_dans_ligne++)
  {
    // si différent de indCase de référence
    if (id_dans_ligne != indice_case_reference && ps->grille[id_dans_ligne].val == 0)
    {
      ind_val_dans_cand = rechercherValeur(valCand, ps->grille[id_dans_ligne]);
      if (ind_val_dans_cand < ps->grille[id_dans_ligne].n_candidats)
      {
        //  si le cand est dans les cand de la ligne, on renvoie 1
        return 1;
      }
    }
  }
  return 0;
}

/** Pour une valeur donnée et une cases,
 * recherche si cette valeur est dans les candidats 
 * des cases de la colonne
 * @param valCand valeur a rechercher dans les cases de la colonne
 * @param indice_case_reference indice de la case de référence
 * @param ps pointeur sur le sudoku
 * @return 1 s'il existe valCand dans les cases de la colonne,
 * 0 sinon
 */
int rechercheSiCandidatUniqueDansColonne(int valCand, int indice_case_reference, T_sudoku *ps)
{
  T_coordonnees coordCaseP = obtenirCoords(indice_case_reference);

  int ind_val_dans_cand;
  for (int ind_ele_colo = coordCaseP.colonne; ind_ele_colo <= 72 + coordCaseP.colonne; ind_ele_colo += 9)
  {
    // si différent de indCase de référence
    if (ind_ele_colo != indice_case_reference && ps->grille[ind_ele_colo].val == 0)
    {
      ind_val_dans_cand = rechercherValeur(valCand, ps->grille[ind_ele_colo]);
      if (ind_val_dans_cand < ps->grille[ind_ele_colo].n_candidats)
      {
        //  si le cand est dans les cand de la colonne, on renvoie 1
        return 1;
      }
    }
  }
  return 0;
}

/** Pour une valeur donnée et une case,
 * recherche si cette valeur est dans les candidats 
 * des cases de le groupement
 * @param valCand valeur a rechercher dans les cases du groupement
 * @param indice_case_reference indice de la case de référence
 * @param ps pointeur sur le sudoku
 * @return 1 s'il existe valCand dans les cases du groupement,
 * 0 sinon
 */
int rechercheSiCandidatUniqueDansGroupement(int valCand, int indice_case_reference, T_sudoku *ps)
{
  T_coordonnees coord_debut_region = debutRegion(indiceRegion(obtenirCoords(indice_case_reference)));
  T_coordonnees coordValeur;
  int indElementGroupement;
  for (int x = coord_debut_region.ligne; x < (coord_debut_region.ligne + 3); x++)
  {
    for (int y = coord_debut_region.colonne; y < (coord_debut_region.colonne + 3); y++)
    {
      coordValeur.ligne = x;
      coordValeur.colonne = y;
      indElementGroupement = obtenirIndice(coordValeur);
      if (indElementGroupement != indice_case_reference && ps->grille[indElementGroupement].val == 0)
      {
        int ind_val_dans_cand = rechercherValeur(valCand, ps->grille[indElementGroupement]);
        if (ind_val_dans_cand < ps->grille[indElementGroupement].n_candidats)
        {
          //  si le cand est dans les cand de la ligne, on renvoie 1
          return 1;
        }
      }
    }
  }
  return 0;
}

/** Applique R3 sur la case
 * @param indCase indice de la case traité
 * @param ps pointeur sur un sudoku
 * @return 1 si une modification a eu lieu, 0 sinon 
 */
int R3_case(int indCase, T_sudoku *ps)
{
  // On ne prend en compte uniquement les cases dant la valeur est nulles
  if (ps->grille[indCase].val != 0)
  {
    return 0;
  }
  int valArechercher;
  //  indice de chaque candidats de la case indCase
  for (int ind_candidat = 0; ind_candidat < ps->grille[indCase].n_candidats; ind_candidat++)
  {
    //  valeur a rechercher dans les cases de chaque ligne, colonne, grpmt
    valArechercher = ps->grille[indCase].candidats[ind_candidat];
    //        T_coordonnees coordCase = obtenirCoords(indCase);
    //   Ligne
    if (!rechercheSiCandidatUniqueDansLigne(valArechercher, indCase, ps))
    {
      // si pas dans les candidats de la ligne, on affecte
      affectationIndiceValeurACase(ind_candidat, &ps->grille[indCase]);
      return 1;
    }
    // Colonne
    else if (!rechercheSiCandidatUniqueDansColonne(valArechercher, indCase, ps))
    {
      // si pas dans les candidats de la colonne, on affecte
      affectationIndiceValeurACase(ind_candidat, &ps->grille[indCase]);
      return 1;
    }
    // groupement
    else if (!rechercheSiCandidatUniqueDansGroupement(valArechercher, indCase, ps))
    {
      // si pas dans les candidats du groupememt, on affecte
      affectationIndiceValeurACase(ind_candidat, &ps->grille[indCase]);
      return 1;
    }
  }
  return 0;
}

/** Applique R3 sur toutes les cases du sudoku,
 * renvoie 1 si une modification a eu lieu, 0 sinon
 * @param ps pointeur sur un sudoku
 * @return 1 si une modification a eu lieu, 0 sinon
 */
int R3_sudoku(T_sudoku *ps)
{
  int verifSiModification = 0;
  // SI R3 appliqué, supprime partout (ligne, colonne, groupement)
  for (int i = 0; i < 81; i++)
  {
    if (R3_case(i, ps))
    {
      verifSiModification += retireCandidatLigne(ps, i);
      verifSiModification += retireCandidatColonne(ps, i);
      verifSiModification += retireCandidatGroupement(ps, i);
    }
  }
  if (verifSiModification)
  {
    return 1;
  }
  return 0;
}