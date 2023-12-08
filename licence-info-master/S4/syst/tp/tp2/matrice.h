#ifndef MATRICE_H
#define MATRICE_H

#define NB_LIGNES_MAX 12
#define NB_COLONNES_MAX 24

extern void initialiserMatrice( int matrice[NB_LIGNES_MAX][NB_COLONNES_MAX],
				unsigned nbLignes, unsigned nbColonnes);
extern void afficherMatrice( int matrice[NB_LIGNES_MAX][NB_COLONNES_MAX],
			     unsigned nbLignes, unsigned nbColonnes);
#endif
