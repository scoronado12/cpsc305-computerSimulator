#include <stdio.h>
#include "memory_system.h"

void memory_store(int address, unsigned char value){


}


void load_memory(char *filename){
    FILE *fp;
    
    fp = fopen(filename, "r");

    
    char data[20];
    while(1){
        if (fscanf(fp, "%d") == EOF){
            break;
        } else{

            //TODO load into spot in memory?

        }
    }    

}
