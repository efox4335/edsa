/*
all structers will call these arrays then profiling with determine if they need to manage there
own raw data
*/
#include <stdlib.h>
#include <string.h>
#include "edsa_exparr.h"
#include "../edsa_error_codes/edsa_error_codes.h"

size_t edsa_exparr_init(edsa_exparr *restrict *const restrict arr, const size_t arr_size, const size_t data_size)
{
	size_t alloc_size = arr_size * data_size;

	if(alloc_size == 0){
		return EDSA_EXPARR_INTI_ZERO_ALLOC_SIZE;
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

//reallocs arr->arr if index would cause overflow
//new arr->arr_size is either twice the old val or index + 1 which ever is larger
//to avoid many successive calls to realloc
//if 2 * arr->arr_size trys * arr->data_size is too large falls back on (index + 1) * arr->data_size
//if both fail returns error
size_t edsa_exparr_ins(edsa_exparr *const restrict arr, size_t index, void *const restrict data)
{
	if(index >= arr->arr_size){
		size_t new_size;
		const size_t arr_size_double = arr->arr_size * 2;
		const size_t index_inc = index + 1;
		void *new_arr = NULL;

		if(index + 1 > arr->arr_size * 2){
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

		goto size_found;

		index_size://executes only if arr->arr_size * 2 is unsuitable
			if(index_inc < index){
				return EDSA_EXPARR_INS_INDEX_TO_HIGH;
			}

			new_size = index_inc * arr->data_size;

			if(new_size / index_inc != arr->data_size){
				return EDSA_EXPARR_INS_INDEX_TO_HIGH;
			}

			new_arr = realloc(arr->arr, new_size);

			if(new_arr == NULL){
				return EDSA_EXPARR_INS_REALLOC_FAIL;
			}

		size_found:
			arr->arr = new_arr;
	}

	//no need to check for overflow as index < arr->arr_size
	memcpy(((char *) arr->arr) + index * arr->data_size, data, arr->data_size);

	return EDSA_SUCCESS;
}

size_t edsa_exparr_free(edsa_exparr *const restrict arr)
{
	free(arr->arr);
	free(arr);

	return EDSA_SUCCESS;
}
