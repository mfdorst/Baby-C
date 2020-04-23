#pragma once

#include "util.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct {
  char *name;
  usize offset;
} Symbol;

void add_declaration(char *name);
bool is_declared(char *symbol);
Symbol *find_symbol(char *name);
void free_symbol_table();
