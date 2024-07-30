#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>
#include <stdint.h>

#define ARENA_PAGE_SIZE 4096

typedef struct ArenaV0 {
    uint8_t *data;
    size_t size;
    size_t current;
    struct ArenaV0 *next;
} ArenaV0;

ArenaV0 *arena_create();

void *arena_alloc(ArenaV0 *arena, size_t size);
void arena_reset(ArenaV0 *arena);
void arena_reset(ArenaV0 *arena);
void arena_destroy(ArenaV0 *arena);

#endif
