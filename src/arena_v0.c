#include "./arena_v0.h"
#include <stdio.h>
#include <stdlib.h>

static ArenaV0* _arena_create(size_t size) {
    uint8_t *data = malloc(size);

    if (data == NULL) {
        fprintf(stderr, "Failed to alloc data for arena (size = %zu)", size);
        exit(EXIT_FAILURE);
    }
    
    ArenaV0 *arena = malloc(sizeof(ArenaV0));
    
    if (data == NULL) {
        fprintf(stderr, "Failed to alloc arena struct");
        exit(EXIT_FAILURE);
    }

    arena->next_arena = NULL;
    arena->current = 0;
    arena->data = data;
    arena->size = size;

    return arena;
}

ArenaV0 *arena_create() {
    return _arena_create(ARENA_PAGE_SIZE);
}

void *arena_alloc(ArenaV0 *arena, size_t size) {
    do  {
        if ((arena->size - arena->current) >= size) {
            arena->current += size;
            return &arena->data[arena->current + size];
        }

        arena = arena->next_arena;
    } while (arena->next_arena != NULL);

    size_t new_arena_size = size > ARENA_PAGE_SIZE ? size : ARENA_PAGE_SIZE;

    ArenaV0 *new_arena = _arena_create(new_arena_size);
    new_arena->size = size;
    new_arena->current = size;

    arena->next_arena = new_arena;

    return new_arena->data;
}

void arena_destroy(ArenaV0 *arena) {
    while (arena) {
        ArenaV0 *tmp_next = arena->next_arena;

        free(arena->data);
        free(arena);

        arena = tmp_next;
    }
}


