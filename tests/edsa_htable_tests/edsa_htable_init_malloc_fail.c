/*
 - uses ldpreload to overide stdlib realloc with one that always returns null
*/
#include "edsa.h"
#include <stdio.h>

int main(void)
{
	edsa_htable *htable;
	size_t ret_val = 0;
	char *fail_err = NULL;
	char *ret_str = NULL;

	ret_val = edsa_htable_init(&htable, sizeof(int), sizeof(int), 1);

	if(ret_val != EDSA_HTABLE_INIT_MALLOC_FAIL){
		edsa_get_error_string(ret_val, &fail_err);
		edsa_get_error_string(EDSA_HTABLE_INIT_MALLOC_FAIL, &ret_str);
		printf("edsa_htable_init_malloc_fail.c: edsa_htable_init failed to return %s instead returned %s\n",
		ret_str, fail_err);
		fflush(stdout);
		return 1;
	}

	return 0;
}
