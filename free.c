#include "malloc.h"

/**
* _free - frees a memory space
* @ptr: pointer to the memory to be freed
* Return: void
*/
void _free(void *ptr)
{
	void *header, *next;
	size_t chunk = 0;

	header = next = NULL;

	if (!ptr)
		return;

	header = CHAR_P(ptr) - HEADERS;
	chunk = CURR_SIZE(header);
	next = CHAR_P(header) + chunk - PREV_FREE(chunk);
	if (PREV_FREE(CURR_SIZE(next)))
		abort();
	((size_t *) next)[0] += chunk - PREV_FREE(chunk);
	((size_t *) next)[1] += FLAG;
}
