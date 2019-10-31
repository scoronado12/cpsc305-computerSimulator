#include "memory.h"
#include "bit_functions.h"
/* *
 * Simulate the memory chip represented by a 2D array
 * Direction was seen on pg 67 of the PDF under heading
 * memory Module
 * */



unsigned char mem_get(unsigned int row_selected, unsigned int col_selected){

    
    //Was at risk of reimplementing bit_find - so this is my solution
    return mem_chip.mem_arr[bit_find(row_selected)][bit_find(col_selected)];
    
    /* Commented out b/c this is the job of bit_find() 
    //loop through 2d array and detect whether the char is the same from both ends
    for (int i = 0; i <= 32; i++){
        for (int j = 0 ; j <= 32 ; j++){
           if (mem_chip.mem_arr[i][j] == mem_chip.mem_arr[row_selected][col_selected]){
              mem = mem_chip.mem_arr[i][j]; //set it to mem 
           } 
        }   
    }*/

}

void mem_put(unsigned int row_selected, unsigned int col_selected, unsigned char b){
    //Set this spot in the array to the unsigned char b that was passed in 
    mem_chip.mem_arr[bit_find(row_selected)][bit_find(col_selected)] = b;

}
