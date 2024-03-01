#include <nkltypes.h>

void *xmemcpy(void *dst, void *src, ptrdiff_t n) {
	char *dst_b = (char *)dst;
	char *src_b = (char *)src;

	if (n <= 0)
		return dst;

	while (n--)
		*dst_b++ = *src_b++;
	return dst;
}

void *xmemmove(void *dst, void *src, ptrdiff_t n) {
	char *dst_b = (char *)dst;
	char *src_b = (char *)src;

	if (n <= 0)
		return NULL;

	/* Since we are copying byte by byte, we don't need to worry about overlap */
	while (n--)
		*dst_b++ = *src_b++;

	return dst;
}

void *xmemset(void *dst, int8_t c, ptrdiff_t n) {
	char *dst_b = (char *)dst;

	if (n <= 0)
		return dst;

	while (n--)
		*dst_b++ = c;

	return dst;
}

