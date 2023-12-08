CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic
EXEC = tsp_exec

INCDIR = includes/
LIBDIR = lib/

CFILES = main.c $(wildcard $(LIBDIR)*)
OFILES = $(subst lib/, , $(patsubst %.c, %.o, $(CFILES)))

YELLCOL = \033[33m
REDCOL = \033[91m
GREENCOL = \033[92m
LCYANCOL = \033[96m
CYANCOL = \033[36m
ENDCOL = \033[0m

all : $(EXEC)
	@echo "$(YELLCOL)Removing all .o files$(ENDCOL)"
	@make cleanup -s \

$(EXEC) : libraries
	@echo "$(LCYANCOL)Linking all objects files together$(ENDCOL)"
	@$(CC) $(CFLAGS) $(OFILES) -o $@ -I./$(INCDIR) -lm\

libraries : $(CFILES)
	@echo "$(LCYANCOL)Compile all source files$(ENDCOL)"
	@$(CC) -c $^ -I$(INCDIR) \

test:
	@echo "$(REDCOL)Test incomming...$(ENDCOL)"


cleanup:
	@rm *.o 

.PHONY: clean
clean:
	@echo "$(GREENCOL)Cleaning base directory$(ENDCOL)"
	@rm -f $(EXEC) *.o *.csv