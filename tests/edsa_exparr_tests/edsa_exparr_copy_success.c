#include "edsa.h"
#include <stdio.h>

int main(void)
{
	edsa_exparr *arr;
	size_t ele_num = 10;
	size_t ret_val = 0;
	char temp = '\0';
	char *fail_err = NULL;
	char *ret_str = NULL;

	edsa_exparr_init(&arr, ele_num, sizeof(char));
	edsa_exparr_ins(arr, 0, &temp);
	ret_val = edsa_exparr_copy(arr, 0, 30);

	if(ret_val != EDSA_SUCCESS){
		edsa_get_error_string(ret_val, &fail_err);
		edsa_get_error_string(EDSA_SUCCESS, &ret_str);
		printf("edsa_exparr_copy_success.c: edsa_exparr_copy failed to return %s instead returned %s\n",
		ret_str, fail_err);
		fflush(stdout);
		return 1;
	}

	edsa_exparr_free(arr);

	return 0;
}
