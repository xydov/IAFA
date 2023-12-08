#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/** Main function for testing the Stack implementation.
 * The main function expects one parameter that is the file where values added to the stack are
 * to be read.
 *
 * This file must contain the following informations :
 * - on the first line, the number of values to be added to the stack,
 * - on the second line, the values to be added, separated by a space (or tab).
 *
 * The values will be added to the stack in the order they are read from the file.
 */

void close_free(FILE* f, Stack s)
{
	fclose(f);	
	free(s);
}


int main(int argc, char **argv)
{
	Stack theStack;
	FILE *input;
	int n;

	if (argc < 2)
	{
		fprintf(stderr, "usage : %s filename\n", argv[0]);
		close_free(input, theStack);
		return 1;
	}

	input = fopen(argv[1], "r");

	if (!input)
	{
		perror(argv[1]);

		close_free(input, theStack);
		return 1;
	}

	theStack = stack();
	fscanf(input, "%d", &n);

	if (n >= STACK_SIZE)
	{
		fprintf(stderr, "Erreur taille Stack\n");

		close_free(input, theStack);
		return 1;
	}

	for (int i = 0; i < n; ++i)
	{
		int v;
		fscanf(input, "%d", &v);
		theStack = push(theStack, v);
	}

	dump(theStack, stderr);

	while (!empty(theStack))
	{
		printf("Removing element %d\n", top(theStack));
		theStack = pop(theStack);
	}

	close_free(input, theStack);
	
	return 0;
}
