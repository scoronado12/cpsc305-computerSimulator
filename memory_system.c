#include <stdio.h>
#include "memory_system.h"
#include "memory.h"
#include "decoder.h"


void memory_store(int address, unsigned char value){
    unsigned int decoded_val = decoder(value);
    //TODO associate with address
}

unsigned char memory_fetch(int address){

    for (int i = 0; i <= 32; i++){
        for (int j = 0; j <= 32; j++){
            if (address == mem_chip.mem_arr[i][j]){
                return mem_chip.mem_arr[i][j];//TODO look more into this check, address is not comparable to contents of the 2d arr
            }
        }
    }

}

unsigned int memory_fetch_word(int address){

    for (int i = 0; i <= 32; i++){
        for (int j = 0; j <= 32; j++){
            if (address == mem_chip.mem_arr[i][j]){
                return decoder(mem_chip.mem_arr[i][j]); //TODO same idea here as memory_fetch()
            }

        }
    }

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
