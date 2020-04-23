#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LLNode LLNode;

struct LLNode {
  Symbol symbol;
  LLNode *next;
};

LLNode *g_head;
LLNode *g_tail;
usize g_offset = 0;

LLNode *make_llnode(void);

void add_declaration(char *symbol) {
  if (g_head == NULL) {
    g_head = make_llnode();
    g_tail = g_head;
  } else {
    g_tail->next = make_llnode();
    g_tail = g_tail->next;
  }
  g_tail->symbol.name = symbol;
  g_tail->symbol.offset = g_offset;
  g_offset += 4;
}

bool is_declared(char *symbol) { return find_symbol(symbol) != NULL; }

Symbol *find_symbol(char *name) {
  LLNode *node;
  for (node = g_head; node != NULL; node = node->next) {
    if (strcmp(node->symbol.name, name) == 0) {
      return &node->symbol;
    }
  }
  return NULL;
}

void free_symbol_table() {
  LLNode *node = g_head;
  while (node != NULL) {
    LLNode *next = node->next;
    free(node->symbol.name);
    free(node);
    node = next;
  }
}

LLNode *make_llnode(void) {
  LLNode *node = (LLNode *)malloc(sizeof(LLNode));
  node->symbol.name = NULL;
  node->symbol.offset = 0;
  node->next = NULL;
  return node;
}
