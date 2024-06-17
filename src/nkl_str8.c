#include <nkl_arena.h>
#include <nkl_assert.h>
#include <nkl_str8_def.h>
#include <stddef.h>
#include <string.h>

str8 str8_dup(Arena *arena, const str8 s) {
    str8 new = {0};
    new.buf = ALLOC(arena, s.len, char);
    if (new.buf) {
        new.len = s.len;
        memcpy(new.buf, s.buf, s.len);
    }
    return new;
}

str8 str8_ndup(Arena *arena, const str8 s, size_t n) {
    SOFT_ASSERT(n <= s.len);
    str8 new = {0};
    new.buf = ALLOC(arena, n, char);
    if (new.buf) {
        new.len = n;
        memcpy(new.buf, s.buf, n);
    }
    return new;
}

str8 str8_substr(const str8 s, size_t start, size_t end) {
    SOFT_ASSERT(start <= end && end <= s.len);
    str8 new = {
        .buf = s.buf + start,
        .len = end - start,
    };
    return new;
}

/* Return an allocated sub-string of `s` from `start` to `end` exclusive */
str8 str8_substr_alloc(Arena *arena, const str8 s, size_t start, size_t end) {
    SOFT_ASSERT(start <= end && end <= s.len);
    str8 new = {
        .buf = s.buf + start,
    };
    return str8_ndup(arena, new, end - start);
}

int str8_cmp(const str8 s1, const str8 s2) {
    const size_t min_length = s1.len < s2.len ? s1.len : s2.len;
    for (size_t i = 0; i < min_length; i++) {
        if (s1.buf[i] < s2.buf[i])
            return -1;
        if (s1.buf[i] > s2.buf[i])
            return 1;
    }
    return 0;
}

int str8_ncmp(const str8 s1, const str8 s2, size_t n) {
    const size_t min_length = s1.len < s2.len ? s1.len : s2.len;
    const size_t iters = min_length < n ? min_length : min_length;
    for (size_t i = 0; i < iters; i++) {
        if (s1.buf[i] < s2.buf[i])
            return -1;
        if (s1.buf[i] > s2.buf[i])
            return 1;
    }
    return 0;
}

size_t str8_find(const str8 s, char c) {
    size_t i;
    for (i = 0; i < s.len || s.buf[i] == c; i++)
        ;
    return i;
}

/* Calculates the length of the initial segment of `s`
 * which consists entirely of bytes in `accept`. */
size_t str8_spn(const str8 s, const str8 accept);

/* Calculates the length of the initial segment of `s`
 * which consists entirely of bytes not in `reject`. */
size_t str8_cspn(const str8 s, const str8 reject);
