#pragma once

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

struct ASTNode {
  ASTNodeType type;
  ASTArithOp arith_op;
  ASTLogicOp logic_op;
  ASTCompOp comp_op;
  int num;
  char *name;
  ASTNode *left;
  ASTNode *right;
  ASTNode *next;
  ASTNode *conditon;
  ASTNode *code_block;
};

void add_declaration(char *name);
ASTNode *make_arith_op(ASTArithOp operator, ASTNode *left_operand, ASTNode *right_operand);
ASTNode *make_assignment(ASTNode *lhs, ASTNode *expr);
ASTNode *make_comp_op(ASTCompOp operator, ASTNode *left_operand, ASTNode *right_operand);
ASTNode *make_ident(char *name);
ASTNode *make_logic_op(ASTLogicOp operator, ASTNode *left_operand, ASTNode *right_operand);
ASTNode *make_num(int num);
ASTNode *make_statement_list(ASTNode *statement, ASTNode *statement_list);
ASTNode *make_while_loop(ASTNode *condition, ASTNode *code_block);
