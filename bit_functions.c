#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
#define SET_BIT(var1, var2, pos) ((var1=var2) & (1<<(pos)))

/**
 * find the fisrt bit set in value, beginning with bit position 0
 * @param value - the value to search for a bit set
 * @return i - the first bit position or -1 if the value is 0
 */

int bit_find(int value){

    for (int i = 0; i < 32; i++)
        if (CHECK_BIT(value, i))
            return i;
    return -1;
}

int bit_test(int value, int bit_pos){
	// Will return 0 if false, 1 if true
	return CHECK_BIT(value, bit_pos); //check bit for every value that is passed in
    
}

void bit_set(int *value, int bit_pos){

    *value |= 1 << bit_pos;
}

void bit_clear(int *value, int bit_pos){

   *value &= ~(1 << bit_pos); 

} 
