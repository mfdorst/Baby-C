#include "code_gen.h"

typedef enum { ILOC_LOADI, ILOC_STOREAI, ILOC_ADD } iloc_op_t;

u32 g_next_reg = 1;

u32 generate_iloc(FILE *out_file, const ASTNode *const ast) {
  if (ast->type == AST_ARITH_OP) {
    char *op;
    if (ast->data.arith_op.op == OP_ADD) {
      op = "add";
    }
    if (ast->data.arith_op.op == OP_SUB) {
      op = "sub";
    }
    if (ast->data.arith_op.op == OP_MULT) {
      op = "mult";
    }
    if (ast->data.arith_op.op == OP_DIV) {
      op = "div";
    }
    const u32 src1 = generate_iloc(out_file, ast->data.arith_op.lhs);
    const u32 src2 = generate_iloc(out_file, ast->data.arith_op.rhs);
    const u32 dest = g_next_reg++;
    fprintf(out_file, "\t%s r%u, r%u -> r%u\n", op, src1, src2, dest);
    return dest;
  }
  if (ast->type == AST_ASSIGN) {
    u32 src = generate_iloc(out_file, ast->data.assign.rhs);
    u32 offset = ast->data.assign.lhs->data.ident->offset;
    fprintf(out_file, "\tstoreAI r%u -> rarp, %u\n", src, offset);
  }
  if (ast->type == AST_IDENT) {
    const u32 offset = ast->data.ident->offset;
    const u32 dest = g_next_reg++;
    fprintf(out_file, "\tloadAI rarp, %u -> r%u\n", offset, dest);
    return dest;
  }
  if (ast->type == AST_NUM) {
    const u32 dest = g_next_reg++;
    fprintf(out_file, "\tloadi %u -> r%u\n", ast->data.num, dest);
    return dest;
  }
  if (ast->next) {
    generate_iloc(out_file, ast->next);
  }
  return 0;
}
