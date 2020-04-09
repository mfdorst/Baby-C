#include "symbol_table.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct LLNode LLNode;

struct LLNode {
  char *symbol;
  LLNode *next;
};

LLNode *g_head;
LLNode *g_tail;

LLNode *make_llnode(void);

void add_declaration(char *symbol) {
  if (g_head == NULL) {
    g_head = make_llnode();
    g_tail = g_head;
  } else {
    g_tail->next = make_llnode();
    g_tail = g_tail->next;
  }
  g_tail->symbol = symbol;
}

bool is_declared(char *symbol) {
  LLNode *node;
  for (node = g_head; node != NULL; node = node->next) {
    if (strcmp(symbol, node->symbol) == 0) {
      return true;
    }
  }
  return false;
}

LLNode *make_llnode(void) {
  LLNode * node = (LLNode *) malloc(sizeof(LLNode));
  node->symbol = NULL;
  node->next = NULL;
  return node;
}
