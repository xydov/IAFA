/*
 * Macros utilisés pour réaliser des tests automatiques.
 */
#ifndef TEST_H
#define TEST_H

#define VERT	"\x1b[1;32m"
#define ROUGE	"\x1b[1;31m"
#define NORMAL	"\x1b[0m"

#define INIT_TEST \
	int err = 0, test = 0; \
	int errs[1000]

#define FIN_TEST \
	if(err == 0) \
		printf(VERT "SUCCES:" NORMAL " tous les test sont reussis !\n"); \
	else { \
		printf(ROUGE "ERREUR:" NORMAL " %d erreurs sur %d tests.\n\t", err, test); \
		for(int i = 0; i < err; i++) printf("[%d] ", errs[i]); \
		printf("\n"); \
	}

#define TEST(c) \
	{ \
		test++; \
		printf("[%d] test %s:%d: %s\n", test, __FILE__, __LINE__, #c); \
		if(!(c)) \
			{ printf(ROUGE "\tERREUR" NORMAL "\n"); errs[err] = test; err++; } \
		else \
			printf(VERT "\tOK" NORMAL "\n"); \
	}
			
#endif	/* TEST_H */
