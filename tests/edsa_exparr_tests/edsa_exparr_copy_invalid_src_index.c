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
	ret_val = edsa_exparr_copy(arr, 20, 30);

	if(ret_val != EDSA_EXPARR_COPY_INVALID_SRC_INDEX){
		edsa_get_error_string(ret_val, &fail_err);
		edsa_get_error_string(EDSA_EXPARR_COPY_INVALID_SRC_INDEX, &ret_str);
		printf("edsa_exparr_copy_invalid_src_index.c: edsa_exparr_copy failed to return %s instead returned %s\n",
		ret_str, fail_err);
		fflush(stdout);
		return 1;
	}

	edsa_exparr_free(arr);

	return 0;
}
