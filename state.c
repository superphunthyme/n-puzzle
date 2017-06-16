#include <stdlib.h>
#include "state.h"

void init_board_state(state *s, board *current, state *prev, int moves) {
    board *new = malloc(sizeof(board));
    *new = *current;
    s->current = new;
    s->previous = prev;
    s->moves = moves;
    s->score = current->manhattan + moves;
}
