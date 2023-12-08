/*
 * Vérification de parenthèses.
 */

#include <stdio.h>

#include "pile.h"

int main() {
	pile_t p;
	char c;

	init_pile(&p);

	scanf("%c", &c);
	while(c != '$') {

		if (c == '(') {
			empiler(&p, c);
		} else if (c == ')') {
			depiler(&p);
		}

		scanf("%c", &c);
	}
	if (!pile_vide(&p)) {
		printf("ERREUR de parenthésage (..)\n" );
	}

	return 0;
}
