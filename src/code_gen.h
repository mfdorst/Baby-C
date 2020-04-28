#pragma once

#include "ast.h"
#include "basic_block.h"
#include "util.h"
#include <stdio.h>

u32 generate_iloc(FILE *out_file, const ASTNode *const ast, Program *program);
