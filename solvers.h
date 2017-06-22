#include "board.h"
#include "state.h"

/**
 * @brief A* solver
 *
 * Find the optimal number of moves to solve a board @p b, and print the
 * solution. Faster than IDA* but memory use is exponential to size of board.
 *
 * @param b Board to solve
 */
void a_star_solve(board *b);

/**
 * @brief IDA* solver
 *
 * Find the optimal number of moves to solve a board @p b, and print the
 * solution. Slower than A* but memory use is linear to size of board
 *
 * @param b Board to solve
 * 
 * @return 0 if solved
 * @return NOT_FOUND if recursive call to search returns __INT_MAX__
 */
int ida_star_solve(board *b);

/**
 * @brief Free states' memory from heap
 * 
 * @param key Used for iterating through heap keys
 * @param value Used for iterating through heap values
 */
void free_states(int *key, state *value);
