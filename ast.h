#ifndef YOUR_CODE_H
#define YOUR_CODE_H

typedef enum {
  ASTNODE_ARITH_OP,
  ASTNODE_LOGIC_OP,
  ASTNODE_COMPARE,
  ASTNODE_ASSIGN,
  ASTNODE_IDENT,
  ASTNODE_NUM,
  ASTNODE_IF,
  ASTNODE_WHILE
} ASTNodeType;

typedef enum { OP_ADD, OP_SUB, OP_MULT, OP_DIV } ASTOp;

typedef struct ASTNode ASTNode;
struct ASTNode {
  ASTNodeType type;
  ASTOp op;
  int num;
  char *name;
  ASTNode *left;
  ASTNode *right;

  // The following pointer is just a suggestion; you don't have to use it if you
  // have a better design.
  ASTNode *next; // a pointer used to link statement nodes together in a
                 // statement list

  // Depending on your implementation, you may need to add other fields to this
  // struct
};

// Add functions to make_ the different kinds of ASTs
// These functions are called by the code embedded in the grammar.
// Here are some samples:
ASTNode *make_num(int num);
ASTNode *make_ident(char *name);
ASTNode *make_statement_list(ASTNode *st, ASTNode *stList);
ASTNode *make_op(ASTOp operator, ASTNode *left_operand, ASTNode *right_operand);

// Need a function to add a declaration to your symbol table
void add_declaration(char *name);

// This is the function that generates ILOC code after the construction of the
// AST
// void GenerateILOC(ASTNode* node);
#endif
