#include "edsa.h"

int cmp_func(const void *const a, const void *const b)
{
	return *((int *) a) > *((int *) b);
}

int main(void)
{
	edsa_heap *heap;
	size_t ret_val;

	ret_val = edsa_heap_init(&heap, 1, sizeof (int), cmp_func);

	if(ret_val == EDSA_SUCCESS){
		edsa_heap_free(heap);

		return 0;
	}
	edsa_heap_free(heap);

	return 1;
}
