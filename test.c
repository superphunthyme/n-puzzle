#include <stdio.h>
#include "board.h"
#include "state.h"
#include "heap.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>

#define FOUND -1
#define NOT_FOUND -2

void a_star_solve(board *b);
int ida_star_solve(board *b);
int search(board *node, int g, int bound, int* counter);

int main(int argc, char *argv[]) {

  // Uncomment to seed if initializing random board
  //srand(time(NULL));

  clock_t diff = 0;
  board *b = &(board){};
  int tiles[DIM * DIM] = {5, 6, 3, 4, 8, 0, 1, 15, 10, 7, 2, 11, 12, 9, 14, 13};
  if (argc == DIM * DIM + 1) {
    for(int i = 1; i < argc; ++i) {
      tiles[i-1] = atoi(argv[i]);
    }
  }
  init_board(b, tiles, DIM);

  clock_t start = clock();
  //a_star_solve(b);
  diff = clock() - start;
  int msec = diff * 1000 / CLOCKS_PER_SEC;
  printf("A*: Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);

  start = clock();
  ida_star_solve(b);
  diff = clock() - start;
  msec = diff * 1000 / CLOCKS_PER_SEC;
  printf("IDA*: Time taken %d seconds %d milliseconds\n", msec/1000, msec%1000);

}

// TODO Properly free memory after function is finished
void a_star_solve(board *b) {

  if (is_solved(b)) {
    printf("Board was already solved\n");
    return;
  }

  state *initial_state = &(state){};
  init_board_state(initial_state, b, NULL, 0);

  heap states;
  heap_create(&states, 0, NULL);
  heap_insert(&states, &initial_state->score, initial_state);

  int *min_key;
  state *best_state;
  int counter = 0;
  board *neighbour;
  best_state = initial_state;

  while(best_state->current->manhattan != 0) {
    heap_delmin(&states, &min_key, &best_state);
    linked_list *list_neighbours = list_create();
    neighbours(best_state->current, list_neighbours);

    while(!list_is_empty(list_neighbours)) {
      neighbour = list_get(0, list_neighbours);
      //board *ncopy = malloc(sizeof(board));
      //memcpy(ncopy, neighbour, sizeof(board));
      // TODO Avoid copying entire board?
      init_board(neighbour, neighbour->tiles, neighbour->dim);
      if(!best_state->previous || !equals(neighbour, best_state->previous->current)) {
        state *neighbour_state = malloc(sizeof(state));
        init_board_state(neighbour_state, neighbour, best_state, best_state->moves + 1);
        heap_insert(&states, &neighbour_state->score, neighbour_state);
      }
      list_remove(0, list_neighbours);
    }
  }


  while(best_state->previous) {
    counter++;
    print_board(best_state->current);
    best_state = best_state->previous;
  }
  print_board(b);
  printf("Solved in %d moves\n", counter);
}

int ida_star_solve(board *b) {
  if (is_solved(b)) {
    printf("Board was already solved\n");
    return 0;
  }
  int bound = b->manhattan;
  int t;
  int count = 0;
  int *counter = &count;
  while(1) {
    t = search(b, 0, bound, counter);
    if (t == FOUND) {
      print_board(b);
      printf("Solved in %d moves\n", *counter);
      return bound;
    }
    if (t == __INT_MAX__) {
      return NOT_FOUND;
    }
    bound = t;
  }
}

int search(board *node, int g, int bound, int *counter) {
  int f = g + node->manhattan;
  int t;
  if (f > bound) {
    return f;
  }
  if (is_solved(node)) {
    return FOUND;
  }
  int minimum = INT_MAX;
  board *neighbour;
  linked_list *list_neighbours = list_create();
  neighbours(node, list_neighbours);
  while(!list_is_empty(list_neighbours)) {
    neighbour = list_get(0, list_neighbours);
    t = search(neighbour, g + 1, bound, counter);
    if (t == FOUND) {
      print_board(neighbour);
      list_destroy(list_neighbours);
      (*counter)++;
      return FOUND;
    }
    if (t < minimum) {
      minimum = t;
    }
    list_remove(0, list_neighbours);
  }
  free(list_neighbours);
  return minimum;
}
