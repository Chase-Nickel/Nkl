#ifndef __TYPES_H
#define __TYPES_H 1

#ifndef NULL
#define NULL ((void *)0)
#endif

/* TODO: make more portable. Check different archictectures and define based on that. #error on no standard found
 */
#if __STDC_VERSION__ < 199901L
/* C89 */
#error "Define your own standard types losser"
#else
/* C99 and up */
#include <stdint.h>
#include <stddef.h>
#endif

typedef int8_t result_t;

typedef struct str8_t str8_t;
struct str8_t {
  char   *buf;
  int32_t len;
};

typedef struct str16_t str16_t;
struct str16_t {
  int16_t *buf;
  int32_t  len;
};

typedef struct str32_t str32_t;
struct str32_t {
  int32_t *buf;
  int32_t  len;
};

typedef struct i8arr i8arr;
struct i8arr {
	int8_t *buf;
	int32_t size;
};

typedef struct i16arr i16arr;
struct i16arr {
	int16_t *buf;
	int32_t size;
};

typedef struct i32arr i32arr;
struct i32arr {
	int32_t *buf;
	int32_t size;
};

typedef struct u8arr u8arr;
struct u8arr {
	uint8_t *buf;
	int32_t size;
};

typedef struct u16arr u16arr;
struct u16arr {
	uint16_t *buf;
	int32_t size;
};

typedef struct u32arr u32arr;
struct u32arr {
	uint32_t *buf;
	int32_t size;
};

#if __STDC_VERSION__ < 199901L
/* c89 requires constant initializers */
extern str8_t _nkl_str8_make(const char *s, const int32_t size);
#define STR8(s) _nkl_str8_make(s, (int32_t)(sizeof(s) - 1))
#else
#define STR8(s) ((str8_t) {s, (int32_t)(sizeof(s) - 1)})
#endif

#endif

