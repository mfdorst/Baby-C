#include "linked_list.h"
#include <stddef.h>
#include <stdlib.h>

LLNode *make_node();

///
/// Appends an item to the linked list. O(1) time.
///
void list_append(LinkedList *list, void *elem) {
  if (list->head == NULL) {
    list->head = list->tail = make_node();
  } else {
    list->tail->next = make_node();
    list->tail = list->tail->next;
  }
  list->tail->data = elem;
}

///
/// Constructs an empty linked list.
///
LinkedList list_create(void (*destructor)(void *)) {
  LinkedList list;
  list.head = NULL;
  list.tail = NULL;
  list.destructor = destructor;
  return list;
}

///
/// Destroys (frees) a linked list, utilizing the provided destructor.
/// The container has no knowledge of the data it holds, and so must use the provided destructor
/// function to free the contents of the list. O(n) time.
///
void list_destroy(LinkedList *const list) {
  LLNode *node = list->head;
  while (node != NULL) {
    list->destructor(node->data);
    LLNode *next_node = node->next;
    free(node);
    node = next_node;
  }
  list->head = list->tail = NULL;
}

///
/// Finds an element that compares equal to the passed in element using the compare_eq function
/// pointer. Returns the element, or NULL if no such element is found.
///
void *list_find(const LinkedList *list, const void *elem,
                bool (*compare_eq)(const void *elem_in_list, const void *elem_to_find)) {
  LLNode *node;
  for (node = list->head; node != NULL; node = node->next) {
    if (compare_eq(node->data, elem)) {
      return node->data;
    }
  }
  return NULL;
}

///
/// Get the element at the tail of the list.
/// Returns NULL if the list is empty.
///
void *list_tail(const LinkedList *list) {
  if (list->tail) {
    return list->tail->data;
  }
  return NULL;
}

///
/// Constructs a new (empty) linked list node
///
LLNode *make_node() {
  LLNode *node = malloc(sizeof(LLNode));
  node->data = NULL;
  node->next = NULL;
  return node;
}
