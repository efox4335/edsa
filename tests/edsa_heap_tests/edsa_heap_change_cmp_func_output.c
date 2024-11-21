#include "edsa.h"
#include <stdio.h>

int cmp_func_1(const void *const a, const void *const b)
{
	return *((int *) a) > *((int *) b);
}

int cmp_func_2(const void *const a, const void *const b)
{
	return *((int *) a) > *((int *) b);
}

int main(void)
{
	size_t ele_num = 10;
	size_t ret_val = 0;
	char *fail_err = NULL;
	char *ret_str = NULL;
	edsa_heap *heap;

	edsa_heap_init(&heap, 1, sizeof (int), cmp_func_1);
	ret_val = edsa_heap_change_cmp_func(heap, cmp_func_2);

	if(heap->cmp_func != cmp_func_2){
		printf("edsa_heap_change_cmp_func_output.c: edsa_heap_change_cmp_func did not change the comparison function\n");
		edsa_heap_free(heap);

		return 1;
	}

	edsa_heap_free(heap);

	return 0;
}
