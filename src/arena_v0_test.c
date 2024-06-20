#include <assert.h>
#include <stdio.h>
#include "./arena_v0.h"


void test_create_arena() {
    ArenaV0 *arena = arena_create();
    
    assert(arena->size == ARENA_PAGE_SIZE && "Arena has the correct size");
    assert(arena->current == 0 && "Start pointer should be 0");
    assert(arena->data != NULL && "Data pointer should not be null");
}

void test_alloc1() {
    ArenaV0 *arena = arena_create();
    
    uint8_t *ptr = arena_alloc(arena, sizeof(uint8_t) * 64);

    for (size_t i = 0; i < 64; i += 1) {
        ptr[i] = 'A';
    }

    assert(arena->current == 64 && "Arena's pointer should advance after alloc");

    size_t correct_char_count = 0;

    for (size_t i = 0; i < 64; i += 1) {
        if (arena->data[i] == 'A') {
            correct_char_count += 1;
        }
    }

    assert(correct_char_count == 64 && "Saved data should be available");
}

void test_alloc2() {
    ArenaV0 *arena = arena_create();
    
    uint8_t *ptr1 = arena_alloc(arena, sizeof(uint8_t) * 200);
    uint8_t *ptr2 = arena_alloc(arena, sizeof(uint8_t) * ARENA_PAGE_SIZE * 2);
    uint8_t *ptr3 = arena_alloc(arena, sizeof(uint8_t) * 300);

    assert(ptr1 == &arena->data[0] && "small pointer should point to first region");
    assert(ptr2 == &arena->next_arena->data[0] && "big pointer should point to second region");
    assert(ptr3 == &arena->data[200] && "2nd small pointer should point to first region");
}

int main() {
    test_create_arena();
    test_alloc1();
    test_alloc2();

    return 0;
}
