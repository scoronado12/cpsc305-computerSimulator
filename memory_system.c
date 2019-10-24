#include <stdio.h>
#include "memory_system.h"
#include "memory.h"
#include "decoder.h"

#define MEM_ROW (address/32)%32
#define MEM_COL (address)%32

void memory_store(int address, unsigned char value){
    
    //mem_chip.mem_arr[MEM_ROW][MEM_COL] = decoder(value);
    unsigned int lower5 = (address) & 0x1f;
    unsigned int upper5 = (address >> 5) & 0x1f;
    
    mem_put(decoder(lower5), decoder(upper5), value);
}


unsigned char memory_fetch(int address){
    
    unsigned int lower5 = (address) & 0x1f;
    unsigned int upper5 = (address >> 5) & 0x1f;
    
    return mem_get(decoder(lower5), decoder(upper5));

}

unsigned int memory_fetch_word(int address){
    
    unsigned byte1 = memory_fetch(address);
    unsigned byte2 = memory_fetch(address + 1);
    unsigned byte3 = memory_fetch(address + 2);
    unsigned byte4 = memory_fetch(address + 3);
    
    
    //reverse operation of memory store word
    return (byte4 << 24) | (byte3 << 16) | (byte2 << 8) | byte1;
    
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
    //split bytes
    unsigned byte1 = value & 0xff;
    unsigned byte2 = (value >> 8) & 0xff;
    unsigned byte3 = (value >> 16) & 0xff;
    unsigned byte4 = (value >> 24) & 0xff;

    printf("%x %x %x %x\n",byte1, byte2, byte3, byte4);
    //store the memory
    memory_store(address, byte1);
    memory_store(address + 1, byte2);
    memory_store(address + 2, byte3);
    memory_store(address + 3, byte4);

}

void load_memory(char *filename){

    FILE *fp;
     
    fp = fopen(filename, "r");
    unsigned int addr;
    unsigned int data_buff;
    fscanf(fp, "%x", &addr);
    
    
    while(1){
        if (fscanf(fp, "%x", &data_buff) == EOF){ //changed from %d to %x per gusty's instructions
            break;
        }
        
        memory_store_word(addr += 4, data_buff);
        
    }    
    
    /*
    char add = data_buff[0];
    int starting_addr = (int) add;
//      printf("Value of 'add': %d\n", starting_addr);
    for(int i = 1; i < 10; i++){
//	printf("The value: %x\nThe address: %d\n", data_buff[i], starting_addr + (i-1));  
        memory_store_word(starting_addr + (i-1), data_buff[i]);
    }   
*/
}
