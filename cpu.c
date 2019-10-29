#include "bit_functions.h"
#include "memory_system.h"
#include "cpu.h"

int registers[16];
int cpsr; //current prog status register

void set_reg(int reg, int value){
  registers[reg] = value;  
}

int get_reg(int reg){
   return registers[reg]; 
}

int get_cpsr(){
    return cpsr;
}


void show_regs(){
    for (int i = 0; i <= 16; i++)
        printf("Register %d: %d", i, get_reg(i));
}


void step(){
    int pc = registers[PC]; 
    unsigned int reg;
    unsigned int address; 
    int dest, r1, r2;
    unsigned int inst = memory_fetch_word(registers[PC]); // fetch
    int opcode = inst >> 24;


   switch (opcode) {// decode
       case LDR: //execute
           reg = inst >> 16 & 0xff;
           address = inst & 0xffff;
           if (address > 1023 || reg > 15) {
               printf("Address/Register out of bounds.\n");
               exit(1);
           }
           registers[reg] = memory_fetch_word(address);
           printf("reg: %d, reg val: 0x%x08x, address: 0x%04x\n", reg, registers[reg], address);

           pc += 4;
           break;
       case LDI:
           //LDI
       case LDX:
           //LDI
       case STR:
          //memory store word
          reg = inst >> 16 & 0xff;
          address = inst & 0xffff;
          if (address > 1023 || reg >15){
              printf("Address/Register out of bounds.\n");
              exit(1);
          }
          memory_store_word(address, reg);
          pc += 4;
          
          break; 
       case ADD:
          reg = inst >> 16 & 0xff;
          address = inst & 0xffff;
          if (address > 1023 || reg > 15) {
              printf("Address/Register out of bounds.\n");
              exit(1);
          }

          dest = (inst >> 16) & 0xff;
          r1 = (inst >> 8) & 0xff;
          r2 = (inst >> 0) & 0xff;
          registers[dest] = registers[r1] + registers[r2];

          break;
       case SUB:
          reg = inst >> 16 & 0xff;
          address = inst & 0xffff;
          if (address > 1023 || reg > 15) {
              printf("Address/Register out of bounds.\n");
              exit(1);
          }

          dest = (inst >> 16) & 0xff;
          r1 = (inst >> 8) & 0xff;
          r2 = (inst >> 0) & 0xff;
          registers[dest] = registers[r1] - registers[r2];



          break;
       case MUL:
          //multiply
          reg = inst >> 16 & 0xff;
          address = inst & 0xffff;
          if (address > 1023 || reg > 15) {
              printf("Address/Register out of bounds.\n");
              exit(1);
          }

          dest = (inst >> 16) & 0xff;
          r1 = (inst >> 8) & 0xff;
          r2 = (inst >> 0) & 0xff;
          registers[dest] = registers[r1] * registers[r2];

          break;
       case DIV:
          //divide
          reg = inst >> 16 & 0xff;
          address = inst & 0xffff;
          if (address > 1023 || reg > 15) {
              printf("Address/Register out of bounds.\n");
              exit(1);
          }

          dest = (inst >> 16) & 0xff;
          r1 = (inst >> 8) & 0xff;
          r2 = (inst >> 0) & 0xff;
          registers[dest] = registers[r1] / registers[r2];
          break;
       case CMP:
          //compare
          reg = inst >> 16 & 0xff;
          address = inst & 0xffff;
          if (address > 1023 || reg > 15) {
              printf("Address/Register out of bounds.\n");
              exit(1);
          }


       case B:
          //branch
          break;
       case BEQ:
          //branch equal to
          break;
       case BNE:
         //branch not equal
       case BLT:
         //branch less than
          break;
       case BGT:
          //branch greater than
          break;
   }

   registers[PC] += pc; //increase program counter by 4 each time
 
}
