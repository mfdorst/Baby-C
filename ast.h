#pragma once

typedef enum {
  AST_ARITH_OP,
  AST_LOGIC_OP,
  AST_COMPARE,
  AST_ASSIGN,
  AST_IDENT,
  AST_NUM,
  AST_IF,
  AST_WHILE
} ASTNodeType;

typedef enum { OP_ADD, OP_SUB, OP_MULT, OP_DIV, OP_AND, OP_OR } ASTOp;

typedef struct ASTNode ASTNode;

struct ASTNode {
  ASTNodeType type;
  ASTOp op;
  int num;
  char *name;
  ASTNode *left;
  ASTNode *right;
  ASTNode *next;
};

void add_declaration(char *name);
ASTNode *make_op(ASTOp operator, ASTNode *left_operand, ASTNode *right_operand);
ASTNode *make_assignment(ASTNode *lhs, ASTNode *expr);
ASTNode *make_ident(char *name);
ASTNode *make_num(int num);
ASTNode *make_statement_list(ASTNode *statement, ASTNode *statement_list);
