#ifndef __NKL_MEM_H
#define __NKL_MEM_H 1

#include <nkltypes.h>

/**
 * \brief The xmemcpy() function copies n bytes from
 *        memory area src to memory area dest.
 *        The memory areas must not overlap.
 * @see xmemmove() if the memory areas overlap
 * @param dst Destination pointer for bytes to be copied
 * @param src Source pointer for bytes to be copied from
 * @param n Count of bytes to copy from src to dst
 * @return The destination pointer
 */
extern void *xmemcpy(void *dst, void *src, ptrdiff_t n);

/**
 * \brief The xmemmove() function copies n bytes from
 *        memory area src to memory area dest.
 *        The memory areas may overlap
 * @param dst Destination pointer for bytes to be copied
 * @param src Source pointer for bytes to be copied from
 * @param n Count of bytes to copy from src to dst
 * @return The destination pointer
 */
extern void *xmemmove(void *dst, void *src, ptrdiff_t n);

/**
 * \brief The xmemset() function fills the first n bytes of the
 *        memory area pointed to by s with the constant byte c.
 * @param dst Destination pointer for bytes to be set
 * @param c Value to be set
 * @param n Count of bytes to be set at dst
 * @return The destination pointer
 */
extern void *xmemset(void *dst, int8_t c, ptrdiff_t n);

#endif

