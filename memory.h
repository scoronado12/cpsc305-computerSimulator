
struct mem_chip{
    unsigned char mem_arr[32][32];
}mem_chip;


unsigned char mem_get(unsigned int row_selected, unsigned int col_selected);
void mem_put(unsigned int row_selected, unsigned int col_selected, unsigned char b);

