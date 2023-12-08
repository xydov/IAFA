CC = cc
CFLAGS =-Wall -g -DNDEBUG

EXECS = tri_rap_derec

all : $(EXECS)

clean:
	rm -rf $(EXECS) *.o

tri_rap_derec: tri_rapide_moodle.o pile.o
	$(CC) -o $@ $^ $(CFLAGS)

pile.o: pile.h



%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)