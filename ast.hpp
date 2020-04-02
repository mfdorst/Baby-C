#pragma once

#include <memory>
#include <string>

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

enum ASTCompOp { OP_LT, OP_GT, OP_GE, OP_LE, OP_EQ, OP_NE };

enum ASTLogicalOp { OP_AND, OP_OR };

struct ASTNode;

using ASTNodeRef = std::shared_ptr<ASTNode>;

struct ASTNode {
  ASTNodeType type;
  ASTOp op;
  ASTCompOp comp_op;
  ASTLogicalOp logical_op;
  int num;
  std::string name;
  ASTNodeRef left;
  ASTNodeRef right;
  ASTNodeRef next;
  ASTNodeRef condition;
  ASTNodeRef while_block;
  ASTNodeRef if_block;
  ASTNodeRef else_block;
};

extern ASTNodeRef g_ast_root;

ASTNodeRef make_assign(ASTNodeRef lhs, ASTNodeRef rhs);
ASTNodeRef make_comparison(ASTCompOp op, ASTNodeRef lhs, ASTNodeRef rhs);
ASTNodeRef make_ident(std::string name, bool left_hand);
ASTNodeRef make_if(ASTNodeRef condition, ASTNodeRef if_block, ASTNodeRef else_block = nullptr);
ASTNodeRef make_logical_op(ASTLogicalOp op, ASTNodeRef lhs, ASTNodeRef rhs);
ASTNodeRef make_num(int num);
ASTNodeRef make_op(ASTOp op, ASTNodeRef left_operand, ASTNodeRef right_operand);
ASTNodeRef make_statement_list(ASTNodeRef statement, ASTNodeRef statement_list);
ASTNodeRef make_while(ASTNodeRef condition, ASTNodeRef statement_list);

void add_declaration(const std::string &name);
