#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h>
#include <stdint.h>

typedef struct Arena
{
    uint8_t* data;
    size_t cursor;
    size_t size;
} Arena;

void arena_init(Arena* arena, size_t size);
void arena_free(Arena* arena);

uint8_t* arena_grab(Arena* arena, size_t bytes);

#ifdef ARENA_IMPL
#undef ARENA_IMPL

void arena_init(Arena* arena, size_t size)
{
    arena->data = (uint8_t*)malloc(size);
    arena->size = size;
    arena->cursor = 0;
}

void arena_free(Arena* arena)
{
    arena->cursor = 0;
    arena->size = 0;

    free(arena->data);
}

uint8_t* arena_get(Arena* arena, size_t bytes)
{
    size_t new_cursor = arena->cursor + bytes;

    if (new_cursor >= arena->size)
    {
        fprintf(stderr, "no available memory in arena\n");
        return NULL;
    }
    
    uint8_t* ptr = arena->data + arena->cursor;
    arena->cursor = new_cursor;

    return ptr;
}

#endif

#endif // ARENA_H
