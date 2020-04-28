#pragma once

#include "linked_list.h"
#include "util.h"

///
/// Codes for an ILOC instruction.
///
typedef enum { ILOC_ADD, ILOC_SUB, ILOC_MULT, ILOC_DIV, ILOC_LOADI } Mnemonic;

///
/// Holds a list of instructions that constitute a basic block.
///
typedef struct {
  LinkedList instructions;
} BasicBlock;

///
/// Holds a list of basic blocks that constitue a program.
///
typedef struct {
  LinkedList basic_blocks;
} Program;

///
/// Constructs a new program on the stack.
///
Program construct_program();

///
/// Destroys (frees) a program.
///
void destroy_program(Program *program);

///
/// Starts a new basic block.
///
void add_basic_block(Program *program);

///
/// Adds an instruction to the last basic block.
///
void add_instruction(Program *program, Mnemonic mnemonic, u32 src1, u32 src2, u32 dest);
