#include <assert.h>
#include <stdio.h>
#include "./arena_v0.h"


void test_create_arena() {
    ArenaV0 *arena = arena_create();
    
    assert(arena->size == ARENA_PAGE_SIZE && "Arena has the correct size");
    assert(arena->current == 0 && "Start pointer should be 0");
    assert(arena->data != NULL && "Data pointer should not be null");
}

int main() {
    test_create_arena();

    return 0;
}
