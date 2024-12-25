// Need this to use the getline C function on Linux. Works without this on MacOs. Not tested on Windows.
#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "token.h"
#include "queue.h"
#include "stack.h"

void *printToken(FILE *f, void *e)
{
	fprintf(f, "Infix	:");

}

bool isSymbol(char c)
{
	if (	strcmp(&c, "+")
		|| 	strcmp(&c, "-")
		|| 	strcmp(&c, "*")
		|| 	strcmp(&c, "/")
		|| 	strcmp(&c, "^")
		|| 	strcmp(&c, "(")
		|| 	strcmp(&c, ")"))
	{
		return true;
	}
	return false;
}


Queue *stringToTokenQueue(const char *expression)
{
	Queue *q = createQueue(q);

	char *curspos = expression;
	int lg = 0;

	while (!strcmp(curspos, "\0"))
	{
		Token *t;
		if (strcmp(curspos, " ") && strcmp(curspos, "\n"))
		{
			if (lg > 0)
			{
				//	tokenize and add to queue
				t = createTokenFromString(curspos, lg);
				q = queuePush(q, t);
			}
			lg = 0;
		}
		else if (isSymbol(*curspos))
		{
			//	tokenize and add to queue
			t = createTokenFromString(curspos, lg);
			q = queuePush(q, t);
			lg = 0;

		} else {
			// the tokenizing is done in the upper part
			lg ++;
		}

		curspos++;
	}

	return q;
}


void computeExpressions(FILE *input)
{
	/* line that is being read */
	char *line;
	size_t len = 0;
	ssize_t read;
	
	Queue *q;

	while ((read = getline(&line, &len, input)) != -1)
	{
		if (read > 1)
		{
			fprintf(stdout, "Input	: %s", line);
			q = stringToTokenQueue(line);
			queueDump(stdout, q, printToken(stdout, q));
			
			/* fprintf(stdout, "Recepition ligne de lg %zu \n", read); */
		}
	}
	if (line)
	{
		free(line);
	}
}



/** Main function for testing.
 * The main function expects one parameter that is the file where expressions to translate are
 * to be read.
 *
 * This file must contain a valid expression on each line
 *
 */
int main(int argc, char **argv)
{
	FILE *input;

	if (argc < 2)
	{
		fprintf(stderr, "usage : %s filename\n", argv[0]);
		return 1;
	}

	input = fopen(argv[1], "r");

	if (!input)
	{
		perror(argv[1]);
		return 1;
	}

	computeExpressions(input);

	fclose(input);
	return 0;
}
