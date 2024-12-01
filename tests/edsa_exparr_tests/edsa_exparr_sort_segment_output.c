//sets arr in reverse order sorts segment and checks if segment is sorted and if the bounds are kept
#include "edsa.h"
#include <stdio.h>
#include <stdlib.h>

int cmp_func(const void *ele_1, const void *ele_2)
{
	return *((int *)ele_1) - *((int *) ele_2);
}

void set_arr_inv(size_t *arr, size_t size)
{
	for(size_t i = 0; i < size; ++i){
		arr[i] = size - i;
	}
}

//returns index of failed data
//returns size on pass
size_t check_arr_part(size_t *arr, size_t st_index, size_t end_index, size_t arr_size)
{
	for(size_t i = st_index; i < end_index + 1; ++i){
		if(arr[i] != arr_size - i){
			return i;
		}
	}

	return arr_size;
}

//returns second index of first unsorted pair
//returns end_index + 1 on success
//checks if arr is sorted from st_index to end_index
size_t check_sorted_part(size_t *arr, size_t st_index, size_t end_index)
{
	for(size_t i = st_index + 1; i < end_index + 1; ++i){
		if(arr[i - 1] > arr[i]){
			return i;
		}
	}

	return end_index + 1;
}

int main(void)
{
	enum{DATA_AMOUNT = 1000, SEGMENT_OFFSET = 34};

	size_t ret_val = 0;
	edsa_exparr *arr;
	size_t data[DATA_AMOUNT];

	set_arr_inv(data, DATA_AMOUNT);

	edsa_exparr_init(&arr, 1, sizeof(size_t));
	for(size_t i = 0; i < DATA_AMOUNT; ++i){
		edsa_exparr_ins(arr, i, &(data[i]));
	}

	edsa_exparr_sort_segment(arr, cmp_func, SEGMENT_OFFSET, DATA_AMOUNT - SEGMENT_OFFSET - 1);

	for(size_t i = 0; i < DATA_AMOUNT; ++i){
		edsa_exparr_read(arr, i, &(data[i]));
	}

	ret_val = check_arr_part(data, 0, SEGMENT_OFFSET - 1, DATA_AMOUNT);

	if(ret_val != DATA_AMOUNT){
		printf("edsa_exparr_sort_segment_output.c: edsa_exparr_sort_segment failed to pass back correct data at index %ld\n",
		ret_val);
		fflush(stdout);
		edsa_exparr_free(arr);
		return 1;
	}

	ret_val = check_arr_part(data, DATA_AMOUNT - SEGMENT_OFFSET, DATA_AMOUNT - 1, DATA_AMOUNT);

	if(ret_val != DATA_AMOUNT){
		printf("edsa_exparr_sort_segment_output.c: edsa_exparr_sort_segment failed to pass back correct data at index %ld\n",
		ret_val);
		fflush(stdout);
		edsa_exparr_free(arr);
		return 1;
	}

	ret_val = check_sorted_part(data, SEGMENT_OFFSET, DATA_AMOUNT - SEGMENT_OFFSET - 1);

	if(ret_val != DATA_AMOUNT - SEGMENT_OFFSET){
		printf("edsa_exparr_sort_segment_output.c: edsa_exparr_sort_segment failed to pass back correct sorted data at index %ld\n",
		ret_val);
		fflush(stdout);
		edsa_exparr_free(arr);
		return 1;
	}

	edsa_exparr_free(arr);
	return 0;
}
