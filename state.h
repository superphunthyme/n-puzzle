#pragma once
#include "board.h"

typedef struct state {
  board *current;
  struct state *previous;
  int moves;
  int score;
} state;

void init_board_state(state *s, board *current, state *prev, int moves);
