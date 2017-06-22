/** @file */
#pragma once
#include <stdbool.h>
#include <stddef.h>
#include "linked-list.h"
/**
 * Size of the board
 */
#define DIM 4

typedef struct linked_list linked_list;

// Maybe make tiles variable length
/**
 * Structure to represent a board
 */
typedef struct board {
  int dim; ///< The width and height of the board.
  int tiles[DIM*DIM]; ///< The tiles of the board.
  int manhattan; ///< The value of the sum of the manhattan distances of the tiles.
  int zero_location; ///< The location of the zero (empty) tile.
} board;

/**
 * @brief Initialize a random board of dimensions size x size
 *
 * Creates a new board @p b of dimensions @p size x @p size with randomly shuffled tiles.
 * The board produced is always solvable.
 *
 * @param b Pointer to the board to be initialized
 * @param size The width and height of the board (not useful at the moment)
 *
 * @note For now, size must match the size specified at compile-time in the DIM
 * macro in board.h
 */
void init_board_random(board *b, int size);

/**
 * @brief Initizlize a board
 *
 * Creates a new board @p b of dimensions @p size x @p size with given @p
 * tiles.
 *
 * The board produced may not be valid/solvable if the tiles are incorrectly
 * set.
 *
 * @param b Pointer to the board to be initialized
 * @param size The width and height of the board (not useful at the moment)
 *
 * @note For now, size must match the size specified at compile-time in the DIM
 * macro in board.h
 */
void init_board(board *b, int tiles[], int size);

/**
 * @brief Check if board is in solved state
 *
 * @param b Pointer to a board
 *
 * @return @c TRUE if board is solved else @c FALSE
 */
bool is_solved(board *b);

/**
 * @brief Check if board can be solved
 *
 * @param b Pointer to a board
 *
 * @return @c TRUE if board is solvable else @c FALSE
 */
bool is_solvable(board *b);

/**
 * @brief Check if two boards are equal
 *
 * Check if the tiles from @p b1 and @p b2 match.
 *
 * @param b1 Pointer to a board to compare
 * @param b2 Pointer to a board to compare
 *
 * @return @c TRUE if boards have same tiles else @c FALSE
 * @note If the boards are an invalid state, may return true even though some
 * properties do not match.
 */
bool equals(board *b1, board *b2);

/**
 * @brief Swap tile with empty tile
 *
 * Swap the tile at @p location with the empty (0) tile, recalculating
 * heuristic and zero location.
 * 
 * The function assumes that the tile swapped is adjacent to the empty tile.
 *
 * @param b Pointer to a board
 * @param location Location of the tile to swap
 *
 * @return @c TRUE if boards have same tiles else @c FALSE
 */
void swap_zero(board *b, int location);

/**
 * @brief Retrieve neighbours of a given board
 *
 * Neighbours are the possible boards which can be obatined after one valid move
 * on @p b.
 *
 * @param b Pointer to a board
 * @param neighbours Pointer to a list which will store the neighbours
 */
void neighbours(board *b, linked_list *neighbours);

/**
 * @brief Print the board to the console
 *
 * @param b Pointer to a board
 */
void print_board(board *b);
