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

    arena->next = NULL;
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
            uint8_t *ptr = &arena->data[arena->current];
            arena->current += size;
            return ptr;
        }

        if (arena->next != NULL) {
            arena = arena->next;
        }
    } while (arena->next != NULL);

    size_t new_arena_size = size > ARENA_PAGE_SIZE ? size : ARENA_PAGE_SIZE;

    ArenaV0 *new_arena = _arena_create(new_arena_size);
    new_arena->size = size;
    new_arena->current = size;

    arena->next = new_arena;

    return new_arena->data;
}

void arena_destroy(ArenaV0 *arena) {
    while (arena) {
        ArenaV0 *tmp_next = arena->next;

        free(arena->data);
        free(arena);

        arena = tmp_next;
    }
}

void arena_reset(ArenaV0 *arena) {
    while (arena) {
        arena->current = 0;
        arena = arena->next;
    }
}

