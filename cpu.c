#include <stdio.h>
#include <stdlib.h>
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
        printf("Register %d: %d \n", i, get_reg(i));
}


void step(){
    int pc = registers[PC]; 
    unsigned int reg;
    unsigned int address; 
    unsigned int literal; 
    int dest, r1, r2;
    unsigned int inst = memory_fetch_word(registers[PC]); // fetch from PC reg 14
    int opcode = inst >> 24;
    printf("PC: %x, Inst: %x, Opcode: %d\n" , registers[PC],inst, opcode);

   switch (opcode) {// decode
       case LDR: //execute
           printf("LDR detected\n");

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
           //LDI memory_fetch
           reg = inst >> 16 & 0xff;
           literal = inst & 0xffff;
           if (literal > 1023 || reg > 15) {
               printf("Address/Register out of bounds.\n");
               exit(1);
           }
           registers[reg] = literal;
           printf("reg: %d, reg val: 0x%x08x, address: 0x%04x\n", reg, registers[reg], literal);

           pc += 4;

           break;
       case LDX:
          // LDX 
           dest = inst >> 16 & 0xff;
           int offset = inst >> 8 & 0xff;
           r1 = inst & 0xff;
           registers[dest] = memory_fetch_word(registers[r1] + offset);
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
          memory_store_word(address, registers[reg]);
          pc += 4;
          
          break; 
       case ADD:
          dest = (inst >> 16) & 0xff;
          r1 = (inst >> 8) & 0xff;
          r2 = (inst >> 0) & 0xff;
          if (dest > 15 || r1 > 15 || r2 > 15) {
              printf("Register out of bounds.\n");
              exit(1);
          }
          registers[dest] = registers[r1] + registers[r2];
          pc += 4;
          break;
       case SUB:
          dest = (inst >> 16) & 0xff;
          r1 = (inst >> 8) & 0xff;
          r2 = (inst >> 0) & 0xff;
          if (dest > 15 || r1 > 15 || r2 > 15) {
              printf("Register out of bounds.\n");
              exit(1);
          }
          registers[dest] = registers[r1] - registers[r2];
          pc += 4;
          break;
       case MUL:
          dest = (inst >> 16) & 0xff;
          r1 = (inst >> 8) & 0xff;
          r2 = (inst >> 0) & 0xff;
          if (dest > 15 || r1 > 15 || r2 > 15) {
              printf("Register out of bounds.\n");
              exit(1);
          }
          registers[dest] = registers[r1] * registers[r2];
          pc += 4;
          break;
       case DIV:
          dest = (inst >> 16) & 0xff;
          r1 = (inst >> 8) & 0xff;
          r2 = (inst >> 0) & 0xff;
          if (dest > 15 || r1 > 15 || r2 > 15) {
              printf("Register out of bounds.\n");
              exit(1);
          }
          registers[dest] = registers[r1] / registers[r2];
          pc += 4;
          break;
       case CMP:
          //compare
          r1 = (inst >> 8) & 0xff;
          r2 = (inst >> 0) & 0xff;
          if (r1 > 15 || r2 > 15) {
              printf("Register out of bounds.\n");
              exit(1);
          }
          if (registers[r1] == registers[r2]){
              bit_set(&cpsr, Z);
              bit_clear(&cpsr, LT);
              bit_clear(&cpsr, GT);
              // Z set to 1
          } else if (registers[r1] < registers[r2]){
              bit_set(&cpsr, LT);
              bit_clear(&cpsr, Z);
              bit_clear(&cpsr, GT);

          } else if (registers[r1] > registers[r2]){
              bit_set(&cpsr, GT);
              bit_clear(&cpsr, Z);
              bit_clear(&cpsr, LT);
          
          } else {
              printf("CMP Invalid, clearing...\n");
              bit_clear(&cpsr, GT);
              bit_clear(&cpsr, LT);
              bit_clear(&cpsr, Z);
          
          }
          pc += 4;
          break;
       case B:
          
          reg = inst >> 16 & 0xff;
          address = inst & 0xffff;
          if (address > 1023 || reg > 15) {
              printf("Address/Register out of bounds.\n");
              exit(1);
          }

	  //notice how there is no if or check_bit() condition
          pc = address; //set pc to address unconditionally
          break;
       case BEQ:
          //branch equal to
          reg = inst >> 16 & 0xff;

          address = inst & 0xffff;
          if (address > 1023 || reg > 15) { //check if do-able
              printf("Address/Register out of bounds.\n");
              exit(1);
          }

          if (bit_test(cpsr, Z)){ //if cpsr's bit Z is turned on
              pc = address;
          } else {
              pc += 4;
          }

          //do more stuff
          break;
       case BNE:
          reg = inst >> 16 & 0xff;
          address = inst & 0xffff;
          if (address > 1023 || reg > 15) { //check if do-able
              printf("Address/Register out of bounds.\n");
              exit(1);
          }
          
          if (!bit_test(cpsr, Z)){ //aka if this is true
              pc = address; //set PC to address
          } else {
              pc += 4;
          }
          break;
       case BLT:
         //branch less than
         reg = inst >> 16 & 0xff;
         address = inst & 0xffff;
         if (address > 1023 || reg > 15) { //check if do-able
             printf("Address/Register out of bounds.\n");
             exit(1);
         }
         
         if (bit_test(cpsr, LT)){ //aka if this is true
             pc = address; //set PC to address
         }else {
             pc += 4;
         }
         break;
       case BGT:
         reg = inst >> 16 & 0xff;
         address = inst & 0xffff;
         if (address > 1023 || reg > 15) { //check if do-able
             printf("Address/Register out of bounds.\n");
             exit(1);
          }
          
          if (bit_test(cpsr, GT)){ //aka if this is true
              pc = address; //set PC to address
          } else {
              pc += 4;
          }

          break;
       case MOV:
         /*  WARNING: this may or may not work correctly */ 
         r1 = (inst >> 8) & 0xff;
         r2 = (inst >> 0) ^ 0xff;
         if (r1 > 15 || r2 > 15) {
             printf("Register out of bounds.\n");
             exit(1);
         }
         registers[r1] = registers[r2];
         pc += 4;
         break;
        case BL:
         /* 
          * This also is an attempt to do something based on assumptions alone */
         address = inst & 0xffff;
         if (address > 1023) {
             printf("Address out of bounds.\n");
             exit(1);
         }

         
	  //notice how there is no if or check_bit() condition
         pc = address; //set pc to address unconditionally
         registers[R14] = pc+4;
         break;
          
   }

   
   // registers[PC] += pc; //increase program counter by 4 each time
   registers[PC] = pc; //increase program counter by 4 each time
 
}

void step_n(int n){
    for (int i = 0; i <= n; i++){
        step();
    }

}

