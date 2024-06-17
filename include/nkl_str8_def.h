#ifndef NKL_STR8_DEF_H
#define NKL_STR8_DEF_H 1

#include <stddef.h>

typedef struct str8 str8;
struct str8 {
    char *buf;
    size_t len;
};

// Convert a string literal into str8
#define STR8(s)                                                                \
    (const str8) { s, sizeof s - 1 }

#endif // !NKL_STR8_DEF_H
