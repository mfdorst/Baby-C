#pragma once

#include "ast.h"
#include "util.h"
#include <stdio.h>

u32 generate_iloc(FILE *out_file, ASTNode *ast);
