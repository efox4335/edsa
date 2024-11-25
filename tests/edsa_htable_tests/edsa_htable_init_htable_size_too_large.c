#include "edsa.h"
#include <stdio.h>

int main(void)
{
	edsa_htable *htable;
	size_t ret_val = 0;
	char *fail_err = NULL;
	char *ret_str = NULL;

	ret_val = edsa_htable_init(&htable, sizeof(int), sizeof(int), (size_t) -1);

	if(ret_val != EDSA_HTABLE_INIT_HTABLE_SIZE_TOO_LARGE){
		edsa_get_error_string(ret_val, &fail_err);
		edsa_get_error_string(EDSA_HTABLE_INIT_HTABLE_SIZE_TOO_LARGE, &ret_str);
		printf("edsa_htable_init_htable_size_too_large.c: edsa_htable_init failed to return %s instead returned %s\n",
		ret_str, fail_err);
		fflush(stdout);
		return 1;
	}

	return 0;
}
