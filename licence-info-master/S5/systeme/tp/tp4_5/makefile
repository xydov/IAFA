CFLAGS=-Wall -Wextra -Wshadow -pedantic -Werror

main:
	gcc -g -Wall -o e1 tp45_exo1.c

e2v1:
	gcc -g -Wall -o e2v1 tp45_exo2-v1_base.c
	
boucle:
	gcc -o boucle afficher.c
	
e2v2: boucle
	gcc -g -Wall -o e2v2 tp45_exo2-v2_base.c

e3:
	gcc -g tp45_exo3_base.c -o tp45_exo3 -Wall

e4:
	gcc -g $(CFLAGS) tp45_exo4.c -o tp45_exo4

clean:
	rm -rf e1 e2v1 e2v2 boucle tp45_exo3 tp45_exo4