#include "ast.hpp"

// Write the implementations of the functions that do the real work here

std::shared_ptr<ASTNode> make_num(int num) {
  auto node = std::make_shared<ASTNode>();
  node->type = AST_NUM;
  node->num = num;
  return node;
}

std::shared_ptr<ASTNode> make_ident(std::string name) {
  auto node = std::make_shared<ASTNode>();
  node->type = AST_NUM;
  node->name = std::move(name);
  return node;
}

std::shared_ptr<ASTNode> make_statement_list(std::shared_ptr<ASTNode> statement,
                                             std::shared_ptr<ASTNode> statement_list) {
  if (statement_list) {
    statement_list->next = statement;
    return statement_list;
  }
  return statement;
}

std::shared_ptr<ASTNode> make_op(ASTOp op, std::shared_ptr<ASTNode> left_operand,
                                 std::shared_ptr<ASTNode> right_operand) {
  auto node = std::make_shared<ASTNode>();
  node->op = op;
  node->left = std::move(left_operand);
  node->right = std::move(right_operand);
  return node;
}

void add_declaration(std::string name) {}
