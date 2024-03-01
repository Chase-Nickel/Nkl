#ifndef __NKL_ALLOC
#define __NKL_ALLOC 1

#include <nkltypes.h>

typedef struct Arena Arena;
struct Arena {
  char *beg;
  char *end;
  ptrdiff_t off;
};

extern void arena_create(ptrdiff_t size);
extern void arena_free(Arena *a);
extern void arena_reset(Arena *a);

#define ARENA_OOM_HARDFAIL (1 << 0)
#define ARENA_NO_ZERO      (1 << 1)
extern void *arena_alloc(Arena *a, ptrdiff_t size, ptrdiff_t align, uint32_t flags);

#define ALLOC(arena, count, type) arena_alloc((arena), sizeof(type) * (count), _Alignof(type), 0)
#define ALLOCF(arena, count, type, flags) arena_alloc((arena), (count) * sizeof(type), _Alignof(type), (flags))

#endif

