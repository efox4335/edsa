/*
a version of malloc that always returns NULL for testing malloc fail
*/
#include <stddef.h>

void *malloc(size_t size)
{
	return NULL;
}
