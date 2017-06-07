CC=gcc
CC_OPT=-Wall -std=gnu11 -g -O2
PRGM=n-puzzle
DEPS=test.c board.c state.c heap.c linked-list.c

MAIN: $(DEPS)
	$(CC) $(CC_OPT) $(DEPS) -o $(PRGM)

clean:
	rm $(PRGM)
