#ifndef NKL_ALLOC_H
#define NKL_ALLOC_H 1

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

#define ARENA_OOM_HARDFAIL (1 << 0)
#define ARENA_NO_ZERO      (1 << 1)
void *arena_alloc(Arena *a, size_t size, size_t align, uint32_t flags);

#define ALLOC(arena, count, type) arena_alloc((arena), sizeof(type) * (count), _Alignof(type), 0)
#define ALLOCF(arena, count, type, flags) arena_alloc((arena), (count) * sizeof(type), _Alignof(type), (flags))

#endif // !NKL_ALLOC_H
