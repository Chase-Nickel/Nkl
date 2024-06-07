#include <stdio.h>
#include <stdlib.h>

[[noreturn]]
void nkl_assert_failed(const char *file, int line) {
    fprintf(stderr, "Assertion failed. %s:%d\n", file, line);
    for(;;) {
        exit(1);
    }
}

