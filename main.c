#include "memory_system.h"

int main(){
	
    load_memory("mem_load.txt"); 
    memory_store_word(12, 0x0a0b0c0d); //store 0x0a0b0c0d in address 12
    printf("memory_fetch_word(12): 0x%08x\n", memory_fetch_word(12)); //0x0a0b0c0d should print out
    return 0;	 
}

