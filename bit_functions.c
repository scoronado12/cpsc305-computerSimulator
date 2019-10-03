#include "bit_functions.h"



int bit_find(int value){

    for (int i = 0; i < 32; i++){
        if (CHECK_BIT(value, i))
            return i;
    }

}
