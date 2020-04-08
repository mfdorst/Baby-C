#include "ast.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void add_declaration(char *name) {}

ASTNode *make_arith_op(ASTArithOp operator, ASTNode *left_operand, ASTNode *right_operand) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_ARITH_OP;
  node->arith_op = operator;
  node->left = left_operand;
  node->right = right_operand;
  return node;
}

ASTNode *make_assignment(ASTNode *lhs, ASTNode *expr) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_ASSIGN;
  node->left = lhs;
  node->right = expr;
  return node;
}

ASTNode *make_comp_op(ASTCompOp operator, ASTNode *left_operand, ASTNode *right_operand) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_COMP_OP;
  node->comp_op = operator;
  node->left = left_operand;
  node->right = right_operand;
  return node;
}

ASTNode *make_ident(char *name) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_IDENT;
  node->name = name;
  return node;
}

ASTNode *make_if(ASTNode *condition, ASTNode *if_block, ASTNode *else_block) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_IF;
  node->conditon = condition;
  node->code_block = if_block;
  node->else_block = else_block;
  return node;
}

ASTNode *make_logic_op(ASTLogicOp operator, ASTNode *left_operand, ASTNode *right_operand) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_LOGIC_OP;
  node->logic_op = operator;
  node->left = left_operand;
  node->right = right_operand;
  return node;
}

ASTNode *make_num(int num) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_NUM;
  node->num = num;
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

ASTNode *make_while_loop(ASTNode *condition, ASTNode *code_block) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_WHILE;
  node->conditon = condition;
  node->code_block = code_block;
  return node;
}
