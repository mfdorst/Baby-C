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

struct ASTNode {
  ASTNodeType type;
  ASTOp op;
  ASTCompOp comp_op;
  ASTLogicalOp logical_op;
  int num;
  std::string name;
  std::shared_ptr<ASTNode> left;
  std::shared_ptr<ASTNode> right;
  std::shared_ptr<ASTNode> next;
  std::shared_ptr<ASTNode> condition;
  std::shared_ptr<ASTNode> while_block;
  std::shared_ptr<ASTNode> if_block;
  std::shared_ptr<ASTNode> else_block;
};

extern std::shared_ptr<ASTNode> g_ast_root;

std::shared_ptr<ASTNode> make_assign(std::shared_ptr<ASTNode> lhs, std::shared_ptr<ASTNode> rhs);
std::shared_ptr<ASTNode> make_comparison(ASTCompOp op, std::shared_ptr<ASTNode> lhs,
                                         std::shared_ptr<ASTNode> rhs);
std::shared_ptr<ASTNode> make_ident(std::string name, bool left_hand);
std::shared_ptr<ASTNode> make_if(std::shared_ptr<ASTNode> condition,
                                 std::shared_ptr<ASTNode> if_block,
                                 std::shared_ptr<ASTNode> else_block = nullptr);
std::shared_ptr<ASTNode> make_logical_op(ASTLogicalOp op, std::shared_ptr<ASTNode> lhs,
                                         std::shared_ptr<ASTNode> rhs);
std::shared_ptr<ASTNode> make_num(int num);
std::shared_ptr<ASTNode> make_op(ASTOp op, std::shared_ptr<ASTNode> left_operand,
                                 std::shared_ptr<ASTNode> right_operand);
std::shared_ptr<ASTNode> make_statement_list(std::shared_ptr<ASTNode> statement,
                                             std::shared_ptr<ASTNode> statement_list);
std::shared_ptr<ASTNode> make_while(std::shared_ptr<ASTNode> condition,
                                    std::shared_ptr<ASTNode> statement_list);

void add_declaration(const std::string &name);
