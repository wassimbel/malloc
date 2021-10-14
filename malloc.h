#ifndef _MALLOC_H_
#define _MALLOC_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define PAGESIZE sysconf(_SC_PAGESIZE)
#define align(offset, align) ((offset + (align - 1)) & -align)
#define PREV_FREE(x) (x & FLAG_FREE)
#define LAST_HEADER(x) (x & FLAG_LAST_HEADER)
#define CHAR_P(x) ((char *) x)
#define PREV_SIZE(x) (SIZET_P(x)[0])
#define CURR_SIZE(x) (SIZET_P(x)[1])
#define HEADERS (sizeof(size_t) * 2)
#define FLAG 0x1

void *naive_malloc(size_t size);
void _free(void *ptr);

#endif /* _MALLOC_H_ */
