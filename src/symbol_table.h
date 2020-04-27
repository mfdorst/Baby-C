#pragma once

#include "util.h"
#include <stdbool.h>

typedef struct {
  char *name;
  u32 offset;
} Symbol;

void add_declaration(char *name);
bool is_declared(char *symbol);
Symbol *find_symbol(char *name);
void free_symbol_table();
