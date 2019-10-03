#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))


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

