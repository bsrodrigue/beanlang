#include "common.h"
#include "rle.h"

void init_rle(RLE *rle)
{
    rle->capacity = 0;
    rle->count = 0;
    rle->numbers = NULL;
    rle->last_number = 0;
    rle->last_index = 0;
}

void expand_rle(RLE *rle)
{
    int arr[256];
    int last_index = 0;

    for (int i = 0; i < rle->count; i = i + 2)
    {
        int number = rle->numbers[i];
        int occurences = rle->numbers[i + 1];

        for (int j = last_index; j < last_index + occurences; j++)
        {
            arr[j] = number;
        }

        last_index = last_index + occurences;
    }

    for (int i = 0; i < 34; i++)
    {
        printf("%d", arr[i]);
    }
    printf("\n");
}

void push_rle(RLE *rle, int number)
{
    if (rle->capacity < rle->count + 2)
    {
        rle->capacity = rle->capacity < 8 ? 8 : 2 * rle->capacity;
        rle->numbers = (int *)realloc(rle->numbers, sizeof(int) * rle->capacity);
    }

    if (rle->numbers[0] == NULL)
    {
        rle->numbers[0] = number;
        rle->numbers[1] = 1;
        rle->last_index = 1;
        rle->last_number = number;
        rle->count = 2;
        return;
    }

    if (rle->last_number == number)
    {
        rle->numbers[rle->last_index]++;
    }
    else
    {
        rle->numbers[rle->last_index + 1] = number;
        rle->numbers[rle->last_index + 2] = 1;
        rle->last_number = number;
        rle->last_index = rle->last_index + 2;
        rle->count = rle->count + 2;
    }
}

void print_rle(RLE rle)
{
    for (int i = 0; i < rle.count; i = i + 2)
    {
        printf("%d:%d\n", rle.numbers[i], rle.numbers[i + 1]);
    }
}