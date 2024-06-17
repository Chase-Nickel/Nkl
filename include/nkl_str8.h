#ifndef NKL_STR8_H
#define NKL_STR8_H 1

#include <nkl_arena.h>
#include <nkl_str8_def.h>
#include <stddef.h>

/* Return an allocated str8 with the same buffer & length of `s` */
str8 str8_dup(Arena *arena, str8 s);

/* Return an allocated str8 with the same `n` bytes of the buffer of `s`. */
str8 str8_ndup(Arena *arena, str8 s, size_t n);

/* Return a sub-string of `s` from `start` to `end` exclusive */
str8 str8_sub(str8 s, size_t start, size_t end);

/* Return an allocated sub-string of `s` from `start` to `end` exclusive */
str8 str8_suba(Arena *arena, str8 s, size_t start, size_t end);

/* Compare `s1` and `s2` alphabetically.
 * Return 0 if `s1` and `s2` are alphabetically equal.
 * Return a negative value if `s1` is alphabetically less than `s2`.
 * Return a positive value if `s1` is alphabetically greater than `s2` */
size_t str8_cmp(str8 s1, str8 s2);

/* Compare at most `n` bytes of `s1` and `s2`.
 * Return 0 if `s1` and `s2` are alphabetically equal.
 * Return a negative value if `s1` is alphabetically less than `s2`.
 * Return a positive value if `s1` is alphabetically greater than `s2` */
size_t str8_ncmp(str8 s1, str8 s2, size_t n);

/* Return a pointer to the first occurance of `c` in `string`.
 * Returns NULL if not in the string. */
char *str8_chr(str8 s, char c);

/* Calculates the length (in bytes) of the initial segment of `s`
 * which consists entirely of bytes in `accept`. */
size_t str8_spn(str8 s, str8 accept);

/* Calculates the length of the initial segment of `s`
 * which consists entirely of bytes not in `reject`. */
size_t str8_cspn(str8 s, str8 reject);

#endif // !NKL_STR8_H
