#include <stdio.h>
#include "memory_system.h"
#include "memory.h"
#include "decoder.h"

#define MEM_ROW (address/32)%32
#define MEM_COL address%32

void memory_store(int address, unsigned char value){
    
    //mem_chip.mem_arr[MEM_ROW][MEM_COL] = decoder(value);
    mem_put(MEM_ROW, MEM_COL, value);
}


unsigned char memory_fetch(int address){
    
    return mem_get(MEM_ROW, MEM_COL);

}

unsigned int memory_fetch_word(int address){
    //address = decoder(address);
    return decoder(mem_chip.mem_arr[MEM_ROW][MEM_COL]);
   // return mem_chip.mem_arr[MEM_ROW][MEM_COL];
}

void memory_dump(int start_address, int num_bytes){
    //may need a hand with this one
	for(int i = 0; i < num_bytes; i++){
	    printf("0x%04x (0d%04d) ", start_address, start_address);
	    unsigned char bytefetch = memory_fetch(start_address + i);
	    for(int j = 0;j < 8; j++){
		printf("0x%02x ", bytefetch);
	    }
	    printf("\n");
	} 
}

void memory_store_word(int address, unsigned int value){

    mem_chip.mem_arr[MEM_ROW][MEM_COL] = value;

}

void load_memory(char *filename){

    FILE *fp;
     
    fp = fopen(filename, "r");
    
    char data_buff[10];
    while(1){
        if (fscanf(fp, "%x", data_buff) == EOF){ //changed from %d to %x per gusty's instructions
            break;
        }
    }    
    char add = data_buff[0];
    int starting_addr = (int) add;
//      printf("Value of 'add': %d\n", starting_addr);
    for(int i = 1; i < 10; i++){
//	printf("The value: %x\nThe address: %d\n", data_buff[i], starting_addr + (i-1));  
	memory_store_word(starting_addr + (i-1), data_buff[i]);
    }   

}
