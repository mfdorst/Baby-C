#include "ast.h"
#include "basic_block.h"
#include "code_gen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *yyin;
extern int yyparse();

ASTNode *g_ast_root;

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("ERROR: Invalid number of command-line arguments. Usage: bcc file_name.bc\n");
    exit(1);
  }

  char *in_file_path = argv[1];
  usize in_file_path_len = strlen(in_file_path);
  // Check for the `.bc` extension
  if (in_file_path[in_file_path_len - 3] != '.' || in_file_path[in_file_path_len - 2] != 'b' ||
      in_file_path[in_file_path_len - 1] != 'c') {
    printf("ERROR: Invalid file extension. Expected a '.bc' extension.\n");
    exit(1);
  }

  yyin = fopen(in_file_path, "r");
  if (yyin == NULL) {
    printf("ERROR: Failed to open '%s'\n", in_file_path);
    exit(1);
  }

  yyparse();
  fclose(yyin);

  // Path of output file will be two characters longer, + 1 for NULL termination
  char *out_file_path = malloc(in_file_path_len + 3);
  memcpy(out_file_path, in_file_path, in_file_path_len - 2);
  strcpy(out_file_path + in_file_path_len - 2, "iloc");

  FILE *out_file = fopen(out_file_path, "w");
  if (out_file == NULL) {
    printf("ERROR: Failed to open '%s'\n", out_file_path);
    free(out_file_path);
    exit(1);
  }
  free(out_file_path);

#ifdef DEBUG
  print_ast(g_ast_root);
#endif

  Program program = construct_program();
  generate_iloc(out_file, g_ast_root, &program);

  destroy_program(&program);
  fclose(out_file);
  free_ast(g_ast_root);
  free_symbol_table();
}
