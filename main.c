#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
extern int yyparse();

ASTNode *g_ast_root;

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("ERROR: Invalid number of command-line arguments. Usage: bcc "
           "File_Name.bc\n");
    exit(1);
  }
  yyin = fopen(argv[1], "r");
  if (yyin == NULL) {
    printf("ERROR: Failed to open the input file\n");
    exit(1);
  }

  yyparse();
  fclose(yyin);
}
