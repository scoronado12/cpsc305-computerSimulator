#include <stdio.h>
#include "memory_system.h"
#include "memory.h"

void memory_store(int address, unsigned char value){


}


void load_memory(char *filename){

    FILE *fp;
    
    fp = fopen(filename, "r");
    
    char content[12];
    
    char data[20];
    while(1){
        if (fscanf(fp, "%d", content) == EOF){
            break;
        } else{
            strcpy(/*spot in memory*/, content);
            //TODO load into spot in memory?
            
        }
    }    

}
