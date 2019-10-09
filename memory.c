/* *
 * Simulate the memory chip represented by a 2D array
 * Direction was seen on pg 67 of the PDF under heading
 * memory Module
 * */

struct mem_chip{
    
    unsigned char mem_arr[32][32];

} mem_chip;


unsigned char mem_get(unsigned int row_selected, unsigned int col_selected){

    unsigned char mem = "";

    //loop through 2d array and detect whether the char is the same from both ends
    for (int i = 0; i <= 32; i++){
        for (int j = 0 ; j <= 32 ; j++){
           if (mem_chip.mem_arr[i][j] == mem_chip.mem_arr[row_selected][col_selected]){
              mem = mem_chip.mem_arr[i][j]; //set it to mem 
           } 

        }
    }

	return mem; //return the unsigned char
}

void mem_put(unsigned int row_selected, unsigned int col_selected, unsigned char b){


}
