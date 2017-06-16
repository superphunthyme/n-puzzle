#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"
#include "solvers.h"

#define FOUND -1
#define NOT_FOUND -2

void a_star_solve(board *b) {

  if (is_solved(b)) {
    printf("Board was already solved\n");
    return;
  }

  state *initial_state = malloc(sizeof(state));
  init_board_state(initial_state, b, NULL, 0);

  heap states;
  heap_create(&states, 0, NULL);
  heap_insert(&states, &initial_state->score, initial_state);

  int *min_key;
  board *neighbour;
  state *best_state = initial_state;
  state *neighbour_state;
  int counter = 0;

  linked_list *to_delete = list_create();

  while(1) {
    heap_delmin(&states, &min_key, &best_state);
    list_add(best_state, to_delete);
    if(best_state->current->manhattan == 0 ) {
      break;
    }
    linked_list *list_neighbours = list_create();
    neighbours(best_state->current, list_neighbours);

    while(!list_is_empty(list_neighbours)) {
      neighbour = list_get(0, list_neighbours);
      if(!best_state->previous || !equals(neighbour, best_state->previous->current)) {
        neighbour_state = malloc(sizeof(state));
        check_pointer(neighbour_state);
        init_board_state(neighbour_state, neighbour, best_state, best_state->moves + 1);
        heap_insert(&states, &neighbour_state->score, neighbour_state);
      }
      list_remove(0, list_neighbours);
    }
    free(list_neighbours);
  }


  while(best_state->previous) {
    counter++;
    print_board(best_state->current);
    best_state = best_state->previous;
  }

  // Freeing all states popped from heap
  while(!list_is_empty(to_delete)) {
    initial_state = list_get(0, to_delete);
    free(initial_state->current);
    list_remove(0, to_delete);
  }
  free(to_delete);

  // Freeing states left on heap
  heap_foreach(&states, free_states);

  print_board(b);
  printf("Solved in %d moves\n", counter);
  heap_destroy(&states);
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

void free_states(int *key, state *value) {
  free(value->current);
  free(value);
}
