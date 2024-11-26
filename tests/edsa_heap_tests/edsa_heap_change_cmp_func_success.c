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
	size_t ret_val = 0;
	char *fail_err = NULL;
	char *ret_str = NULL;
	edsa_heap *heap;

	edsa_heap_init(&heap, 1, sizeof (int), cmp_func_1);
	ret_val = edsa_heap_change_cmp_func(heap, cmp_func_2);

	if(ret_val != EDSA_SUCCESS){
		edsa_get_error_string(ret_val, &fail_err);
		edsa_get_error_string(EDSA_SUCCESS, &ret_str);
		printf("edsa_heap_change_cmp_func_success.c: edsa_heap_change_cmp_func failed to return %s instead returned %s\n",
		ret_str, fail_err);
		fflush(stdout);
		edsa_heap_free(heap);
		return 1;
	}

	edsa_heap_free(heap);

	return 0;
}
