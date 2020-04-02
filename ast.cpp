#include "ast.hpp"
#include <iostream>

ASTNodeRef make_assign(ASTNodeRef lhs, ASTNodeRef rhs) {
  std::cout << "Creating Assignment node\n";
  auto node = std::make_shared<ASTNode>();
  node->right = std::move(rhs);
  node->left = std::move(lhs);
  return node;
}

ASTNodeRef make_comparison(ASTCompOp op, ASTNodeRef lhs, ASTNodeRef rhs) {
  std::cout << "Creating Compare node\n";
  auto node = std::make_shared<ASTNode>();
  node->comp_op = op;
  node->left = std::move(lhs);
  node->right = std::move(rhs);
  return node;
}

ASTNodeRef make_ident(std::string name, bool left_hand) {
  std::cout << "Creating " << (left_hand ? "left-hand " : "") << "IDENT node for " << name << '\n';
  auto node = std::make_shared<ASTNode>();
  node->type = AST_NUM;
  node->name = std::move(name);
  return node;
}

ASTNodeRef make_if(ASTNodeRef condition, ASTNodeRef if_block, ASTNodeRef else_block) {
  std::cout << "Creating if-else Statement node\n";
  auto node = std::make_shared<ASTNode>();
  node->condition = std::move(condition);
  node->if_block = std::move(if_block);
  node->else_block = std::move(else_block);
  return node;
}

ASTNodeRef make_if(ASTNodeRef condition, ASTNodeRef if_block) {
  std::cout << "Creating if Statement node\n";
  auto node = std::make_shared<ASTNode>();
  node->condition = std::move(condition);
  node->if_block = std::move(if_block);
  return node;
}

ASTNodeRef make_num(int num) {
  std::cout << "Creating NUM node for " << num << '\n';
  auto node = std::make_shared<ASTNode>();
  node->type = AST_NUM;
  node->num = num;
  return node;
}

ASTNodeRef make_logical_op(ASTLogicalOp op, ASTNodeRef lhs, ASTNodeRef rhs) {
  std::cout << "Creating " << (op == OP_AND ? "AND" : "OR") << " node\n";
  auto node = std::make_shared<ASTNode>();
  node->logical_op = op;
  node->left = std::move(lhs);
  node->right = std::move(rhs);
  return node;
}

std::string op_to_str(ASTOp op);

ASTNodeRef make_op(ASTOp op, ASTNodeRef left_operand, ASTNodeRef right_operand) {
  std::cout << "Creating " << op_to_str(op) << " node\n";
  auto node = std::make_shared<ASTNode>();
  node->op = op;
  node->left = std::move(left_operand);
  node->right = std::move(right_operand);
  return node;
}

ASTNodeRef make_statement_list(ASTNodeRef statement, ASTNodeRef statement_list) {
  std::cout << "Adding a Statement to a Statement list \n";
  if (statement_list) {
    statement_list->next = statement;
    return statement_list;
  }
  return statement;
}

ASTNodeRef make_while(ASTNodeRef condition, ASTNodeRef statement_list) {
  std::cout << "Creating while loop node\n";
  auto node = std::make_shared<ASTNode>();
  node->condition = std::move(condition);
  node->while_block = std::move(statement_list);
  return node;
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
