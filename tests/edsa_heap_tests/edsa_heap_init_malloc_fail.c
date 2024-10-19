/*
uses ld_preload to overide glibc malloc with one that always returns NULL
*/
#include "edsa.h"

int cmp_func(const void *const a, const void *const b)
{
	return *((char *) a) > *((char *) b);
}

int main(void)
{
	edsa_heap *heap;
	size_t ret_val;

	ret_val = edsa_heap_init(&heap, 10, sizeof(char), cmp_func);

	if(ret_val == EDSA_HEAP_INIT_MALLOC_FAILED){
		return 0;
	}

	return 1;
}
