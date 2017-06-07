#include "state.h"

void init_board_state(state *s, board *current, state *prev, int moves) {
  s->current = current;
  s->previous = prev;
  s->moves = moves;
  s->score = current->manhattan + moves;
}
