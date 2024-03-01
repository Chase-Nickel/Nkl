#include <nkltypes.h>
#include <nklalloc.h>

/* \brief range8() returns an array of int8_t between
 *        start and stop (exclusive), step amount apart
 * @param a The arena where the array will be allocated
 * @param start The starting point of the numbers
 * @param stop The stopping point of the numbers
 * @param step The distance between each number in the array
 * @return Array of integers
 */
i8arr range8(Arena *a, int8_t start, int8_t stop, int8_t step) {
	i8arr arr = {0};
	if (start < stop || step < 1 || !a)
		return arr;

	arr.buf = ALLOC(a, (stop - start) / step, int8_t);
	if (!arr.buf)
		return arr;

	{
		int8_t *fill = arr.buf;
		for (size_t i = start; i < stop; i += step)
			*fill++ = i;
	}

	return arr;
}

/* \brief irange8() returns an array of int8_t between
 *        start and stop (inclusive), step amount apart
 * @param a The arena where the array will be allocated
 * @param start The starting point of the numbers
 * @param stop The stopping point of the numbers
 * @param step The distance between each number in the array
 * @return Array of integers
 */
i8arr irange8(Arena *a, int8_t start, int8_t stop, int8_t step) {
	i8arr arr = {0};
	if (start < stop || step < 1 || !a)
		return arr;

	arr.buf = ALLOC(a, stop - start + 1, int8_t);
	if (!arr.buf)
		return arr;

	{
		int8_t *fill = arr.buf;
		for (size_t i = start; i <= stop; i += step)
			*fill++ = i;
	}

	return arr;
}

