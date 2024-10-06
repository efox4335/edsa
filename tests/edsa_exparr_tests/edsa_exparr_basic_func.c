#include "../../src/edsa.h"
#include <stdio.h>

//test only if the return val correct
//fflush needed because print may not happen if address sanitizer detects leaks
int main(void)
{
	edsa_exparr *arr;
	size_t val = 0xaaaaaaa;
	size_t ret_val;
	char *fail_err = NULL;
	char *ret_str = NULL;

	ret_val = edsa_exparr_init(&arr, 20, sizeof(size_t));

	if(ret_val != EDSA_SUCCESS){
		edsa_get_error_string(ret_val, &fail_err);
		edsa_get_error_string(EDSA_SUCCESS, &ret_str);
		printf("edsa_exparr_basic_func.c: edsa_exparr_init failed to return %s instead returned %s\n",
		ret_str, fail_err);
		fflush(stdout);
		return 1;
	}

	ret_val = edsa_exparr_free(arr);

	if(ret_val != EDSA_SUCCESS){
		edsa_get_error_string(ret_val, &fail_err);
		edsa_get_error_string(EDSA_SUCCESS, &ret_str);
		printf("edsa_exparr_basic_func.c: edsa_exparr_free failed to return %s instead returned %s\n",
		ret_str, fail_err);
		fflush(stdout);
		return 1;
	}

	return 0;
}
