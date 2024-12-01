#include "edsa.h"
#include <stdio.h>

int cmp_func(const void *ele_1, const void *ele_2)
{
	return *((int *)ele_1) - *((int *) ele_2);
}

int main(void)
{
	edsa_exparr *arr;
	size_t ele_num = 10;
	size_t ret_val = 0;
	int temp[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	char *fail_err = NULL;
	char *ret_str = NULL;

	edsa_exparr_init(&arr, ele_num, sizeof(int));
	for(int i = 0; i < 10; ++i){
		edsa_exparr_ins(arr, i, &(temp[i]));
	}
	ret_val = edsa_exparr_sort_segment(arr, cmp_func, 1, 0);

	if(ret_val != EDSA_EXPARR_SORT_SEGMENT_INVALID_END_INDEX){
		edsa_get_error_string(ret_val, &fail_err);
		edsa_get_error_string(EDSA_EXPARR_SORT_SEGMENT_INVALID_END_INDEX, &ret_str);
		printf("edsa_exparr_sort_segment_success.c: edsa_exparr_sort_segment failed to return %s instead returned %s\n",
		ret_str, fail_err);
		fflush(stdout);
		edsa_exparr_free(arr);
		return 1;
	}

	ret_val = edsa_exparr_sort_segment(arr, cmp_func, 1, 1);

	if(ret_val != EDSA_EXPARR_SORT_SEGMENT_INVALID_END_INDEX){
		edsa_get_error_string(ret_val, &fail_err);
		edsa_get_error_string(EDSA_EXPARR_SORT_SEGMENT_INVALID_END_INDEX, &ret_str);
		printf("edsa_exparr_sort_segment_success.c: edsa_exparr_sort_segment failed to return %s instead returned %s\n",
		ret_str, fail_err);
		fflush(stdout);
		edsa_exparr_free(arr);
		return 1;
	}

	ret_val = edsa_exparr_sort_segment(arr, cmp_func, 1, 10);

	if(ret_val != EDSA_EXPARR_SORT_SEGMENT_INVALID_END_INDEX){
		edsa_get_error_string(ret_val, &fail_err);
		edsa_get_error_string(EDSA_EXPARR_SORT_SEGMENT_INVALID_END_INDEX, &ret_str);
		printf("edsa_exparr_sort_segment_success.c: edsa_exparr_sort_segment failed to return %s instead returned %s\n",
		ret_str, fail_err);
		fflush(stdout);
		edsa_exparr_free(arr);
		return 1;
	}


	edsa_exparr_free(arr);

	return 0;
}
