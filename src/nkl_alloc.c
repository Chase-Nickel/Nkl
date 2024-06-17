#include <nkl_error.h>
#include <nkl_str8_def.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct Arena Arena;
struct Arena {
    char *beg;
    size_t size;
    size_t off;
};

Arena arena_create(size_t size) {
    Arena a = {0};
    if (size == 0) {
        size = 65536;
    }
    a.beg = malloc(size);
    if (a.beg) {
        a.size = size;
    }
    return a;
}
void arena_free(Arena *a) { free(a->beg); }

void arena_free_s(Arena *a) {
    free(a->beg);
    a->beg = NULL;
    a->size = 0;
    a->off = 0;
}

void arena_reset(Arena *a) { a->off = 0; }

#define ARENA_OOM_HARDFAIL ((unsigned long)1 << (unsigned long)0)
#define ARENA_NO_ZERO ((unsigned long)1 << (unsigned long)1)
void *arena_malloc(Arena *a, size_t size, size_t align, unsigned long flags) {
    if (!a || (align & (align - 1)) != 0) {
        return NULL;
    }
    size_t pad = -(uintptr_t)(a->beg + a->off) & (align - 1);
    size_t padded_size = size + pad;

    if (a->off + padded_size > a->size) {
        if (flags & ARENA_OOM_HARDFAIL)
            error_oom(STR8("No memory remaining in arena. Exiting."));
        return NULL;
    }
    void *o = a->beg + pad;
    a->off += padded_size;
    if (flags & ARENA_NO_ZERO) {
#ifdef NDEBUG
        return memset(o, 0xCD, padded_size);
#else
        return o;
#endif
    }
    return memset(o, 0, padded_size);
}

#define ALLOC(arena, count, type)                                              \
    arena_malloc((arena), sizeof(type) * (count), _Alignof(type), 0)
#define ALLOCF(arena, count, type, flags)                                      \
    arena_malloc((arena), sizeof(type) * (count), _Alignof(type), (flags))
