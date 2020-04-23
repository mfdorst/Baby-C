#include "code_gen.h"

unsigned g_next_reg = 1;

typedef enum {
  ILOC_LOADI,
  ILOC_STOREAI
} iloc_op_t;

void emit(FILE* out_file, iloc_op_t op, u32 src, u32 dest);

u32 generate_iloc(FILE *out_file, ASTNode *ast) {
  if (ast->type == AST_NUM) {
    u32 dest_reg = g_next_reg++;
    emit(out_file, ILOC_LOADI, ast->data.num, dest_reg);
    return dest_reg;
  }
  if (ast->type == AST_ASSIGN) {
    u32 src_reg = generate_iloc(out_file, ast->data.assign.rhs);
    u32 offset = ast->data.assign.lhs->data.ident->offset;
    emit(out_file, ILOC_STOREAI, src_reg, offset);
  }
  
}

void emit(FILE* out_file, iloc_op_t op, u32 src, u32 dest) {
  if (op == ILOC_LOADI) {
    fprintf(out_file, "loadi %u -> r%u", src, dest);
    return;
  }
  if (op == ILOC_STOREAI) {
    fprintf(out_file, "storeAI r%u -> arp, %u", src, dest);
    return;
  }
}
