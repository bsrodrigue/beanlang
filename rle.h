#ifndef clox_rle_h
#define clox_rle_h

typedef struct
{
    int last_number;
    int last_index;
    int count;
    int capacity;
    int original_count;
    int *numbers;
} RLE;

void init_rle(RLE *rle);
void push_rle(RLE *rle, int number);
void expand_rle(RLE *rle, int *arr, int size);
void print_rle(RLE rle);

#endif