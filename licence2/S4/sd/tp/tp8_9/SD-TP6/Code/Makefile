CC=gcc
CFLAGS=-std=c99 -Wextra -Wall -Werror -pedantic 
LDFLAGS=-lm

ifeq ($(DEBUG),yes)
	CFLAGS += -g
	LDFLAGS +=
else
	CFLAGS += -O3 -DNDEBUG
	LDFLAGS +=
endif

EXEC=bstreetest
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: 
ifeq ($(DEBUG),yes)
	@echo "Generating in debug mode"
else
	@echo "Generating in release mode"
endif
	@$(MAKE) $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC) documentation/html *.dot *.pdf

doc: bstree.h queue.h main.c
	@doxygen documentation/TP6-7

pdf : $(EXEC)
	@dot -Tpdf *.dot -O
	
queue.o : queue.h
bstree.o : bstree.h queue.h
main.o : bstree.o queue.o
doc : bstree.h queue.h main.c
