#ifndef NKL_STR8_DEF_H
#define NKL_STR8_DEF_H 1

#include <stddef.h>

typedef struct str8 str8;
struct str8 {
    char *buf;
    size_t len;
};

#if defined(__STDC_VERSION__) && __STDC_VERSION__ < 199901L
str8 str8_make(const char *buf, size_t len);
#define STR8(s) str8_make(s, sizeof s - 1)
#else
#define STR8(s) (str8){s, sizeof s - 1}
#endif

#endif // !NKL_STR8_DEF_H
