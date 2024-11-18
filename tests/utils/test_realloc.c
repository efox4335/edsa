/*
 - a version of realloc that always returns NULL for testing realloc fail
*/
#include <stddef.h>

void *realloc(void *ptr, size_t size)
{
	return NULL;
}
