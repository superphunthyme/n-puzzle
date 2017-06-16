CC=gcc
CC_OPT=-Wall -std=gnu11 -O2
CC_DBG_OPT=-Wall -std=gnu11
PRGM=n-puzzle
DEPS=test.c board.c state.c heap.c linked-list.c solvers.c

MAIN: $(DEPS)
	$(CC) $(CC_OPT) $(DEPS) -o $(PRGM)

clean:
	rm $(PRGM)

debug:
	$(CC) $(CC_DBG_OPT) $(DEPS) -g -o $(PRGM)
