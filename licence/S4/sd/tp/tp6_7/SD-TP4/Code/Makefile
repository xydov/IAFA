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

EXEC=skiplisttest
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
	@rm -rf $(EXEC) documentation/html

doc: rng.h skiplist.h
	@doxygen documentation/TP4-5


tests : $(EXEC)
	@$(BASH) ../Test/test_script.sh $(EXEC)
	
rng.o : rng.h
skiplist.o : skiplist.h rng.h
skiplisttest.o : skiplist.h rng.h
doc : rng.h skiplist.h

