#include <stdlib.h>
#include "chunk.h"
#include "memory.h"
#include "common.h"
#include "rle.h"

void initChunk(Chunk *chunk)
{
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
    init_rle(&chunk->rle);
}

void freeChunk(Chunk *chunk)
{
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

void writeChunk(Chunk *chunk, uint8_t byte, int line)
{
    if (chunk->capacity < chunk->count + 1)
    {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    push_rle(&chunk->rle, line);
    chunk->count++;
}

int addConstant(Chunk *chunk, Value value)
{
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

// Do not forget to update what Value type evolves
void writeConstant(Chunk *chunk, Value value, int line)
{
    int index = addConstant(chunk, value);
    if (index >= 256)
    {
        writeChunk(chunk, index, line);
        writeChunk(chunk, index, line);
    }
}

int getLine(Chunk chunk, int position)
{
    int arr[chunk.rle.original_count];
    expand_rle(&chunk.rle, arr, chunk.rle.original_count);
    return arr[position];
}