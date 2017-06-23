#pragma once
#include <stdbool.h>
#include "board.h"

typedef void *T;

#define check_pointer(p)          \
  if (!p) {                     \
    printf("Out of memory."); \
    exit(EXIT_FAILURE);       \
  }

/**
 * An element of a linked list
 * */
typedef struct list_element {
  struct list_element *next;   ///< Pointer to next element in the list
  T value;                     ///< Value at node
} list_element;

/**
 * A linked list
 * */
typedef struct linked_list {
  list_element *head;   ///< Pointer to the head of the list
  int size;       ///< Length of list
} linked_list;

/**
 * @brief Initialize an empty list
 *
 * @return Pointer to created list
 */
linked_list *list_create();

/**
 * @brief Destory a a given list
 *
 * @param l Pointer to list to be destroyed
 *
 * @warning For now, one should remove all the elements, then free the list's
 * pointer, as the implementation has a bug
 */
void list_destroy(linked_list *l);

/**
 * @brief Add an element with value e to a list
 *
 * Add an item at the front of the list, taking constant time.
 *
 * @param e The item to add to the list @p l
 * @param l The list to which @p e is added
 */
void list_add(T e, linked_list *l);

/**
 * @brief Add an element with value e to the list at a specified position
 *
 * Add an item at position @p index (list indexing starts at 0), taking linear
 * time with respect to the index. Will not add the item if the index is out of
 * bounds.
 *
 * @param index The position that the item will occupy in the list
 * @param e The item to add to the list
 * @param l The list to which @p e is added
 */
void list_add_at(int index, T e, linked_list *l);

/**
 * @brief Remove an element from a list at a specified position
 *
 * Remove an item at position @p index (list indexing starts at 0), taking linear
 * time with respect to the index.
 *
 * @param index The position from which to remove an element
 * @param l The list from which the element is removed
 *
 * @note The item's value is destroyed as well. If additional allocation has
 * been for the element's value, then this must be manually managed.
 */
void list_remove(int index, linked_list *l);

/**
 * @brief Retrieve a value from a list at a specified position
 *
 * Retrieve an value of a list_element at position @p index (list indexing
 * starts at 0), taking linear time with respect to the index. Will not remove
 * the item if the index is out of bounds.
 *
 * @param index The position from which to find the element
 * @param l The list from which the element is retrieved
 */
T list_get(int index, linked_list *l);

/**
 * @brief Set a value from a list at a specified position
 *
 * Set an value of a list_element at position @p index (list indexing
 * starts at 0), taking linear time with respect to the index. Will not change
 * the item if the index is out of bounds.
 *
 * @param index The position from which to find the element
 * @param l The list from which the element is set
 *
 * @return The element at the given @p index
 */
void list_set(int index, T e, linked_list *l);

/**
 * @brief Check if a list contains a certain value
 *
 * Check that a list contains an element whose value is e.
 *
 * @param e The value to find in the list
 * @param l The list to search
 *
 * @return @c TRUE if list contains a list_element with value @p e else @c FALSE
   list contains a list_element with value @p e*
 * @warning The implementation must change according to T's type. For the
 * moment, the equality of board types is declared. The behaviour will be undefined
 * on other types.
 */
bool list_contains(T e, linked_list *l);

/**
 * @brief Check if a list is empty
 *
 * Check that a list is empty (has no list_elements)
 *
 * @param l The list to check
 *
 * @return @c TRUE if list is empty else @c FALSE
 */
bool list_is_empty(linked_list *l);
