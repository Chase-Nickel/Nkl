#ifndef NKL_VOID_GENERIC_VECTOR_H
#define NKL_VOID_GENERIC_VECTOR_H 1

/*
 * TODO:
 *   - Better docstrings
 */

#include <stdbool.h>
#include <stddef.h>

struct Vector {
    size_t len;
    size_t cap;
    size_t item_size;
    void *buf;
};

// Initialize a vector with an item size and an initial length
// Will not allocate if init_length == 0
struct Vector Vec_init(size_t item_size, size_t init_length);
#define VEC_INIT(type) Vec_init(sizeof(type), 0)

// Deinitialize a vector
// Will:
//   - Free the buffer and set it to NULL
//   - Set length & capacity to 0
void Vec_deinit_s(struct Vector *vec);

// Deinitialize a vector
// Will:
//   - Free the buffer
void Vec_deinit(struct Vector *vec);

// Append an item to a vector
bool Vec_append(struct Vector *vec, const void *data);

// Prepend an item to a vector
bool Vec_prepend(struct Vector *vec, const void *data);

// Index a vector
// Store the data in out
// Return true if index out of bounds
bool Vec_index(struct Vector vec, size_t index, void *out);

// Index a vector
// Return a pointer to the data in the buffer
// Return NULL if index out of bounds
void *Vec_index_ref(struct Vector vec, size_t index);

// Index a vector
// Returns an allocated pointer with the data
// Return NULL if index out of bounds or allocation failed
void *Vec_index_alloc(struct Vector vec, size_t index);

// Remove an item at index from a vector
// Copy the removed item into out
bool Vec_pop(struct Vector *vec, size_t index, void *out);

// Remove an item from the front of a vector
// Copy the removed item into out
bool Vec_pop_front(struct Vector *vec, void *out);

// Remove an item from the back of a vector
// Copy the removed item into out
bool Vec_pop_back(struct Vector *vec, void *out);

// Remove an item at index from a vector
// Return an allocated pointer containing the removed data
void *Vec_pop_alloc(struct Vector *vec, size_t index);

// Remove an item from the front of a vector
// Return an allocated pointer containing the removed data
void *Vec_pop_front_alloc(struct Vector *vec);

// Remove an item from the back of a vector
// Return an allocated pointer containing the removed data
void *Vec_pop_back_alloc(struct Vector *vec);

// Remove an item at index from a vector
bool Vec_remove(struct Vector *vec, size_t index);

// Insert an item at index into a vector
bool Vec_insert(struct Vector *vec, const void *data, size_t index);

#define VEC_PRINT_TEMPLATE(type, name, format)                                 \
    void name(struct Vector vec) {                                             \
        printf("< ");                                                          \
        for (size_t i = 0; i < vec.len; i++) {                                 \
            typeof(type) item;                                                 \
            Vec_index(vec, i, &item);                                          \
            printf(format, item);                                              \
            printf(" ");                                                       \
        }                                                                      \
        puts(">");                                                             \
    }

#endif // !NKL_VOID_GENERIC_VECTOR_H
