#include "edsa.h"
#include <stdio.h>

int main(void)
{
	edsa_htable *htable;
	size_t ret_val = 0;
	char *fail_err = NULL;
	char *ret_str = NULL;
	int key = 1;
	int data = 1;

	edsa_htable_init(&htable, sizeof(int), sizeof(int), 1);
	edsa_htable_ins(htable, &key, &data);
	ret_val = edsa_htable_remove(htable, &key);

	if(ret_val != EDSA_SUCCESS){
		edsa_get_error_string(ret_val, &fail_err);
		edsa_get_error_string(EDSA_SUCCESS, &ret_str);
		printf("edsa_htable_remove_success.c: edsa_htable_remove failed to return %s instead returned %s\n",
		ret_str, fail_err);
		fflush(stdout);
		edsa_htable_free(htable);
		return 1;
	}

	edsa_htable_free(htable);

	return 0;
}
