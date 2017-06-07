#pragma once
#include <stdbool.h>
#include "board.h"
// typedef int T;
typedef struct board* T;

#define check_pointer(p)          \
  if (!p) {                     \
    printf("Out of memory."); \
    exit(EXIT_FAILURE);       \
  }

#define MINIMUM_SIZE 1
/* Minimal stack size (expressed in number of elements) for which *  space is allocated. It should be at least 1. */ #define GROWTH_FACTOR 2
/* How much more memory is allocated each time a stack grows
 *  out of its allocated segment. */

typedef struct list_element {
  struct list_element *next;   /* Pointer to next element in the list */
  T value;                     /* Value at node */
} list_element;

typedef struct {
  list_element *head;   /* Pointer to the head of the list */
  // list_element* allocated_head; /* Pointer to beggining of space allocated
  // to the list */
  int size;       /* Length of list */
} linked_list;

linked_list *list_create();
list_element *init_list_element();
void list_destroy(linked_list *l);
void list_add(T e, linked_list *l);
void list_add_at(int index, T e, linked_list *l);
void list_remove(int index, linked_list *l);
T list_get(int index, linked_list *l);
void list_set(int index, T e, linked_list *l);
/* In terms of value or exact object? */
bool list_contains(T e, linked_list *l);
bool list_is_empty(linked_list *l);
