#include <nkltypes.h>
#include <stdio.h>
#include <stdlib.h>

void error_oom(const str8_t msg) {
	fprintf(stderr, "ERROR OOM: %.*s", msg.len, msg.buf);
	exit(-1);
}

