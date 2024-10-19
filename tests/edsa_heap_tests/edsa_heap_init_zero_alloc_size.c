#include "edsa.h"

int cmp_func(const void *const a, const void *const b)
{
	return *((int *) a) > *((int *) b);
}

int main(void)
{
	edsa_heap *heap;
	size_t ret_val;

	ret_val = edsa_heap_init(&heap, (size_t) 0, sizeof (int), cmp_func);

	if(ret_val == EDSA_HEAP_INIT_ZERO_ALLOC_SIZE){
		return 0;
	}

	return 1;
}
