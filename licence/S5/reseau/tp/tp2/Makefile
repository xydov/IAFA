FLAGS = -Wall -pthread
# -std=gnu99
CC = gcc

EXEC = router

all: $(EXEC)

router: router.o console.o utils.o
	$(CC) $(FLAGS) *.o -o $@

# '%' matches filename
# $@  for the pattern-matched target
# $<  for the pattern-matched dependency
%.o: %.c
	$(CC) $(FLAGS) -o $@ -c $<

test_forwarding: router
	for r in 1 2 3 4 ; do \
		xterm -title "R $$r" -e ./router $$r --test-forwarding & \
	done

test_topo1: router
	for r in 1 2 3 ; do \
		xterm -title "R $$r" -e ./router $$r topos/t1.txt & \
	done

test_topo2: router
	for r in 1 2 3 4 5 ; do \
		xterm -title "R $$r" -e ./router $$r topos/t2.txt & \
	done

test_topo3: router
	for r in 1 2 3 4 ; do \
		xterm -title "R $$r" -e ./router $$r topos/t3.txt & \
	done

test_topo4: router
	for r in 1 2 3 4 5 6 7 ; do \
		xterm -title "R $$r" -e ./router $$r topos/t4.txt & \
	done

test_topo5: router
	for r in 1 2 3 4 5 ; do \
		xterm -title "R $$r" -e ./router $$r topos/t5.txt & \
	done

kill_test:
	for p in `pgrep router`; do kill $$p; done

clean: kill_test
	rm -f $(EXEC)
	rm -f *.o
	rm -f log/*
