#makefile pile dynamique
CC = cc
CFLAGS =-Wall -g

EXECS = \
	test-pile \
	verif-parent \
	somme

all : $(EXECS)

clean:
	rm -rf $(EXECS) *.o

test-pile: test.o pile.o
	$(CC) -o $@ $^ $(CFLAGS)

verif-parent: verif-parent.o pile.o
	$(CC) -o $@ $^ $(CFLAGS)

somme: somme.o pile.o
	$(CC) -o $@ $^ $(CFLAGS)

pile.o: pile.h
main.o: pile.h test.h

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)
