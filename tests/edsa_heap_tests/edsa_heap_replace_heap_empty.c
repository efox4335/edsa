#include "edsa.h"
#include <stdio.h>

int cmp_func(const void *const a, const void *const b)
{
	return *((int *) a) > *((int *) b);
}

int main(void)
{
	size_t ret_val = 0;
	char *fail_err = NULL;
	char *ret_str = NULL;
	edsa_heap *heap;
	int data_1 = 1;
	int data_2 = 2;

	edsa_heap_init(&heap, 1, sizeof (int), cmp_func);
	ret_val = edsa_heap_replace(heap, &data_2, &data_1);

	if(ret_val != EDSA_HEAP_REPLACE_HEAP_EMPTY){
		edsa_get_error_string(ret_val, &fail_err);
		edsa_get_error_string(EDSA_HEAP_REPLACE_HEAP_EMPTY, &ret_str);
		printf("edsa_heap_replace_heap_empty.c: edsa_heap_replace failed to return %s instead returned %s\n",
		ret_str, fail_err);
		fflush(stdout);
		edsa_heap_free(heap);
		return 1;
	}

	edsa_heap_free(heap);

	return 0;
}
