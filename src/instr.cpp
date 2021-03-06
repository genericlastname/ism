#include <stdio.h>
#include "instr.h"

int* create_registers() {
  // create an array to hold registers
  int* r = new int[33];
  return r;
}

int* create_memory() {
  // create an array to hold memory
  int* m = new int[32];
  return m;
}

void add_op(int* regs, int rd, int rs, int rt) {
  // add register rs to rt and store the result in rd
  *(regs+rd) = *(regs+rs) + *(regs+rt);
  *(regs+32) += 4; // PC register
}

void sub_op(int* regs, int rd, int rs, int rt) {
  // sub register rs and rt and store the result in rd
  *(regs+rd) = *(regs+rs) - *(regs+rt);
  *(regs+32) += 4; // PC register
}

void and_op(int* regs, int rd, int rs, int rt) {
  *(regs+rd) = *(regs+rs) & *(regs+rt);
  *(regs+32) += 4; // PC register
}

void or_op(int* regs, int rd, int rs, int rt) {
  *(regs+rd) = *(regs+rs) & *(regs+rt);
  *(regs+32) += 4; // PC register
}

void lw_op(int* regs, int* mem, int rs, int rt, int offset) {
  *(regs+rt) = *(mem+( *(regs+rs)+offset) );
  *(regs+32) += 4; // PC register
}

void sw_op(int* regs, int* mem, int rs, int rt, int offset) {
  *(mem+( *(regs+rs)+offset) ) = *(regs+rt);
  *(regs+32) += 4; // PC register
}

void addi_op(int* regs, int rt, int rs, __int16_t imm) {
  *(regs+rt) = *(regs+rs) + imm;
  *(regs+32) += 4; // PC register
}

void beq_op(int* regs, int rt, int rs, int offset) {
  if ( *(regs+rt) == *(regs+rs) ) {
    *(regs+32) += 4*offset; // mult by 4 to get number of byte to inc PC by
  }
  else {
    *(regs+32) += 4;
  }
}

void bne_op(int* regs, int rt, int rs, int offset) {
  if ( *(regs+rt) != *(regs+rs) ) {
    *(regs+32) += 4*offset; // mult by 4 to get number of byte to inc PC by
  }
  else {
    *(regs+32) += 4;
  }
}

void show(const int* regs, bool m) {
  for (int i=0; i<32; i+=4) {
    printf("%i:\t%04X\t %i:\t%04X\t %i:\t%04X\t %i:\t%04X\n",
            i, regs[i] & 0xffff, i+1, regs[i+1] & 0xffff, i+2, regs[i+2] & 0xffff, i+3, regs[i+3] & 0xffff);
  }

  if (!m) printf("PC:\t%04X\n", regs[32]);
}
