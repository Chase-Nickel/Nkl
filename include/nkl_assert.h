#ifndef NKL_ASSERT_H
#define NKL_ASSERT_H

/*
 * This header provides macros for assertion of conditions.
 *
 * SOFT_ASSERT(expr)
 *
 *    Assert that expr is true. If false, the program will exit with the file
 *    and line number upon which the assertion failed.
 *    This macro will result in an empty expression if the macro NDEBUG is
 *    defined before including this header. Use SOFT_ASSERT for conditions that
 *    may help debugging but should not appear in a release.
 *
 * HARD_ASSERT(expr)
 *
 *    Assert that expr is true. If false, the program will exit with the file
 *    and line number upon which the assertion failed.
 *    This macro will always check the assertion and will not be stripped. Use
 *    this for hard error states which should never be removed from the program.
 */

[[noreturn]]
extern void nkl_assert_failed(const char *file, int line);

#ifdef NDEBUG
#define SOFT_ASSERT(expr)
#else
#define SOFT_ASSERT(expr)                                                      \
    if (!(expr))                                                               \
    nkl_assert_failed(__FILE__, __LINE__)
#endif

#define HARD_ASSERT(expr)                                                      \
    if (!(expr))                                                               \
    nkl_assert_failed(__FILE__, __LINE__)

#endif // !NKL_ASSERT_H
