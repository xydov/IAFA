FLAGS = -Wall
CC = gcc
LIB_NC = -lncurses

EXECS = client serveur1 serveur2 test-jeu-centralise test-jeu-centralise-nc

all: $(EXECS)

client: client.o
	$(CC) $(FLAGS) $^ -o $@ $(LIB_NC)

serveur1: serveur1.o tresor.o
	$(CC) $(FLAGS) $^ -o $@

serveur2: serveur2.o tresor.o
	$(CC) $(FLAGS) $^ -o $@ -lpthread

test-jeu-centralise: test-jeu-centralise.o tresor.o
	$(CC) $(FLAGS) $^ -o $@

test-jeu-centralise-nc: test-jeu-centralise-nc.o tresor.o
	$(CC) $(FLAGS) $^ -o $@ $(LIB_NC)

%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $<

clean:
	rm -f $(EXECS)
	rm -f *.o
