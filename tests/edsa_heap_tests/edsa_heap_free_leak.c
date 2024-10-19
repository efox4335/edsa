/*
tests for memory leak by address sanitizer
*/
#include "edsa.h"

int cmp_func(const void *const a, const void *const b)
{
	return *((char *) a) > *((char *) b);
}

int main(void)
{
	edsa_heap *heap;

	for(int i = 0; i < 1000; ++i){
		edsa_heap_init(&heap, 1, sizeof(char), cmp_func);

		edsa_heap_free(heap);
	}

	//adress sanitizer will cause test to fail if there is a memory leak
	return 0;
}
