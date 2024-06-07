#ifndef NKL_HASHMAP_H
#define NKL_HASHMAP_H

#include <stddef.h>

typedef struct NklHashmap NklHashmap;
struct NklHashmap {
    void *buf;
    size_t value_size;
    size_t cap;
    size_t filled;

    size_t (*hash)(void *key);
};

#endif
