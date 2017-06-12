#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "linked-list.h"
#define DIM 4

typedef struct linked_list linked_list;

// Maybe make tiles variable length
typedef struct board {
  int dim;
  int tiles[DIM*DIM];
  int manhattan;
  int zero_location;
} board;

void init_board_random(board *b, int size);
void init_board(board *b, int tiles[], int size);
int zero_location(board *b);
bool is_solved(board *b);
bool is_solvable(board *b);
void generate_random_tiles(board *b);
int manhattan(board *b);
bool equals(board *b1, board *b2);
void swap_zero(board *b, int location);
void neighbours(board *b, linked_list *neighbours);
void print_board(board *b);
void shuffle_tiles(int *tiles, size_t n);
