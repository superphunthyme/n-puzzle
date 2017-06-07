#include "linked-list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

linked_list* list_create() {
    linked_list* l = malloc(sizeof(linked_list));
    check_pointer(l);
    l->head = NULL;
    l->size = 0;
    return l;
}

list_element* init_list_element(T e) {
    list_element* elem = malloc(sizeof(list_element));
    check_pointer(elem);
    elem->next = NULL;
    // Needs to be default type for T
    elem->value = e;
    /* What to do with e -> next? */
    return elem;
}

void list_destroy(linked_list* l) {
    struct list_element* head = l->head;
    struct list_element* p;
    while ((p = head) != NULL) {
        head = head->next;
        // Only if value is a pointer
        free(p->value);
        free(p);
    }
    free(l);
}

// Add at front for constant time addition
void list_add(T e, linked_list* l) {
    list_element* elem = init_list_element(e);
    struct list_element* n = l->head;
    l->head = elem;
    elem->next = n;
    l->size++;
}

void list_add_at(int index, T e, linked_list* l) {
    if (index > l->size || index < 0) {
        printf("Element must be placed between 0 and the size of the list\n");
        return;
    }
    l->size++;
    list_element* elem = init_list_element(e);
    if (index == 0) {
        struct list_element* n = l->head;
        l->head = elem;
        elem->next = n;
    } else {
        struct list_element* p = l->head;
        for (int i = 0; i < index - 1; i++) {
            p = p->next;
        }
        elem->next = p->next;
        p->next = elem;
    }
}

void list_remove(int index, linked_list* l) {
    if (index > l->size - 1 || index < 0) {
        printf("List does not have an element here\n");
        return;
    }
    if (list_is_empty(l)) {
        printf("Cannot remove from empty list\n");
        return;
    }
    l->size--;
    if ((index == 0) && (l->head->next == NULL)) {
        // Only if value is a pointer
        free(l->head->value);
        free(l->head);
    } else if (index == 0) {
        struct list_element* n = l->head;
        l->head = l->head->next;
        // Only if value is a pointer
        free(n->value);
        free(n);
    } else {
        struct list_element* p = l->head;
        for (int i = 0; i < index - 1; i++) {
            p = p->next;
        }
        struct list_element* n = p->next;
        p->next = p->next->next;
        // Only if value is a pointer
        free(n->value);
        free(n);
    }
}

T list_get(int index, linked_list* l) {
    if (index > l->size - 1 || index < 0) {
        printf("List does not have an element here\n");
    }
    struct list_element* p = l->head;
    for (int i = 0; i < index; i++) {
        p = p->next;
    }
    return p->value;
}

void list_set(int index, T e, linked_list* l) {
        if (index > l->size - 1 || index < 0) {
            printf("List does not have an element here\n");
            return;
        }
        if (list_is_empty(l)) {
            printf("Cannot remove from empty list\n");
            return;
        }
        struct list_element* p = l->head;
        for (int i = 0; i < index; i++) {
            p = p->next;
        }
        // Will not work for char* unless values are dynamically allocated!!!
        p->value = e;
}

bool list_contains(T e, linked_list* l) {
    bool found = false;
    struct list_element* p = l->head;
    while (p != NULL) {
        // This works for for char*, not any type!!!
        // Assume value cannot be NULL
        if (equals(e, p->value)) {
            found = true;
            break;
        }
        p = p->next;
    }
    return found;
}
bool list_is_empty(linked_list* l) {
    //return (l->head == NULL);
    return l->size == 0;
}
