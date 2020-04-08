#include "ast.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

ASTNode *make_assignment(ASTNode *lhs, ASTNode *expr) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = ASTNODE_ASSIGN;
  node->left = lhs;
  node->right = expr;
  return node;
}

ASTNode *make_num(int num) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = ASTNODE_NUM;
  node->num = num;
  return node;
}

ASTNode *make_ident(char *name) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = ASTNODE_IDENT;
  node->name = name;
  return node;
}

ASTNode *make_statement_list(ASTNode *statement, ASTNode *statement_list) {
  if (statement_list != NULL) {
    statement_list->next = statement;
    return statement_list;
  } else {
    return statement;
  }
}

ASTNode *make_op(ASTOp operator, ASTNode *left_operand,
                 ASTNode *right_operand) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->op = operator;
  node->left = left_operand;
  node->right = right_operand;
  return node;
}

void add_declaration(char *name) {}
