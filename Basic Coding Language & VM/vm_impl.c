#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <error.h>

#include "vm.h"

// registers
static uint32_t reg[NUM_REGS];
#define FP reg[12]
#define SP reg[13]
#define LN reg[14]
#define IP reg[15]

// memory
static uint32_t mem[MEM_SIZE];

// flags
static bool z;
static bool n;

void print_state(FILE *fp);

int vm(FILE *vmin, FILE *vmout, FILE *vmtrace) {
  // initialize flags
  z = 0;
  n = 0;

  // initialize mem
  for (int i = 0; i < MEM_SIZE; i++) {
    mem[i] = 0;
  }

  // initialize register file
  for (int i = 0; i < NUM_REGS; i++) {
    reg[i] = 0;
  }

  print_state(vmtrace);

  while (true) {
    int next;  // the next instruction
    
    if (IP >= CODE_SIZE) {
      error(0, 0, "ip out of bounds");
      exit(1);
    }

    Instruction instruction = code[IP];
    if (0 != code[IP].op) fprintf(vmtrace, "(ip=%d) %s\n", IP, code_string[IP]);
    next = IP + 1;  // can be overwritten by a branch; set to IP at end of loop

    switch (instruction.op) {
    case OP_READ:
      {
        // given
        unsigned long int dest;
        fscanf(vmin, "%lu\n", &dest);
        uint32_t num = (uint32_t) dest;  // warning: no check for overflow
        reg[instruction.arg1] = num;
      }
      break;
    case OP_WR:
      // given
      fprintf(vmout, "%d\n", reg[instruction.arg1]);
      break;
    case OP_BEQ:
      // given
      if (z) {
        next = IP + instruction.arg1;
      }
      break;
    case OP_BLT:
      // TODO
	  if(n)
		  next = IP + instruction.arg1;
      break;
    case OP_BLE:
      // TODO
	  if(n || z)
		  next = IP + instruction.arg1;		  
	  break;
    case OP_BNE:
      // TODO
      if(!z)
		  next = IP + instruction.arg1;
	  break;
    case OP_BGT:
      // TODO
      if(!z)
		next = IP + instruction.arg1;
	  break;
    case OP_BGE:
      // TODO
      if(!z || n)
		next = IP + instruction.arg1;
	  break;
    case OP_BR:
      // TODO
      next = IP + instruction.arg1;
	  break;
    case OP_BL:
      // TODO
      reg[14] = IP + 1;
	  next = IP + instruction.arg1;
	  break;
    case OP_RET:
      // TODO
      next = reg[instruction.arg1];
	  break;
    case OP_MOV:
      // TODO
      reg[instruction.arg1] = reg[instruction.arg2];
	  break;
    case OP_CMP:
      // TODO
    if(reg[instruction.arg1] == reg[instruction.arg2])
		z = 1;
	else
		z = 0;
    if(reg[instruction.arg1] < reg[instruction.arg2])
		  n = 1;
	else
		n = 0;
	  break;
    case OP_ADD:
      // TODO
      reg[instruction.arg1] = reg[instruction.arg2] + reg[instruction.arg3];
	  break;
    case OP_SUB:
      // TODO
      reg[instruction.arg1] = reg[instruction.arg2] - reg[instruction.arg3];
	  break;
    case OP_MUL:
      // TODO
      reg[instruction.arg1] = reg[instruction.arg2] * reg[instruction.arg3];
	  break;
    case OP_DIV:
      // TODO
      reg[instruction.arg1] = reg[instruction.arg2] / reg[instruction.arg3];
	  break;
    case OP_MOD:
      // TODO
	  reg[instruction.arg1] = reg[instruction.arg2] % reg[instruction.arg3];
	  break;
    case OP_MOVI:
      // TODO
      reg[instruction.arg1] = instruction.arg2;      
	  break;
    case OP_CMPI:
      // TODO
      reg[instruction.arg1] = reg[instruction.arg2] + instruction.arg3;            
	  break;
    case OP_ADDI:
      // TODO
      reg[instruction.arg1] = reg[instruction.arg2] + instruction.arg3;            
	  break;
    case OP_SUBI:
      // TODO
      reg[instruction.arg1] = reg[instruction.arg2] - instruction.arg3;      
	  break;
    case OP_MULI:
      // TODO
      reg[instruction.arg1] = reg[instruction.arg2] * instruction.arg3;            
	  break;
    case OP_DIVI:
      // TODO
      reg[instruction.arg1] = reg[instruction.arg2] / instruction.arg3;            
	  break;
    case OP_MODI:
      // TODO
      reg[instruction.arg1] = reg[instruction.arg2] % instruction.arg3;            
	  break;
    case OP_LD:
      // TODO
      reg[instruction.arg1] = mem[reg[instruction.arg2] + instruction.arg3];
	  break;
    case OP_ST:
      // TODO store in mem
      mem[reg[instruction.arg2] + instruction.arg3] = reg[instruction.arg1];
	  break;
    case OP_PSH:
      // TODO
      reg[instruction.arg2]++;
	  mem[reg[instruction.arg2]] = reg[instruction.arg1];
	  break;
    case OP_POP:
      // TODO
      reg[instruction.arg1] = mem[reg[instruction.arg2]];
	  reg[instruction.arg2]--;
	  break;
    case OP_NOP:
      // TODO
      
	  break;
    case OP_HLT:
      // TODO print machine state
      fprintf(vmtrace, "done\n");
      exit(0);
      break;
    default:
      error(0, 0, "unknown opcode");
      exit(1);
    }

    print_state(vmtrace);

    IP = next;
  }

  return 0;
}

void print_register(FILE *fp, int reg) {
  switch (reg) {
  case 12:
    fprintf(fp, "fp(r%d)", reg);
    break;
  case 13:
    fprintf(fp, "sp(r%d)", reg);
    break;
  case 14:
    fprintf(fp, "ln(r%d)", reg);
    break;
  case 15:
    fprintf(fp, "ip(r%d)", reg);
    break;
  default:
    fprintf(fp, "r%d", reg);
    break;
  }
}

void print_state(FILE *fp) {
  fprintf(fp, "registers: ");
  char *delim = "";
  for (int i = 0; i < NUM_REGS; i++) {
    fprintf(fp, "%s", delim);
    print_register(fp, i);
    fprintf(fp, "=%d", reg[i]);
    delim = ", ";
  }
  fprintf(fp, "\n");
  fprintf(fp, "mem[i]:");
  delim = "";
  for (int i = 0; i <= SP; i++) {
    fprintf(fp, "%s%5d", delim, mem[i]);
    delim = "|";
  }
  fprintf(fp, "\n");
  fprintf(fp, "     i:");
  delim = "";
  for (int i = 0; i <= SP; i++) {
    fprintf(fp, "%s%5d", delim, i);
    delim = "|";
  }
  fprintf(fp, "\n");
  fprintf(fp, "    fp:");
  delim = "";
  for (int i = 0; i <= SP; i++) {
    if (i == FP) {
      fprintf(fp, "%s   fp", delim);
    } else {
      fprintf(fp, "%s     ", delim);
    }
    delim = "|";
  }
  fprintf(fp, "\n");
  fprintf(fp, "    sp:");
  delim = "";
  for (int i = 0; i <= SP; i++) {
    if (i == SP) {
      fprintf(fp, "%s   sp", delim);
    } else {
      fprintf(fp, "%s     ", delim);
    }
    delim = "|";
  }
  fprintf(fp, "\n");
}
