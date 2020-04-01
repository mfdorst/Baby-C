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

struct ASTNode {
  ASTNodeType type;
  ASTOp op;
  int num;
  std::string name;
  std::shared_ptr<ASTNode> left;
  std::shared_ptr<ASTNode> right;
  std::shared_ptr<ASTNode> next;
};

extern std::shared_ptr<ASTNode> g_ast_root;

std::shared_ptr<ASTNode> make_num(int num);
std::shared_ptr<ASTNode> make_ident(std::string name);
std::shared_ptr<ASTNode> make_statement_list(std::shared_ptr<ASTNode> statement,
                                             std::shared_ptr<ASTNode> statement_list);
std::shared_ptr<ASTNode> make_op(ASTOp op, std::shared_ptr<ASTNode> left_operand,
                                 std::shared_ptr<ASTNode> right_operand);

void add_declaration(std::string name);
