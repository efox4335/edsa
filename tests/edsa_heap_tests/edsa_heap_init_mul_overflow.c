#include "edsa.h"

int cmp_func(const void *const a, const void *const b)
{
	return *((int *) a) > *((int *) b);
}

int main(void)
{
	edsa_heap *heap;
	size_t ret_val;

	size_t max_val = ~((size_t) 0);

	ret_val = edsa_heap_init(&heap, max_val, sizeof (int), cmp_func);

	if(ret_val == EDSA_HEAP_INIT_MULTIPLICATION_OVERFLOW){
		return 0;
	}

	return 1;
}
