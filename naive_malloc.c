#include "malloc.h"

/**
 * unallocated_memory - checks for unallocated memory
 * @heap_start: pointer to heap start
 * @malloc_calls: number of calls to malloc
 * Return: void
 */

void *unallocated_memory(char *heap_start, size_t malloc_calls)
{
	while (malloc_calls > 0)
	{
		heap_start += *(size_t *)heap_start;
		--malloc_calls;
	}
	return (heap_start);
}

/**
 * extend_memory - extends memory using sbrk()
 * @chunk_size: size of chunk
 * @garbage: garbage memory
 * Return: void
 */

void *extend_memory(size_t chunk_size, size_t *garbage)
{
	void *chunk;

	chunk = sbrk(align(chunk_size, sysconf(_SC_PAGESIZE)));
	if (chunk == (void *) -1)
		return (NULL);
	*garbage += align(chunk_size, sysconf(_SC_PAGESIZE));
	return (chunk);
}

/**
 * headers - set headers
 * @chunk: pointer to start of chunk
 * @chunk_size: size of the chunk
 * @garbage: poingter to garbage memory
 * Return: void
 */
void headers(char *chunk, size_t chunk_size, size_t *garbage)
{
	*garbage -= chunk_size;
	*(size_t *)chunk = chunk_size;
	*(size_t *)(chunk + *(size_t *)chunk) = *garbage;
}

/**
 * naive_malloc - allocates memory dynamically
 * @size: size needed to be allocated for the user
 * Return: void
 **/
void *naive_malloc(size_t size)
{
	size_t chunk_size, headers_size, garbage;
	void *chunk;
	static void *heap_start;
	static size_t malloc_calls;

	headers_size = sizeof(size_t);
	chunk_size = align(size, sizeof(void *)) + headers_size;
	if (!heap_start)
	{
		garbage = 0;
		heap_start = chunk = extend_memory(chunk_size, &garbage);
		if (!chunk)
			return (NULL);
	}
	else
	{
		chunk = unallocated_memory(heap_start, malloc_calls);
		garbage = *(size_t *)chunk;
		if (garbage < chunk_size + headers_size)
			if (!extend_memory(chunk_size, &garbage))
				return (NULL);
	}
	headers(chunk, chunk_size, &garbage);
	++malloc_calls;
	return ((char *)chunk + headers_size);
}
