#include "basic_block.h"
#include <stdlib.h>

///
/// Codes for a complete machine instruction, including the ILOC instruction, and source and
/// destination values.
///
typedef struct {
  Mnemonic mnemonic;
  u32 src1;
  u32 src2;
  u32 dest;
} Instruction;

void destroy_basic_block(void *basic_block);
void destroy_instruction(void *instruction);
BasicBlock *make_basic_block();
Instruction *make_instr(Mnemonic mnemonic, u32 src1, u32 src2, u32 dest);

///
/// Starts a new basic block.
///
void add_basic_block(Program *program) { list_append(&program->basic_blocks, make_basic_block()); }

///
/// Adds an instruction to the last basic block.
///
void add_instruction(Program *program, Mnemonic mnemonic, u32 src1, u32 src2, u32 dest) {
  BasicBlock *last_block = (BasicBlock *)list_tail(&program->basic_blocks);
  list_append(&last_block->instructions, make_instr(mnemonic, src1, src2, dest));
}

///
/// Constructs a new program on the stack.
///
Program construct_program() {
  Program program;
  program.basic_blocks = list_create(destroy_basic_block);
  list_append(&program.basic_blocks, make_basic_block());
  return program;
}

///
/// Destroys (frees) a basic block.
///
void destroy_basic_block(void *basic_block) {
  list_destroy(&((BasicBlock *)basic_block)->instructions);
  free(basic_block);
}

///
/// Destroys (frees) an instruction.
///
void destroy_instruction(void *instruction) { free(instruction); }

///
/// Destroys (frees) a program.
///
void destroy_program(Program *program) { list_destroy(&program->basic_blocks); }

///
/// Allocates and constructs a new instruction on the heap. Freed by the caller.
///
Instruction *make_instr(Mnemonic mnemonic, u32 src1, u32 src2, u32 dest) {
  Instruction *instruction = malloc(sizeof(Instruction));
  instruction->mnemonic = mnemonic;
  instruction->src1 = src1;
  instruction->src2 = src2;
  instruction->dest = dest;
  return instruction;
}

///
/// Allocates and constructs a new basic block on the heap. Freed by the caller using
/// destroy_basic_block().
///
BasicBlock *make_basic_block() {
  BasicBlock *basic_block = malloc(sizeof(BasicBlock));
  basic_block->instructions = list_create(destroy_instruction);
  return basic_block;
}
