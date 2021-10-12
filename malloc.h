#ifndef _MALLOC_H_
#define _MALLOC_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define PAGESIZE sysconf(_SC_PAGESIZE)
#define align(offset, align) ((offset + (align - 1)) & -align)

void *naive_malloc(size_t size);

#endif /* _MALLOC_H_ */
