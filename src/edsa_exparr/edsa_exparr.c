/*
all structers will call these arrays then profiling with determine if they need to manage there
own raw data
*/
#include <stdlib.h>
#include <string.h>
#include "edsa.h"

//error codes for static functions
enum{
	SUCCESS,
	REALLOC_FAIL,
	INDEX_TOO_LARGE
};

//new arr->arr_size is either twice the old val or size + 1 which ever is larger
//to avoid many successive calls to realloc
//if 2 * arr->arr_size * arr->data_size is too large falls back on (size + 1) * arr->data_size
//if both fail returns error
static size_t resize_array(edsa_exparr *const restrict arr, size_t size)
{
	size_t new_size;
	const size_t arr_size_double = arr->arr_size * 2;
	const size_t index_inc = size + 1;
	void *new_arr = NULL;

	//needs to be checked now because if size is the max val then if(index_inc > arr->arr_size * 2) pass when it shouldn't
	if(index_inc < size){
		return INDEX_TOO_LARGE;
	}

	if(index_inc > arr->arr_size * 2){
		goto index_size;
	}

	if(arr_size_double / 2 != arr->arr_size){
		goto index_size;
	}

	new_size = arr_size_double * arr->data_size;

	if(new_size / arr_size_double != arr->data_size){
		goto index_size;
	}

	new_arr = realloc(arr->arr, new_size);

	if(new_arr == NULL){
		goto index_size;
	}

	arr->arr_size = arr_size_double;

	goto size_found;

	index_size://executes only if arr->arr_size * 2 is unsuitable
		new_size = index_inc * arr->data_size;

		if(new_size / index_inc != arr->data_size){
			return INDEX_TOO_LARGE;
		}

		new_arr = realloc(arr->arr, new_size);

		if(new_arr == NULL){
			return REALLOC_FAIL;
		}

		arr->arr_size = index_inc;

	size_found:
		arr->arr = new_arr;

	return SUCCESS;
}

size_t edsa_exparr_init(edsa_exparr *restrict *const restrict arr, const size_t arr_size, const size_t data_size)
{
	size_t alloc_size = arr_size * data_size;

	if(alloc_size == 0){
		return EDSA_EXPARR_INIT_ZERO_ALLOC_SIZE;
	}

	if(alloc_size / data_size != arr_size){
		return EDSA_EXPARR_INIT_MULTIPLICATION_OVERFLOW;
	}

	*arr = malloc(sizeof(edsa_exparr));

	if(*arr == NULL){
		return EDSA_EXPARR_INIT_MALLOC_FAILED;
	}

	(*arr)->arr = malloc(alloc_size);

	if((*arr)->arr == NULL){
		free(*arr);

		return EDSA_EXPARR_INIT_MALLOC_FAILED;
	}

	(*arr)->arr_size = arr_size;
	(*arr)->data_size = data_size;

	return EDSA_SUCCESS;
}

//reallocs arr->arr if index would cause buffer overflow
//handels case where arr->arr_size == 0
size_t edsa_exparr_ins(edsa_exparr *const restrict arr, size_t index, void *const restrict data)
{
	if(index >= arr->arr_size){
		switch(resize_array(arr, index)){
			case INDEX_TOO_LARGE:
				return EDSA_EXPARR_INS_INDEX_TO_HIGH;
			case REALLOC_FAIL:
				return EDSA_EXPARR_INS_REALLOC_FAIL;
			case SUCCESS:
				break;
		}
	}

	//no need to check for overflow as index < arr->arr_size
	memcpy(((char *) arr->arr) + index * arr->data_size, data, arr->data_size);

	return EDSA_SUCCESS;
}

//reallocs arr if dest_index would cause buffer overflow
size_t edsa_exparr_copy(edsa_exparr *const restrict arr, size_t src_index, size_t dest_index)
{
	if(src_index >= arr->arr_size){
		return EDSA_EXPARR_COPY_INVALID_SRC_INDEX;
	}

	if(dest_index >= arr->arr_size){
		switch(resize_array(arr, dest_index)){
			case INDEX_TOO_LARGE:
				return EDSA_EXPARR_COPY_INVALID_DEST_INDEX;
			case REALLOC_FAIL:
				return EDSA_EXPARR_COPY_REALLOC_FAIL;
			case SUCCESS:
				break;
		}
	}

	if(dest_index == src_index){
		return EDSA_SUCCESS;
	}

	memcpy(((char *) arr->arr) + dest_index * arr->data_size,
	((char *) arr->arr) + src_index * arr->data_size,
	arr->data_size);

	return EDSA_SUCCESS;
}

size_t edsa_exparr_read(edsa_exparr *const restrict arr, size_t index, void *const restrict data)
{
	if(index >= arr->arr_size){
		return EDSA_EXPARR_READ_INVALID_INDEX;
	}

	memcpy(data, ((char *) arr->arr) + index * arr->data_size, arr->data_size);

	return EDSA_SUCCESS;
}

size_t edsa_exparr_sort_segment(edsa_exparr *const restrict arr, int (*cmp_func)(const void *, const void *), const size_t st_index, const size_t end_index)
{
	if(st_index <= end_index){
		return EDSA_EXPARR_SORT_SEGMENT_INVALID_END_INDEX;
	}

	if(end_index >= arr->arr_size){
		return EDSA_EXPARR_SORT_SEGMENT_INVALID_END_INDEX;
	}

	size_t segment_len = end_index - st_index;
	++segment_len;

	qsort(((char *) arr->arr) + arr->data_size * st_index, segment_len, arr->data_size, cmp_func);

	return EDSA_SUCCESS;
}

size_t edsa_exparr_free(edsa_exparr *const restrict arr)
{
	free(arr->arr);
	free(arr);

	return EDSA_SUCCESS;
}
