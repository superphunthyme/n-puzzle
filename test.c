#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "heap.h"
#include "solvers.h"

int main(int argc, char *argv[]) {

  // Uncomment to seed if initializing random board
  srand(time(NULL));

  clock_t diff = 0;
  board *b = &(board){};
  if (argc == DIM * DIM + 1) {
    int tiles[DIM * DIM];
    for(int i = 1; i < argc; ++i) {
      tiles[i-1] = atoi(argv[i]);
    }
    init_board(b, tiles, DIM);
    if(!is_solvable(b)) {
        fprintf(stderr, "Puzzle is not solvable.\n");
        return 1;
    }
  }
  else {
    init_board_random(b, DIM);
  }
  printf("Initial Board:\n");
  print_board(b);
  printf("\n");

  clock_t start = clock();
  a_star_solve(b);
  diff = clock() - start;
  int msec = diff * 1000 / CLOCKS_PER_SEC;
  printf("A*: Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);

  start = clock();
  ida_star_solve(b);
  diff = clock() - start;
  msec = diff * 1000 / CLOCKS_PER_SEC;
  printf("IDA*: Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);

}
