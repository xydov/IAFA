/*
 * Vérification de parenthèses.
 */

#include <stdio.h>

#include "pile.h"

int main() {
	pile_t p;
	char c;
	int colonne = 1;
	int ligne = 1;
	int Finisher = 0;

	init_pile(&p);

	scanf("%c", &c);
	while(c != '$') {

		if (c == '\n') {
			ligne ++;
			colonne = 1;
		} else {
			colonne ++;
		}

		if ((c == '(') || (c =='{') || (c == '[')) {
			empiler(&p, c);
		} else if (!pile_vide(&p)) {
			if ((c == ')' && sommet(&p) == '(')
					|| ((c == ']') && (sommet(&p) == '['))
					|| ((c == '}') && (sommet(&p) == '{')))
					{
				depiler(&p);
			} else {
				Finisher ++;
			}
		}

		scanf("%c", &c);
	}

	if (Finisher == 0) {
		printf("ERREUR de Parenthésage ([{}])\n" );
		printf("Ligne: %d | Colonne: %d\n", ligne, colonne);
	} else {
		printf("Parenthésage Ok ([{}])\n");
	}

	return 0;
}
