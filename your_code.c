#include "your_code.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Write the implementations of the functions that do the real work here

ASTNode *CreateNumNode(int num) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = ASTNODE_NUM;
  node->num = num;
  return node;
}

ASTNode *CreateIdentNode(char *name) {
  ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
  node->type = ASTNODE_NUM;
  node->name = name;
  return node;
}

// Take a statement node and a statement list node and connect them together
// to form a bigger statement list node (add the statement to the statement
// list). Return a pointer to the bigger list that resulted from this linking
ASTNode *CreateStatementListNode(ASTNode *statement, ASTNode *statement_list) {
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

void AddDeclaration(char *name) {}

// Commented out in this assignment
/*void GenerateILOC(ASTNode* node);
{

}*/
