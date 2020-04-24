#include "ast.h"
#include <assert.h>
#include <stdlib.h>

#ifdef DEBUG
#include "util.h"
#include <stdio.h>
#include <string.h>

char *ast_node_to_str(const ASTNode *const node);
void print_ast(const ASTNode *const ast);
void print_ast_impl(const ASTNode *const ast, const char *const current_prefix,
                    const char *const next_prefix, const bool last);
#endif

void free_ast(ASTNode *node) {
  if (node == NULL)
    return;
  switch (node->type) {
  case AST_ARITH_OP:
    free_ast(node->data.arith_op.lhs);
    free_ast(node->data.arith_op.rhs);
    break;
  case AST_ASSIGN:
    free_ast(node->data.assign.lhs);
    free_ast(node->data.assign.rhs);
    break;
  case AST_COMP_OP:
    free_ast(node->data.comp_op.lhs);
    free_ast(node->data.comp_op.rhs);
    break;
  case AST_IDENT:
    break;
  case AST_IF:
    free_ast(node->data.if_stmt.condition);
    free_ast(node->data.if_stmt.if_block);
    free_ast(node->data.if_stmt.else_block);
    break;
  case AST_LOGIC_OP:
    free_ast(node->data.logic_op.lhs);
    free_ast(node->data.logic_op.rhs);
    break;
  case AST_NUM:
    break;
  case AST_WHILE:
    free_ast(node->data.while_loop.condition);
    free_ast(node->data.while_loop.code_block);
  }
  free(node);
}

ASTNode *make_arith_op(ASTArithOp operator, ASTNode *left_operand, ASTNode *right_operand) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_ARITH_OP;
  node->data.arith_op.op = operator;
  node->data.arith_op.lhs = left_operand;
  node->data.arith_op.rhs = right_operand;
  return node;
}

ASTNode *make_assignment(ASTNode *lhs, ASTNode *expr) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_ASSIGN;
  node->data.assign.lhs = lhs;
  node->data.assign.rhs = expr;
  return node;
}

ASTNode *make_comp_op(ASTCompOp operator, ASTNode *left_operand, ASTNode *right_operand) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_COMP_OP;
  node->data.comp_op.op = operator;
  node->data.comp_op.lhs = left_operand;
  node->data.comp_op.rhs = right_operand;
  return node;
}

ASTNode *make_ident(Symbol *symbol) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_IDENT;
  node->data.ident = symbol;
  return node;
}

ASTNode *make_if(ASTNode *condition, ASTNode *if_block, ASTNode *else_block) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_IF;
  node->data.if_stmt.condition = condition;
  node->data.if_stmt.if_block = if_block;
  node->data.if_stmt.else_block = else_block;
  return node;
}

ASTNode *make_logic_op(ASTLogicOp operator, ASTNode *left_operand, ASTNode *right_operand) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_LOGIC_OP;
  node->data.logic_op.op = operator;
  node->data.logic_op.lhs = left_operand;
  node->data.logic_op.rhs = right_operand;
  return node;
}

ASTNode *make_num(i32 num) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_NUM;
  node->data.num = num;
  return node;
}

ASTNode *prepend_statement(ASTNode *statement, ASTNode *statement_list) {
  statement->next = statement_list;
  return statement;
}

ASTNode *make_while_loop(ASTNode *condition, ASTNode *code_block) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_WHILE;
  node->data.while_loop.condition = condition;
  node->data.while_loop.code_block = code_block;
  return node;
}

#ifdef DEBUG
char *ast_node_to_str(const ASTNode *const node) {
  if (node->type == AST_ARITH_OP) {
    if (node->data.arith_op.op == OP_ADD) {
      return strdup("+");
    }
    if (node->data.arith_op.op == OP_SUB) {
      return strdup("-");
    }
    if (node->data.arith_op.op == OP_MULT) {
      return strdup("*");
    }
    if (node->data.arith_op.op == OP_DIV) {
      return strdup("/");
    }
  }
  if (node->type == AST_ASSIGN) {
    return strdup("=");
  }
  if (node->type == AST_COMP_OP) {
    if (node->data.comp_op.op == OP_LT) {
      return strdup("<");
    }
    if (node->data.comp_op.op == OP_GT) {
      return strdup(">");
    }
    if (node->data.comp_op.op == OP_LE) {
      return strdup("<=");
    }
    if (node->data.comp_op.op == OP_GE) {
      return strdup(">=");
    }
    if (node->data.comp_op.op == OP_EQ) {
      return strdup("==");
    }
    if (node->data.comp_op.op == OP_NE) {
      return strdup("!=");
    }
  }
  if (node->type == AST_IDENT) {
    return strdup(node->data.ident->name);
  }
  if (node->type == AST_IF) {
    return strdup("if");
  }
  if (node->type == AST_LOGIC_OP) {
    if (node->data.logic_op.op == OP_AND) {
      return strdup("&&");
    }
    if (node->data.logic_op.op == OP_OR) {
      return strdup("||");
    }
  }
  if (node->type == AST_NUM) {

    return i32_to_str(node->data.num);
  }
  if (node->type == AST_WHILE) {
    return strdup("while");
  }
  printf("[DEBUG] ERROR: Unreachable code\n");
  exit(1);
}

void print_ast(const ASTNode *const ast) {
  if (!ast->next) {
    print_ast_impl(ast, "", "   ", true);
    return;
  }
  print_ast_impl(ast, "", "│  ", false);
  print_ast(ast->next);
}

void print_ast_impl(const ASTNode *const ast, const char *const current_prefix,
                    const char *const next_prefix, const bool last) {
  const char *branch_symbol = last ? "└-" : "├-";
  char *node_str = ast_node_to_str(ast);
  printf("%s%s %s\n", current_prefix, branch_symbol, node_str);
  free(node_str);

  char *last_prefix = malloc(strlen(next_prefix) + 4);
  char *not_last_prefix = malloc(strlen(next_prefix) + 4);
  sprintf(last_prefix, "%s   ", next_prefix);
  sprintf(not_last_prefix, "%s│  ", next_prefix);

  if (ast->type == AST_ARITH_OP) {
    print_ast_impl(ast->data.arith_op.lhs, next_prefix, not_last_prefix, false);
    print_ast_impl(ast->data.arith_op.rhs, next_prefix, last_prefix, true);
  }
  if (ast->type == AST_ASSIGN) {
    print_ast_impl(ast->data.assign.lhs, next_prefix, not_last_prefix, false);
    print_ast_impl(ast->data.assign.rhs, next_prefix, last_prefix, true);
  }
  if (ast->type == AST_COMP_OP) {
    print_ast_impl(ast->data.comp_op.lhs, next_prefix, not_last_prefix, false);
    print_ast_impl(ast->data.comp_op.rhs, next_prefix, last_prefix, true);
  }
  if (ast->type == AST_IF) {
    print_ast_impl(ast->data.if_stmt.condition, next_prefix, not_last_prefix, false);
    const bool has_else = ast->data.if_stmt.else_block != NULL;
    const char *prefix = has_else ? not_last_prefix : last_prefix;
    print_ast_impl(ast->data.if_stmt.if_block, next_prefix, prefix, !has_else);
    if (has_else) {
      print_ast_impl(ast->data.if_stmt.else_block, next_prefix, last_prefix, true);
    }
  }
  if (ast->type == AST_LOGIC_OP) {
    print_ast_impl(ast->data.logic_op.lhs, next_prefix, not_last_prefix, false);
    print_ast_impl(ast->data.logic_op.rhs, next_prefix, last_prefix, true);
  }
  if (ast->type == AST_WHILE) {
    print_ast_impl(ast->data.while_loop.condition, next_prefix, not_last_prefix, false);
    ASTNode *statement = ast->data.while_loop.code_block;
    while (statement != NULL) {
      bool has_next = statement->next != NULL;
      const char *prefix = has_next ? not_last_prefix : last_prefix;
      print_ast_impl(statement, next_prefix, prefix, !has_next);
      statement = statement->next;
    }
  }
  free(not_last_prefix);
  free(last_prefix);
}
#endif
