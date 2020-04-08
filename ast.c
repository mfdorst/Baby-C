#include "ast.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void add_declaration(char *name) {}

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

ASTNode *make_ident(char *name) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_IDENT;
  node->data.ident = name;
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

ASTNode *make_num(int num) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = AST_NUM;
  node->data.num = num;
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
  node->data.while_loop.condition = condition;
  node->data.while_loop.code_block = code_block;
  return node;
}
