#pragma once
#include <stdbool.h>

///
/// A linked list node.
///
typedef struct LLNode LLNode;
struct LLNode {
  void *data;
  LLNode *next;
};

///
/// A linked list.
///
typedef struct LinkedList LinkedList;
struct LinkedList {
  LLNode *head;
  LLNode *tail;
  void (*destructor)(void *);
};

///
/// Appends an item to the linked list. O(1) time.
///
void list_append(LinkedList *list, void *elem);

///
/// Constructs an empty linked list.
///
LinkedList list_create(void (*destructor)(void *));

///
/// Finds an element that compares equal to the passed in element using the compare_eq function
/// pointer. Returns the element, or NULL if no such element is found.
///
void *list_find(const LinkedList *list, const void *elem,
                bool (*compare_eq)(const void *elem_in_list, const void *elem_to_find));

///
/// Destroys (frees) a linked list, utilizing the provided destructor.
/// The container has no knowledge of the data it holds, and so must use the provided destructor
/// function to free the contents of the list. O(n) time.
///
void list_destroy(LinkedList *list);
