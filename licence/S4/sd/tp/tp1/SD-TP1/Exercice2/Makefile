CC = gcc
CFLAGS = -Wall

EXEC = stack_ex2

ifeq ($(DEBUG),yes)
	CFLAGS += -g
else
	CFLAGS += -O3 -DNDEBUG
endif

all: dynamicstack
	@make clean -s

dynamicstack: dynamicstack.o main.o
	@$(CC) -o $(EXEC) $^

dynamicstack.o: dynamicstack.c
	@$(CC) -o dynamicstack.o -c dynamicstack.c $(CFLAGS)

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