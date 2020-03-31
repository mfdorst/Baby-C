#include "ast.hpp"
#include "lexer.hpp"
#include "make_unique.h"
#include <fstream>
#include <iostream>
#include <memory>

std::unique_ptr<std::ifstream> g_lexer_input;
extern int yyparse();

// A global variable that holds a pointer to the AST root
ASTNode *gASTRoot;

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "ERROR: Invalid number of command-line arguments. Usage: bcc File_Name.bc\n";
    exit(1);
  }

  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  g_lexer_input = make_unique<std::ifstream>(argv[1]);

  // Parses the passed in file and stores the AST in g_ast_root
  yyparse();
}
