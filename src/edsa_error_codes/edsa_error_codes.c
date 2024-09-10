#include <stddef.h>
#include "edsa_error_codes.h"

//gets corresponding error string from code
size_t edsa_get_error_string(size_t error, char **str)
{
	switch(error){
		case EDSA_SUCCESS:
			*str = "EDSA_SUCCESS";
			break;
		case EDSA_STACK_INIT_STACK_MALLOC_FAILED:
			*str = "EDSA_STACK_INIT_STACK_MALLOC_FAILED";
			break;
		case EDSA_STACK_INIT_STACK_METADATA_MALLOC_FAILED:
			*str = "EDSA_STACK_INIT_STACK_METADATA_MALLOC_FAILED";
			break;
		case EDSA_STACK_INIT_STACK_SIZE_MULTIPLICATION_OVERFLOW:
			*str = "EDSA_STACK_INIT_STACK_SIZE_MULTIPLICATION_OVERFLOW";
			break;
		case EDSA_STACK_INIT_ZERO_ALLOC_SIZE:
			*str = "EDSA_STACK_INIT_ZERO_ALLOC_SIZE";
			break;
		case EDSA_STACK_POP_STACK_EMPTY:
			*str = "EDSA_STACK_POP_STACK_EMPTY";
			break;
		case EDSA_STACK_PUSH_STACK_FULL:
			*str = "EDSA_STACK_PUSH_STACK_FULL";
			break;
		case EDSA_STACK_REALLOC_FAILED:
			*str = "EDSA_STACK_REALLOC_FAILED";
			break;
		default:
			*str = "UNKNOWN_ERROR";
			break;

	}

	return EDSA_SUCCESS;
}
