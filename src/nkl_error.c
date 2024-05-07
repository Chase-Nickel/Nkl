#include <nkl_str8_def.h>
#include <stdio.h>
#include <stdlib.h>

void error_oom(str8 msg) {
	fprintf(stderr, "ERROR OOM: %.*s", (int)msg.len, msg.buf);
	exit(-1);
}

