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

void step(){
    int pc = cpsr; //felt logical
    unsigned int reg;
    unsigned int address; 

    int inst = registers[pc]; // fetch
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
          //add
          break;
       case SUB:
          //subtract
          break;
       case MUL:
          //multiply
          break;
       case DIV:
          //divide
          break;
       case CMP:
          //compare
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
 
}
