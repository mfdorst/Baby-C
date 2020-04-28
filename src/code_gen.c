#include "code_gen.h"
#include <stdlib.h>

Program g_program;
u32 g_next_reg = 1;
u32 g_next_label = 1;

char *mnemonic_to_str(Mnemonic mnemoic);

u32 generate_iloc(FILE *out_file, const ASTNode *const ast, Program *program) {
  if (ast->type == AST_ARITH_OP) {
    Mnemonic op;
    if (ast->data.arith_op.op == OP_ADD) {
      op = ILOC_ADD;
    }
    if (ast->data.arith_op.op == OP_SUB) {
      op = ILOC_SUB;
    }
    if (ast->data.arith_op.op == OP_MULT) {
      op = ILOC_MULT;
    }
    if (ast->data.arith_op.op == OP_DIV) {
      op = ILOC_DIV;
    }
    const u32 src1 = generate_iloc(out_file, ast->data.arith_op.lhs, program);
    const u32 src2 = generate_iloc(out_file, ast->data.arith_op.rhs, program);
    const u32 dest = g_next_reg++;
    add_instruction(program, op, src1, src2, dest);
    fprintf(out_file, "X\t%s r%u, r%u -> r%u\n", mnemonic_to_str(op), src1, src2, dest);
    return dest;
  }
  if (ast->type == AST_ASSIGN) {
    const u32 src = generate_iloc(out_file, ast->data.assign.rhs, program);
    const u32 offset = ast->data.assign.lhs->data.ident->offset;
    fprintf(out_file, "\tstoreAI r%u -> rarp, %u\n", src, offset);
  }
  if (ast->type == AST_COMP_OP) {
    char *op;
    if (ast->data.comp_op.op == OP_LT) {
      op = "cmp_LT";
    }
    if (ast->data.comp_op.op == OP_LE) {
      op = "cmp_LE";
    }
    if (ast->data.comp_op.op == OP_GT) {
      op = "cmp_GT";
    }
    if (ast->data.comp_op.op == OP_GE) {
      op = "cmp_GE";
    }
    if (ast->data.comp_op.op == OP_EQ) {
      op = "cmp_EQ";
    }
    if (ast->data.comp_op.op == OP_NE) {
      op = "cmp_NE";
    }
    const u32 src1 = generate_iloc(out_file, ast->data.comp_op.lhs, program);
    const u32 src2 = generate_iloc(out_file, ast->data.comp_op.rhs, program);
    const u32 dest = g_next_reg++;
    fprintf(out_file, "\t%s r%u, r%u -> r%u\n", op, src1, src2, dest);
    return dest;
  }
  if (ast->type == AST_IDENT) {
    const u32 offset = ast->data.ident->offset;
    const u32 dest = g_next_reg++;
    fprintf(out_file, "\tloadAI rarp, %u -> r%u\n", offset, dest);
    return dest;
  }
  if (ast->type == AST_IF) {
    const u32 label = g_next_label++;
    const u32 cond = generate_iloc(out_file, ast->data.if_stmt.condition, program);
    const bool has_else = ast->data.if_stmt.else_block != NULL;
    const char label_suffix = has_else ? 'E' : 'M';
    fprintf(out_file, "\tcbr r%u -> L%u_T, L%u_%c\n", cond, label, label, label_suffix);
    fprintf(out_file, "L%u_T:\n", label);
    generate_iloc(out_file, ast->data.if_stmt.if_block, program);
    if (has_else) {
      fprintf(out_file, "\tjumpi -> L%u_M\n", label);
      fprintf(out_file, "L%u_E:\n", label);
      generate_iloc(out_file, ast->data.if_stmt.else_block, program);
    }
    fprintf(out_file, "L%u_M:\n", label);
  }
  if (ast->type == AST_LOGIC_OP) {
    char *op;
    if (ast->data.logic_op.op == OP_AND) {
      op = "and";
    }
    if (ast->data.logic_op.op == OP_OR) {
      op = "or";
    }
    const u32 src1 = generate_iloc(out_file, ast->data.logic_op.lhs, program);
    const u32 src2 = generate_iloc(out_file, ast->data.logic_op.rhs, program);
    const u32 dest = g_next_reg++;
    fprintf(out_file, "\t%s r%u, r%u -> r%u\n", op, src1, src2, dest);
    return dest;
  }
  if (ast->type == AST_NUM) {
    const u32 dest = g_next_reg++;
    fprintf(out_file, "\tloadi %u -> r%u\n", ast->data.num, dest);
    return dest;
  }
  if (ast->type == AST_WHILE) {
    const u32 label = g_next_label++;
    fprintf(out_file, "L%u_C:\n", label);
    const u32 cond = generate_iloc(out_file, ast->data.while_loop.condition, program);
    fprintf(out_file, "\tcbr r%u -> L%u_B, L%u_O\n", cond, label, label);
    fprintf(out_file, "L%u_B:\n", label);
    generate_iloc(out_file, ast->data.while_loop.code_block, program);
    fprintf(out_file, "\tjumpi -> L%u_C\n", label);
    fprintf(out_file, "L%u_O:\n", label);
  }
  if (ast->next) {
    generate_iloc(out_file, ast->next, program);
  }
  return 0;
}

char *mnemonic_to_str(Mnemonic mnemonic) {
  switch (mnemonic) {
  case ILOC_ADD:
    return "add";
  case ILOC_SUB:
    return "sub";
  case ILOC_MULT:
    return "mult";
  case ILOC_DIV:
    return "div";
  case ILOC_LOADI:
    return "loadi";
  }
  fprintf(stderr, "ERROR: Unreachable state\n");
  exit(1);
}
