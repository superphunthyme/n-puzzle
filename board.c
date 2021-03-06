#include <stdbool.h>
#include <stdio.h>
#include "board.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

static int zero_location(board *b);
static int manhattan(board *b);
static void shuffle_tiles(int *tiles, size_t n);
static void generate_random_tiles(board *b);

void init_board_random(board *b, int size) {
  b->dim = size;
  do {
    generate_random_tiles(b);
  } while (!is_solvable(b));
  b->manhattan = manhattan(b);
  b->zero_location = zero_location(b);
}

void init_board(board *b, int tiles[], int size) {
  b->dim = size;
  memcpy(b->tiles, tiles, size * size * sizeof(int));
  b->manhattan = manhattan(b);
  b->zero_location = zero_location(b);
}

static int zero_location(board *b) {
  for (int i = 0; i < b->dim * b->dim; ++i) {
    if (b->tiles[i] == 0) {
      return i;
    }
  }
  // Should never be reached, just pleasing the compiler
  return -1;
}

bool is_solved(board *b) {
  return b->manhattan == 0;
}

bool is_solvable(board *b) {
  int inversions = 0;
  for (int i = 0; i < b->dim * b->dim - 1; ++i) {
    for (int j = i; j < b->dim * b->dim; ++j) {
      if(b->tiles[i] !=0 && b->tiles[j] != 0 && b->tiles[i] > b->tiles[j])
        inversions += 1;
    }
  }
  return inversions % 2 == 0;
}

static void generate_random_tiles(board *b) {
  for (int i = 0; i < b->dim * b->dim; ++i)
    b->tiles[i] = i;
  shuffle_tiles(b->tiles, b->dim * b->dim);
}

static int manhattan(board *b) {
  int manhattan = 0;
  for (int i = 0; i < b->dim * b->dim; ++i) {
    if (b->tiles[i] != 0) {
      int current_row = i / b->dim;
      int current_col = i % b->dim;
      int correct_row = (b->tiles[i] -1) / b->dim;
      int correct_col = (b->tiles[i] -1) % b->dim;
      manhattan += abs(correct_row - current_row) + abs(current_col - correct_col);

      // Linear conflict heuristic
      if(current_row == correct_row) {
        for (int j = b->dim * current_row; j < b->dim * current_row + current_col; ++j) {
          int j_current_row = j / b->dim;
          int j_correct_row = (b->tiles[j] -1) / b->dim;
          if(j_current_row == j_correct_row) {
            int j_current_col = j % b->dim;
            int j_correct_col = (b->tiles[j -1]) % b->dim;
            if (correct_col < j_correct_col && current_col > j_current_col) {
              manhattan += 2;
            }
          }
        }
      }
    }
  }
  return manhattan;
}

bool equals(board *b1, board *b2) {
  for (int i = 0; i < b1->dim*b1->dim; ++i) {
    if (b1->tiles[i] != b2->tiles[i]) {
      return false;
    }
  }
  return true;
}

void swap_zero(board *b, int location) {
  b->tiles[b->zero_location] = b->tiles[location];
  b->tiles[location] = 0;
  b->zero_location = location;
  b->manhattan = manhattan(b);
}

void neighbours(board *b, linked_list *l_neighbours) {
  if(b->zero_location % b->dim > 0) {
    board *bn = malloc(sizeof(board));
    *bn = *b;
    swap_zero(bn, b->zero_location - 1);
    list_add(bn, l_neighbours);
  }
  if(b->zero_location % b->dim < b->dim - 1 ) {
    board *bn = malloc(sizeof(board));
    *bn = *b;
    swap_zero(bn, b->zero_location + 1);
    list_add(bn, l_neighbours);
  }
  if(b->zero_location / b->dim > 0) {
    board *bn = malloc(sizeof(board));
    *bn = *b;
    swap_zero(bn, b->zero_location - b->dim);
    list_add(bn, l_neighbours);
  }
  if(b->zero_location / b->dim < b->dim - 1) {
    board *bn = malloc(sizeof(board));
    *bn = *b;
    swap_zero(bn, b->zero_location + b->dim);
    list_add(bn, l_neighbours);
  }
}

void print_board(board *b) {
  for (int i = 0; i < b->dim * b->dim; ++i) {
    printf("%-3d", b->tiles[i]);
    if (i % b->dim == b->dim - 1) {
      printf("\n");
    }
  }
  printf("\n");
}

static void shuffle_tiles(int *array, size_t n)
{
  if (n > 1)
  {
    //srand(time(NULL));
    size_t i;
    for (i = 0; i < n - 1; ++i)
    {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}
