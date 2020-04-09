#pragma once

#include "symbol_table.h"

typedef enum {
  AST_ARITH_OP,
  AST_LOGIC_OP,
  AST_COMP_OP,
  AST_ASSIGN,
  AST_IDENT,
  AST_NUM,
  AST_IF,
  AST_WHILE
} ASTNodeType;

typedef enum { OP_ADD, OP_SUB, OP_MULT, OP_DIV } ASTArithOp;

typedef enum { OP_AND, OP_OR } ASTLogicOp;

typedef enum { OP_LT, OP_GT, OP_LE, OP_GE, OP_EQ, OP_NE } ASTCompOp;

typedef struct ASTNode ASTNode;

typedef struct {
  ASTArithOp op;
  ASTNode *lhs;
  ASTNode *rhs;
} ASTArithOpNode;

typedef struct {
  ASTNode *lhs;
  ASTNode *rhs;
} ASTAssignNode;

typedef struct {
  ASTCompOp op;
  ASTNode *lhs;
  ASTNode *rhs;
} ASTCompOpNode;

typedef struct {
  ASTNode *condition;
  ASTNode *if_block;
  ASTNode *else_block;
} ASTIfNode;

typedef struct {
  ASTLogicOp op;
  ASTNode *lhs;
  ASTNode *rhs;
} ASTLogicOpNode;

typedef struct {
  ASTNode *condition;
  ASTNode *code_block;
} ASTWhileNode;

typedef union {
  ASTArithOpNode arith_op;
  ASTLogicOpNode logic_op;
  ASTCompOpNode comp_op;
  ASTAssignNode assign;
  ASTIfNode if_stmt;
  ASTWhileNode while_loop;
  Symbol *ident;
  int num;
} ASTNodeData;

struct ASTNode {
  ASTNodeType type;
  ASTNodeData data;
  ASTNode *next;
};

void free_ast(ASTNode *node);
ASTNode *make_arith_op(ASTArithOp operator, ASTNode *left_operand, ASTNode *right_operand);
ASTNode *make_assignment(ASTNode *lhs, ASTNode *expr);
ASTNode *make_comp_op(ASTCompOp operator, ASTNode *left_operand, ASTNode *right_operand);
ASTNode *make_ident(Symbol *symbol);
ASTNode *make_if(ASTNode *condition, ASTNode *if_block, ASTNode *else_block);
ASTNode *make_logic_op(ASTLogicOp operator, ASTNode *left_operand, ASTNode *right_operand);
ASTNode *make_num(int num);
ASTNode *make_statement_list(ASTNode *statement, ASTNode *statement_list);
ASTNode *make_while_loop(ASTNode *condition, ASTNode *code_block);
