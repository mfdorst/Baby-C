#include "symbol_table.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkedList *g_symbol_table = NULL;
usize g_offset = 0;

void symbol_destructor(void *symbol);
Symbol *make_symbol(char *name, u32 offset);
LinkedList *make_symbol_table();
bool symbol_has_name(const void *symbol, const void *name);

void add_declaration(char *symbol) {
  if (g_symbol_table == NULL) {
    g_symbol_table = make_symbol_table();
  }
  list_append(g_symbol_table, make_symbol(symbol, g_offset));
  g_offset += 4;
}

bool is_declared(char *symbol) { return find_symbol(symbol) != NULL; }

Symbol *find_symbol(char *name) {
  if (g_symbol_table == NULL) {
    g_symbol_table = make_symbol_table();
  }
  return list_find(g_symbol_table, name, symbol_has_name);
}

void free_symbol_table() {
  list_destroy(g_symbol_table);
  free(g_symbol_table);
}

Symbol *make_symbol(char *name, u32 offset) {
  Symbol *symbol = malloc(sizeof(Symbol));
  symbol->name = name;
  symbol->offset = offset;
  return symbol;
}

LinkedList *make_symbol_table() {
  LinkedList *symbol_table = malloc(sizeof(LinkedList));
  *symbol_table = list_create(symbol_destructor);
  return symbol_table;
}

void symbol_destructor(void *symbol) { free(symbol); }

bool symbol_has_name(const void *symbol, const void *name) {
  return strcmp(((Symbol *)symbol)->name, name) == 0;
}
