/*
 - checks for both the index being to large and the ammount of bits being to large
*/
#include "edsa.h"
#include <stdio.h>

struct multi_byte_struct{
	char a[4];
};

int main(void)
{
	edsa_exparr *arr;
	size_t ele_num = 10;
	size_t ret_val = 0;
	char *fail_err = NULL;
	char *ret_str = NULL;

	struct multi_byte_struct temp;
	temp.a[0] = 'a';
	temp.a[1] = 'b';
	temp.a[2] = 'c';
	temp.a[3] = 'd';

	edsa_exparr_init(&arr, ele_num, sizeof(struct multi_byte_struct));

	edsa_exparr_ins(arr, 0, &temp);

	ret_val = edsa_exparr_copy(arr, 0, (size_t) -1);

	if(ret_val != EDSA_EXPARR_COPY_INVALID_DEST_INDEX){
		edsa_get_error_string(ret_val, &fail_err);
		edsa_get_error_string(EDSA_EXPARR_COPY_INVALID_DEST_INDEX, &ret_str);
		printf("edsa_exparr_copy_invalid_dest_index.c: edsa_exparr_copy failed to return %s instead returned %s\n",
		ret_str, fail_err);
		fflush(stdout);
		return 1;
	}

	ret_val = edsa_exparr_copy(arr, 0, ((size_t) -1) / 2);

	if(ret_val != EDSA_EXPARR_COPY_INVALID_DEST_INDEX){
		edsa_get_error_string(ret_val, &fail_err);
		edsa_get_error_string(EDSA_EXPARR_COPY_INVALID_DEST_INDEX, &ret_str);
		printf("edsa_exparr_copy_invalid_dest_index.c: edsa_exparr_copy failed to return %s instead returned %s\n",
		ret_str, fail_err);
		fflush(stdout);
		return 1;
	}

	edsa_exparr_free(arr);

	return 0;
}
