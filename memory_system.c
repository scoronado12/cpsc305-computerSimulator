#include <stdio.h>
#include "memory_system.h"
#include "memory.h"
#include "decoder.h"

#define MEM_ROW address/32%32
#define MEM_COL address%32

void memory_store(int address, unsigned char value){
    
    mem_chip.mem_arr[MEM_ROW][MEM_COL] = decoder(value);

}


unsigned char memory_fetch(int address){
    
    return mem_chip.mem_arr[MEM_ROW][MEM_COL];

}

unsigned int memory_fetch_word(int address){
    //address = decoder(address);
    return decoder(mem_chip.mem_arr[MEM_ROW][MEM_COL]);
   // return mem_chip.mem_arr[MEM_ROW][MEM_COL];
}

void memory_dump(int start_address, int num_bytes){
    //may need a hand with this one

}

void memory_store_word(int address, unsigned int value){

    mem_chip.mem_arr[MEM_ROW][MEM_COL] = value;

}

void load_memory(char *filename){

    FILE *fp;
     
    fp = fopen(filename, "r");
    
    char data_buff[20];
    while(1){
        if (fscanf(fp, "%d", data_buff) == EOF){
            break;
        } else{
            //strcpy(/*SOME SORT OF FUNC IN THIS FILE */, content);
            //TODO First check if the entire file is loaded into our data_buff
            //data_buff[0] is going to equal the starting address (check pg 67)
            
        }
    }    

}
