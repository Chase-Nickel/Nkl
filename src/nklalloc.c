#include <nkltypes.h>
#include <nklmem.h>
#include <nklerror.h>
#include <stdlib.h>

typedef struct Arena Arena;
struct Arena {
	char *beg;
	char *end;
	ptrdiff_t off;
};

Arena *arena_create(ptrdiff_t size) {
	Arena *o = NULL;
	if (size == -1)
		size = 65536;
	if (size <= 0)
		return o;

	o = malloc(sizeof(Arena) + size);
	o->beg = (char *)o + sizeof(Arena);
	o->end = o->beg + size;
	o->off = 0;
	return o;
}
void arena_free(Arena *a) {
	free(a);
}
void arena_reset(Arena *a) {
	a->off = 0;
}

#define ARENA_OOM_HARDFAIL (1 << 0)
#define ARENA_NO_ZERO      (1 << 1)
void *arena_malloc(Arena *a, ptrdiff_t size, ptrdiff_t align, uint32_t flags) {
	if (a == NULL || size <= 0 || align <= 0 || (align & (align - 1)) != 0)
		return NULL;
	{
		void *o;
		ptrdiff_t pad = -(uintptr_t)(a->beg + a->off) & (align - 1);
		ptrdiff_t padded_size = size + pad;

		if (padded_size > a->end - a->beg - a->off) {
			if (flags & ARENA_OOM_HARDFAIL)
				error_oom(STR8("No memory remaining in arena. Exiting."));
			return NULL;
		}
		o = a->beg + pad;
		a->off += padded_size;
#ifdef NDEBUG
		return (flags & ARENA_NO_ZERO)
				? xmemset(o, 0, padded_size)
				: xmemset(o, 0xCD, padded_size);
#else
		return (flags & ARENA_NO_ZERO)
				? xmemset(o, 0, padded_size)
				: o;
#endif
	}
}

#define ALLOC(arena, count, type) arena_malloc((arena), sizeof(type) * (count), _Alignof(type), 0)
#define ALLOCF(arena, count, type, flags) arena_malloc((arena), sizeof(type) * (count), _Alignof(type), (flags))

