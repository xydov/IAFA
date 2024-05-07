#include <stdlib.h> // abs()

/* =================================================================== */
// Fonction qui calcule le résultat du coup du joueur.
// Le coup consite en une abcsisse et une ordonnée proposées (xp, yp).
// Les coordonnées cibles sont celles du trésor (xt, yt).
// Le plateau est défini par une matrice n x n
// La fonction retourne :
//    10 : si les coordonnées fournies désignent une case hors du plateau
//     0 : si les coordonnées jouées sont celles du trésor
//     1 : si les coordonnées jouées sont celles d'une case jouxtant
//         horizontalement ou verticalement celle du trésor
//     2 : si les coordonnées jouées sont celles d'une case :
//           - soit séparée de celle du trésor par une autre case,
//             verticalement ou horizontalement
//           - soit jouxtant immédiatement la case du trésor mais en diagonale
//     3 : dans tous les autres cas
/* =================================================================== */
int recherche_tresor(int n, int xt, int yt, int xp, int yp) {
    int v;
    if ( xp < 1 || yp < 1 || xp > n || yp > n) return 10; // hors plateau
    if ( xp == xt && yp == yt) return 0; // case tresor
    if ( xp == xt || yp == yt) { // croix
        v = abs((xt + yt)-(xp + yp));
        return( v < 3 ? v : 3);
    }
    if ((abs (xp - xt) == 1) && (abs(yp - yt) == 1)) // diagonale
        return 2;
    else // ailleurs
        return 3;
}
