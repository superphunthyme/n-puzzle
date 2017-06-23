#pragma once
#include "board.h"

/** State during execution of A* solver*/
typedef struct state {
  board *current; ///< Current board position.
  struct state *previous; ///< Pointer to neighbouring state that preced this state.
  int moves; ///< Number of moves made to reach this state from initial state.
  int score; ///< A heuristic defined in init_board_state.
} state;


/**
 * @brief Initialize a board state
 *
 * Creates a new state @p s
 *
 * @param s Pointer to the state to be initialized
 * @param current Board associated with this state
 * @param prev Pointer to previous state
 * @param moves Number of moves made to reach this state from initial state.
 */
void init_board_state(state *s, board *current, state *prev, int moves);
