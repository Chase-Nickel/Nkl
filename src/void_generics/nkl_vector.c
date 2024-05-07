#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <void_generics/nkl_vector.h>

typedef struct Vector Vector;

Vector Vec_init(size_t item_size, size_t init_length) {
    Vector vec = {
        .item_size = item_size,
    };
    if (init_length == 0) {
        return vec;
    }
    vec.buf = malloc(init_length * item_size);
    if (vec.buf) {
        vec.cap = init_length;
    };
    return vec;
}

void Vec_deinit(Vector *vec) {
    if (!vec) {
        return;
    }
    free(vec->buf);
}

void Vec_deinit_s(Vector *vec) {
    if (!vec) {
        return;
    }
    vec->len = 0;
    vec->cap = 0;
    free(vec->buf);
    vec->buf = NULL;
}

// Do not pass NULL
static bool size_up(Vector *vec) {
    if (vec->cap >= SIZE_MAX / vec->item_size) {
        return true;
    }
    size_t new_size = 0;
    if (vec->cap == 0) {
        vec->buf = malloc(2 * vec->item_size);
        if (!vec->buf) {
            return true;
        }
        vec->cap = 2;
        return false;
    }
    if (vec->cap >= SIZE_MAX / 2) {
        new_size = (SIZE_MAX / vec->item_size) * vec->item_size;
    } else {
        new_size = vec->cap * 2;
    }
    void *buf_new = realloc(vec->buf, new_size * vec->item_size);
    if (!buf_new) {
        return true;
    }
    vec->cap = new_size;
    vec->buf = buf_new;
    return false;
}

bool Vec_append(Vector *vec, const void *data) {
    if (!vec) {
        return true;
    }
    if (vec->len >= vec->cap) {
        if (size_up(vec)) {
            return true;
        }
    }
    size_t offset = vec->len * vec->item_size;
    memcpy((char *)vec->buf + offset, data, vec->item_size);
    vec->len += 1;
    return false;
}

bool Vec_prepend(Vector *vec, const void *data) {
    if (!vec) {
        return true;
    }
    if (vec->len >= vec->cap) {
        if (size_up(vec)) {
            return true;
        }
    }
    memmove((char *)vec->buf + vec->item_size, vec->buf, vec->item_size);
    memcpy(vec->buf, data, vec->item_size);
    vec->len += 1;
    return false;
}

bool Vec_index(Vector vec, size_t index, void *out) {
    if (index >= vec.len) {
        return true;
    }
    size_t offset = index * vec.item_size;
    memcpy(out, (char *)vec.buf + offset, vec.item_size);
    return false;
}

void *Vec_index_ref(Vector vec, size_t index) {
    if (index >= vec.len) {
        return NULL;
    }
    size_t offset = index * vec.item_size;
    return (char *)vec.buf + offset;
}

void *Vec_index_alloc(Vector vec, size_t index) {
    if (index >= vec.len) {
        return NULL;
    }
    void *out = malloc(vec.item_size);
    if (!out) {
        return NULL;
    }
    size_t offset = index * vec.item_size;
    return memcpy(out, (char *)vec.buf + offset, vec.item_size);
}

bool Vec_pop(struct Vector *vec, size_t index, void *out) {
    if (!vec || index >= vec->len) {
        return true;
    }
    char *buf = vec->buf;
    size_t offset = index * vec->item_size;
    memcpy(out, buf + offset, vec->item_size);
    vec->len -= 1;
    if (index == vec->len) {
        return false;
    }
    size_t offset_right = (index + 1) * vec->item_size;
    size_t right_block = (vec->len - index) * vec->item_size;
    memmove(buf + offset, buf + offset_right, right_block);
    return false;
}

bool Vec_pop_front(struct Vector *vec, void *out) {
    if (!vec || vec->len == 0) {
        return true;
    }
    memcpy(out, vec->buf, vec->item_size);
    vec->len -= 1;
    if (vec->len == 0) {
        return false;
    }
    size_t right_block = vec->len * vec->item_size;
    memmove(vec->buf, (char *)vec->buf + vec->item_size, right_block);
    return false;
}

bool Vec_pop_back(struct Vector *vec, void *out) {
    if (!vec || vec->len == 0) {
        return true;
    }
    size_t offset = (vec->len - 1) * vec->item_size;
    memcpy(out, (char *)vec->buf + offset, vec->item_size);
    vec->len -= 1;
    return false;
}

void *Vec_pop_alloc(struct Vector *vec, size_t index) {
    if (!vec || index >= vec->len) {
        return NULL;
    }
    void *out = malloc(vec->item_size);
    if (!out) {
        return NULL;
    }
    char *buf = vec->buf;
    size_t offset = index * vec->item_size;
    memcpy(out, buf + offset, vec->item_size);
    vec->len -= 1;
    if (index == vec->len) {
        return out;
    }
    size_t offset_right = (index + 1) * vec->item_size;
    size_t right_block = (vec->len - index) * vec->item_size;
    memmove(buf + offset, buf + offset_right, right_block);
    return out;
}

void *Vec_pop_front_alloc(struct Vector *vec) {
    if (!vec || vec->len == 0) {
        return NULL;
    }
    void *out = malloc(vec->item_size);
    if (!out) {
        return NULL;
    }
    memcpy(out, vec->buf, vec->item_size);
    vec->len -= 1;
    if (vec->len == 0) {
        return out;
    }
    size_t right_block = vec->len * vec->item_size;
    memmove(vec->buf, (char *)vec->buf + vec->item_size, right_block);
    return out;
}

void *Vec_pop_back_alloc(struct Vector *vec) {
    if (!vec || vec->len == 0) {
        return NULL;
    }
    void *out = malloc(vec->item_size);
    if (!out) {
        return NULL;
    }
    size_t offset = (vec->len - 1) * vec->item_size;
    memcpy(out, (char *)vec->buf + offset, vec->item_size);
    vec->len -= 1;
    return out;
}

bool Vec_remove(struct Vector *vec, size_t index) {
    if (!vec || index >= vec->len) {
        return true;
    }
    vec->len -= 1;
    if (index == vec->len) {
        return false;
    }
    char *buf = vec->buf;
    size_t offset = index * vec->item_size;
    size_t offset_right = (index + 1) * vec->item_size;
    size_t right_block = (vec->len - index) * vec->item_size;
    memmove(buf + offset, buf + offset_right, right_block);
    return false;
}

bool Vec_insert(struct Vector *vec, const void *data, size_t index) {
    if (!vec || index > vec->len) {
        return true;
    }
    if (vec->len >= vec->cap) {
        if (size_up(vec)) {
            return true;
        }
    }
    char *buf = vec->buf;
    size_t offset = index * vec->item_size;
    if (index < vec->len) {
        size_t offset_right = (index + 1) * vec->item_size;
        size_t right_block = (vec->len - index) * vec->item_size;
        memmove(buf + offset_right, buf + offset, right_block);
    }
    memcpy(buf + offset, data, vec->item_size);
    vec->len += 1;
    return false;
}
