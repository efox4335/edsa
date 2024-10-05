/*
all structers will call these arrays then profiling with determine if they need to manage there
own raw data
*/
#include <stdlib.h>
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
