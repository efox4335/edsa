#include "edsa.h"
#include <stdio.h>

//tests if edsa_exparr_read prevents a buffer overflow
int main(void)
{
	edsa_exparr *arr;
	size_t ele_num = 10;
	size_t ret_val = 0;
	char temp = '\0';
	char *fail_err = NULL;
	char *ret_str = NULL;

	edsa_exparr_init(&arr, ele_num, sizeof(char));

	ret_val = edsa_exparr_read(arr, 10, &temp);

	if(ret_val != EDSA_EXPARR_READ_INVALID_INDEX){
		edsa_get_error_string(ret_val, &fail_err);
		edsa_get_error_string(EDSA_EXPARR_READ_INVALID_INDEX, &ret_str);
		printf("edsa_exparr_read_bounds.c: edsa_exparr_read failed to return %s instead returned %s on invalid index read\n",
		ret_str, fail_err);
		fflush(stdout);
		return 1;
	}

	edsa_exparr_free(arr);

	return 0;
}
