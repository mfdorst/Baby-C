#ifndef YOUR_CODE_H
#define YOUR_CODE_H

enum ASTNodeType {
  ASTNODE_ARITH_OP,
  ASTNODE_LOGIC_OP,
  ASTNODE_COMPARE,
  ASTNODE_ASSIGN,
  ASTNODE_IDENT,
  ASTNODE_NUM,
  ASTNODE_IF,
  ASTNODE_WHILE
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

ASTNode *CreateNumNode(int num);
ASTNode *CreateIdentNode(char *name);
ASTNode *CreateStatementListNode(ASTNode *st, ASTNode *stList);
ASTNode *make_op(ASTOp op, ASTNode *left_operand, ASTNode *right_operand);

void AddDeclaration(char *name);

#endif
