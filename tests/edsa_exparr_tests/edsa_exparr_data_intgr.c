//data is set to integers between 1 and ARR_SIZE
#include "../../src/edsa.h"
#include <stdio.h>

void set_arr(size_t *arr, size_t size)
{
	for(size_t i = 0; i < size; ++i){
		arr[i] = i;
	}
}

//returns index of failed data
//returns size on pass
size_t check_arr(size_t *arr, size_t size)
{
	for(size_t i = 0; i < size; ++i){
		if(arr[i] != i){
			return i;
		}
	}

	return size;
}

void reset_arr(size_t *arr, size_t size)
{
	for(size_t i = 0; i < size; ++i){
		arr[i] = -1;
	}
}

int main(void)
{
	enum {ARR_SIZE = 1000};
	size_t arr[ARR_SIZE];

	set_arr(arr, ARR_SIZE);

	edsa_exparr *exparr;

	//arr_size arg set low to test expansion of arr
	edsa_exparr_init(&exparr, 10, sizeof(size_t));

	size_t ret_val = EDSA_SUCCESS;
	char *fail_err = NULL;
	char *ret_str = NULL;

	for(size_t i = 0; i < ARR_SIZE; ++i){
		ret_val = edsa_exparr_ins(exparr, i, arr + i);

		if(ret_val != EDSA_SUCCESS){
			edsa_get_error_string(ret_val, &fail_err);
			edsa_get_error_string(EDSA_SUCCESS, &ret_str);
			printf("edsa_exparr_data_intgr.c: edsa_exparr_ins failed to return %s instead returned %s\n",
			ret_str, fail_err);
			fflush(stdout);
			return 1;
		}
	}

	//to ensure that check_arr will fail if edsa_exparr_read does nothing
	reset_arr(arr, ARR_SIZE);

	for(size_t i = 0; i < ARR_SIZE; ++i){
		ret_val = edsa_exparr_read(exparr, i, arr + i);

		if(ret_val != EDSA_SUCCESS){
			edsa_get_error_string(ret_val, &fail_err);
			edsa_get_error_string(EDSA_SUCCESS, &ret_str);
			printf("edsa_exparr_data_intgr.c: edsa_exparr_read failed to return %s instead returned %s\n",
			ret_str, fail_err);
			fflush(stdout);
			return 1;
		}
	}

	size_t fail_index = check_arr(arr, ARR_SIZE);

	if(fail_index != ARR_SIZE){
		printf("edsa_exparr_data_intgr.c: edsa_exparr_read failed to pass back correct data at index %ld\n",
		fail_index);
		fflush(stdout);
		return 1;
	}

	edsa_exparr_free(exparr);

	return 0;
}
