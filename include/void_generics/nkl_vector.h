/*
 * void_generics/nkl_vector.h - Generic vector with void pointers
 *
 * This library provides generic vectors in C using void pointers.
 *
 * COMPILE TIME OPTIONS
 *
 *   #define NKL_FAST_MODE
 *
 *      This flag must be globally defined.
 *
 *      By default, vector functions will include index bound checking,
 *      NULL checks, and will zero the struct upon deinit. If this flag is
 *      defined, this functionality will not exist-- effectively an assertion
 *      that you will pass valid inputs.
 *
 *  #define NKL_SHORT_NAMES
 *
 *      By default, exposed functions will be qualified with the "nkl_" prefix.
 *      Define this flag if you wish to remove this prefix for shorter names.
 *      May cause name conflicts
 *
 *  #define NKL_ALLOC(count, size)
 *  #define NKL_REALLOC(count, size)
 *  #define NKL_FREE(ptr)
 *
 *      By default, these are set to use the standard C functions `malloc`,
 *      `realloc`, and `free`. You can override this by defining these with
 *      the functions you wish to use.
 *
 * NOTES
 *
 *   - Allocation is by default only done upon item insertion. If an initial
 *      capacity is specified, allocation will be done at init.
 */


/** DO NOT DEFINE THIS FLAG: IT IS FOR INTERNALS **/
#ifdef NKL_COMPILE_TIME_OPTIONS

/** INSERT ANY COMPILE TIME OPTIONS HERE **/



/** ------------------------------------ **/
#if (defined(NKL_ALLOC) && (!defined(NKL_REALLOC) || !defined(NKL_FREE))) ||   \
    (defined(NKL_REALLOC) && (!defined(NKL_ALLOC) || !defined(NKL_FREE))) ||   \
    (defined(NKL_FREE) && (!defined(NKL_ALLOC) || !defined(NKL_REALLOC)))
#error                                                                         \
    "You must define either all three of NKL_ALLOC, NKL_REALLOC, and NKL_FREE, or none of them."
#endif
#endif


#ifndef NKL_VOID_GENERIC_VECTOR_H
#define NKL_VOID_GENERIC_VECTOR_H 1

#if defined(NKL_SHORT_NAMES)

typedef struct NklVector Vector;
#define vec_init nkl_vec_init
#define vec_deinit nkl_vec_deinit
#define vec_append nkl_vec_append
#define vec_prepend nkl_vec_prepend
#define vec_index nkl_vec_index
#define vec_index_ref nkl_vec_index_ref
#define vec_index_alloc nkl_vec_index_alloc
#define vec_pop nkl_vec_pop
#define vec_pop_front nkl_vec_pop_front
#define vec_pop_back nkl_vec_pop_back
#define vec_pop_alloc nkl_vec_pop_alloc
#define vec_pop_front_alloc nkl_vec_pop_front_alloc
#define vec_pop_back_alloc nkl_vec_pop_back_alloc
#define vec_remove nkl_vec_remove
#define vec_insert nkl_vec_insert

#endif

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
