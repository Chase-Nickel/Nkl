#ifndef __STRING8_H
#define __STRING8_H 1

#include <nklalloc.h>
#include <nkltypes.h>

/* Return an allocated str8 with the same buffer & length of `s` */
extern str8_t str8_dup(const str8_t s, Arena *arena);
/* Return an allocated str8 with the same `n` bytes of the buffer of `s`. */
extern str8_t str8_ndup(const str8_t s, int32_t n, Arena *arena);

/* Return a sub-string of `s` from `start` to `end` exclusive */
extern str8_t str8_sub(const str8_t s, int32_t start, int32_t end);
/* Return an allocated sub-string of `s` from `start` to `end` exclusive */
extern str8_t str8_suba(const str8_t s, int32_t start, int32_t end, Arena *arena);

/* Compare `s1` and `s2` alphabetically. Return 0 if `s1` and `s2` are alphabetically equal. Return a negative value if `s1` is alphabetically less than `s2`. Return a positive value if `s1` is alphabetically greater than `s2` */
extern int32_t str8_cmp(const str8_t s1, const str8_t s2);
/* Compare at most `n` bytes of `s1` and `s2`. Return 0 if `s1` and `s2` are alphabetically equal. Return a negative value if `s1` is alphabetically less than `s2`. Return a positive value if `s1` is alphabetically greater than `s2` */
extern int32_t str8_ncmp(const str8_t s1, const str8_t s2, int32_t n);

/* Return a pointer to the first occurance of `c` in `string`. Returns NULL if not in the string. */
extern char *str8_chr(const str8_t s, char c);

/* Calculates the length (in bytes) of the initial segment of `s` which consists entirely of bytes in `accept`. */
extern int32_t str8_spn(const str8_t s, const str8_t accept);
/* Calculates the length of the initial segment of `s` which consists entirely of bytes not in `reject`. */
extern int32_t str8_cspn(const str8_t s, const str8_t reject);

#endif

