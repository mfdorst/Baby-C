#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  char *name;
  size_t offset;
} Symbol;

void add_declaration(char *name);
bool is_declared(char *symbol);
Symbol *find_symbol(char *name);
