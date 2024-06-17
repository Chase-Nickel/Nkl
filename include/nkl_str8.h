#ifndef NKL_STR8_H
#define NKL_STR8_H 1

#include <nkl_arena.h>
#include <nkl_str8_def.h>
#include <stddef.h>

/* Return an allocated str8 with the same buffer & length of `s` */
str8 str8_dup(Arena *arena, const str8 s);

/* Return an allocated str8 with the same `n` bytes of the buffer of `s`. */
str8 str8_ndup(Arena *arena, const str8 s, size_t n);

/* Return a sub-string of `s` from `start` to `end` exclusive */
str8 str8_substr(const str8 s, size_t start, size_t end);

/* Return an allocated sub-string of `s` from `start` to `end` exclusive */
str8 str8_substr_alloc(Arena *arena, const str8 s, size_t start, size_t end);

/* Compare `s1` and `s2` alphabetically.
 * Return 0 if `s1` and `s2` are alphabetically equal.
 * Return -1 if `s1` is alphabetically less than `s2`.
 * Return 1 if `s1` is alphabetically greater than `s2` */
int str8_cmp(const str8 s1, const str8 s2);

/* Compare at most `n` bytes of `s1` and `s2` alphabetically.
 * Return 0 if `s1` and `s2` are alphabetically equal.
 * Return -1 if `s1` is alphabetically less than `s2`.
 * Return 1 if `s1` is alphabetically greater than `s2` */
int str8_ncmp(const str8 s1, const str8 s2, size_t n);

/* Return the index of the first occurrence of `c` in `string`.
 * Returns the length of the string if the character does not appear. */
size_t str8_find(const str8 s, char c);

/* Calculates the length of the initial segment of `s`
 * which consists entirely of bytes in `accept`. */
size_t str8_spn(const str8 s, const str8 accept);

/* Calculates the length of the initial segment of `s`
 * which consists entirely of bytes not in `reject`. */
size_t str8_cspn(const str8 s, const str8 reject);

#endif // !NKL_STR8_H
