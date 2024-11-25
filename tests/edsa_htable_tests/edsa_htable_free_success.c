#include "edsa.h"
#include <stdio.h>

int main(void)
{
	edsa_htable *htable;
	size_t ret_val = 0;
	char *fail_err = NULL;
	char *ret_str = NULL;

	edsa_htable_init(&htable, sizeof(int), sizeof(int), 1);
	ret_val = edsa_htable_free(htable);

	if(ret_val != EDSA_SUCCESS){
		edsa_get_error_string(ret_val, &fail_err);
		edsa_get_error_string(EDSA_SUCCESS, &ret_str);
		printf("edsa_htable_free_success.c: edsa_htable_free failed to return %s instead returned %s\n",
		ret_str, fail_err);
		fflush(stdout);
		return 1;
	}



	return 0;
}
