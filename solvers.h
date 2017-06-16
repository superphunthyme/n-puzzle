#include "board.h"
#include "state.h"

void a_star_solve(board *b);
int ida_star_solve(board *b);
int search(board *node, int g, int bound, int *counter);
void free_states(int *key, state *value);
