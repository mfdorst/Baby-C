#pragma once

#include "ast.hpp"
#include <memory>
#include <string>

struct ParseNode {
  ASTNodeRef node;
  int num;
  std::string string;
  ASTCompOp comp_op;
};

#define YYSTYPE ParseNode
