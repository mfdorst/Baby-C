#ifndef YOUR_CODE_H
#define YOUR_CODE_H

enum ASTNodeType {
  AST_ARITH_OP,
  AST_LOGIC_OP,
  AST_COMPARE,
  AST_ASSIGN,
  AST_IDENT,
  AST_NUM,
  AST_IF,
  AST_WHILE
};

enum ASTOp { OP_ADD, OP_SUB, OP_MULT, OP_DIV };

struct ASTNode {
  ASTNodeType type;
  ASTOp op;
  int num;
  char *name;
  ASTNode *left;
  ASTNode *right;
  ASTNode *next;
};

extern ASTNode *g_ast_root;

ASTNode *make_num(int num);
ASTNode *make_ident(char *name);
ASTNode *make_statement_list(ASTNode *st, ASTNode *stList);
ASTNode *make_op(ASTOp op, ASTNode *left_operand, ASTNode *right_operand);

void AddDeclaration(char *name);

#endif
