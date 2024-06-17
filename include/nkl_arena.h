#ifndef NKL_ARENA_H
#define NKL_ARENA_H 1

#include <stddef.h>
#include <stdint.h>

typedef struct Arena Arena;
struct Arena {
  char *beg;
  size_t size;
  size_t off;
};

void arena_create(size_t size);
void arena_free(Arena *a);
void arena_reset(Arena *a);

#define ARENA_OOM_HARDFAIL ((unsigned long)1 << (unsigned long)0)
#define ARENA_NO_ZERO      ((unsigned long)1 << (unsigned long)1)
void *arena_alloc(Arena *a, size_t size, size_t align, unsigned long flags);

#define ALLOC(arena, count, type) arena_alloc((arena), sizeof(type) * (count), _Alignof(type), 0)
#define ALLOCF(arena, count, type, flags) arena_alloc((arena), (count) * sizeof(type), _Alignof(type), (flags))

#endif // !NKL_ARENA_H
