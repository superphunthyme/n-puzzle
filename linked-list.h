#pragma once
#include <stdbool.h>
#include "board.h"

typedef void* T;

#define check_pointer(p)          \
  if (!p) {                     \
    printf("Out of memory."); \
    exit(EXIT_FAILURE);       \
  }

typedef struct list_element {
  struct list_element *next;   /* Pointer to next element in the list */
  T value;                     /* Value at node */
} list_element;

typedef struct linked_list {
  list_element *head;   /* Pointer to the head of the list */
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
bool list_contains(T e, linked_list *l);
bool list_is_empty(linked_list *l);
