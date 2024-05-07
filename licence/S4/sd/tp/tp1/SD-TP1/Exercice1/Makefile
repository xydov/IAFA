CC = gcc
CFLAGS = -Wall

EXEC = stack_ex1

ifeq ($(DEBUG),yes)
	CFLAGS += -g
else
	CFLAGS += -O3 -DNDEBUG
endif

all: staticstack
	@make clean -s

staticstack: staticstack.o main.o
	@$(CC) -o $(EXEC) $^

staticstack.o: staticstack.c
	@$(CC) -o staticstack.o -c staticstack.c $(CFLAGS)

main.o: main.c stack.h
	@$(CC) -o main.o -c main.c $(CFLAGS)



.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)


doc: stack.h main.c
	doxygen documentation/TP1

dedocer:
	rm -rf documentation/html/