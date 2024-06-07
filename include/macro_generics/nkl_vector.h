#ifndef NKL_MACRO_GENERIC_VECTOR_H
#define NKL_MACRO_GENERIC_VECTOR_H 1

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define CREATE_VECTOR(type, name)                                              \
    struct name {                                                              \
        size_t len;                                                            \
        size_t cap;                                                            \
        typeof(type) *buf;                                                     \
    };                                                                         \
                                                                               \
    struct name Vec_init(size_t item_size, size_t init_length) {               \
        struct name new = {0};                                                 \
        if (init_length == 0) {                                                \
            return new;                                                        \
        }                                                                      \
        new.buf = malloc(init_length * sizeof(type));                          \
        if (new.buf) {                                                         \
            new.cap = init_length;                                             \
        }                                                                      \
        return new;                                                            \
    }                                                                          \
                                                                               \
    void Vec_deinit_s(struct name *vec) {                                      \
        vec->len = 0;                                                          \
        vec->cap = 0;                                                          \
        free(vec->buf);                                                        \
        vec->buf = NULL;                                                       \
    }                                                                          \
                                                                               \
    void Vec_deinit(struct name *vec) { free(vec->buf); }                      \
                                                                               \
    bool NKL_##name##_size_up(struct name *vec) {                              \
        if (vec->cap == SIZE_MAX / sizeof(type)) {                             \
            return true;                                                       \
        }                                                                      \
        if (vec->cap == 0) {                                                   \
            vec->cap = 1;                                                      \
        }                                                                      \
        size_t new_cap = (vec->cap >= SIZE_MAX / 2)                            \
                             ? (SIZE_MAX / sizeof(type)) * sizeof(type)        \
                             : vec->cap * 2;                                   \
        sizeof(type) *new_buf = realloc(vec->buf, new_cap * sizeof(type));     \
        if (!new_buf) {                                                        \
            return true;                                                       \
        }                                                                      \
        vec->buf = new_buf;                                                    \
        vec->cap = new_cap;                                                    \
        return false;                                                          \
    }                                                                          \
                                                                               \
    bool Vec_append(struct name *vec, typeof(type) data) {                     \
        if (vec->len >= vec->cap) {                                            \
            if (NKL_##name##_size_up(vec)) {                                   \
                return true;                                                   \
            }                                                                  \
        }                                                                      \
        vec->buf[vec->len] = data;                                             \
        vec->len += 1;                                                         \
        return false;                                                          \
    }                                                                          \
                                                                               \
    bool Vec_prepend(struct name *vec, typeof(type) data) {                    \
        if (vec->len >= vec->cap) {                                            \
            if (NKL_##name##_size_up(vec)) {                                   \
                return true;                                                   \
            }                                                                  \
        }                                                                      \
        memcpy(vec->buf + 1, vec->buf, vec->cap * sizeof(type));               \
        vec->buf[0] = data;                                                    \
        vec->len += 1;                                                         \
    }                                                                          \
                                                                               \
    bool Vec_index(struct name vec, size_t index, typeof(type) *out) {         \
        if (index >= vec.cap) {                                                \
            return true;                                                       \
        }                                                                      \
        *out = vec->buf[index];                                                \
        return false;                                                          \
    }                                                                          \
                                                                               \
    typeof(type) Vec_index_ref(struct name vec, size_t index);                 \
                                                                               \
    typeof(type) Vec_index_alloc(struct name vec, size_t index);               \
                                                                               \
    bool Vec_pop(struct name *vec, size_t index, typeof(type) out);            \
                                                                               \
    bool Vec_pop_front(struct name *vec, typeof(type) out);                    \
                                                                               \
    bool Vec_pop_back(struct name *vec, typeof(type) out);                     \
                                                                               \
    typeof(type) Vec_pop_alloc(struct name *vec, size_t index);                \
                                                                               \
    typeof(type) Vec_pop_front_alloc(struct name *vec);                        \
                                                                               \
    typeof(type) Vec_pop_back_alloc(struct name *vec);                         \
                                                                               \
    bool Vec_remove(struct name *vec, size_t index);                           \
                                                                               \
    bool Vec_insert(struct name *vec, typeof(type) data, size_t index);

#endif // !NKL_MACRO_GENERIC_VECTOR_H
