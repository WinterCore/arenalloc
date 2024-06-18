#include <stdio.h>
#include "./arena_v0.h"


int main() {
    ArenaV0 *arena = arena_create();
    
    uint8_t *ptr = arena_alloc(arena, 1000);


    for (size_t i = 0; i < 10000; i += 1) {
        ptr[i] = 'c';
    }

    ptr[10000] = '\0';

    printf("%s", ptr);
    fflush(stdout);

    return 0;
}
