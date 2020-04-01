#pragma once

#include "ast.hpp"
#include <memory>
#include <string>

struct ParseNode {
  std::shared_ptr<ASTNode> node;
  int num;
  std::string string;
};

#define YYSTYPE ParseNode
