#include "ast.hpp"
#include <iostream>

std::shared_ptr<ASTNode> make_assign(std::shared_ptr<ASTNode> lhs, std::shared_ptr<ASTNode> rhs) {
  std::cout << "Creating Assignment node\n";
  auto node = std::make_shared<ASTNode>();
  node->right = std::move(rhs);
  node->left = std::move(lhs);
  return node;
}

std::shared_ptr<ASTNode> make_comparison(ASTCompOp op, std::shared_ptr<ASTNode> lhs,
                                         std::shared_ptr<ASTNode> rhs) {

  std::cout << "Creating " << (op == OP_OR ? "OR" : "Compare") << " node\n";
  auto node = std::make_shared<ASTNode>();
  node->comp_op = op;
  node->left = std::move(lhs);
  node->right = std::move(rhs);
  return node;
}

std::shared_ptr<ASTNode> make_num(int num) {
  std::cout << "Creating NUM node for " << num << '\n';
  auto node = std::make_shared<ASTNode>();
  node->type = AST_NUM;
  node->num = num;
  return node;
}

std::shared_ptr<ASTNode> make_ident(std::string name, bool left_hand) {
  std::cout << "Creating " << (left_hand ? "left-hand " : "") << "IDENT node for " << name << '\n';
  auto node = std::make_shared<ASTNode>();
  node->type = AST_NUM;
  node->name = std::move(name);
  return node;
}

std::shared_ptr<ASTNode> make_statement_list(std::shared_ptr<ASTNode> statement,
                                             std::shared_ptr<ASTNode> statement_list) {
  std::cout << "Adding a Statement to a Statement list \n";
  if (statement_list) {
    statement_list->next = statement;
    return statement_list;
  }
  return statement;
}

std::string op_to_str(ASTOp op);

std::shared_ptr<ASTNode> make_op(ASTOp op, std::shared_ptr<ASTNode> left_operand,
                                 std::shared_ptr<ASTNode> right_operand) {
  std::cout << "Creating " << op_to_str(op) << " node\n";
  auto node = std::make_shared<ASTNode>();
  node->op = op;
  node->left = std::move(left_operand);
  node->right = std::move(right_operand);
  return node;
}

std::shared_ptr<ASTNode> make_while(std::shared_ptr<ASTNode> condition,
                                    std::shared_ptr<ASTNode> statement_list) {
  std::cout << "Creating while loop node\n";
  auto node = std::make_shared<ASTNode>();
  node->condition = std::move(condition);
  node->while_block = std::move(statement_list);
  return node;
}

void add_declaration(const std::string &name) {
  std::cout << "Processing declaration of " << name << '\n';
}

std::string op_to_str(ASTOp op) {
  switch (op) {
  case OP_ADD:
    return "Addition";
  case OP_SUB:
    return "Subtraction";
  case OP_MULT:
    return "Multiplication";
  case OP_DIV:
    return "Division";
  }
}
