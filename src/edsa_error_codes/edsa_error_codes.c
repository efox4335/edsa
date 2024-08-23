#include <stddef.h>
#include "edsa_error_codes.h"

//gets corresponding error string from code
size_t edsa_get_error_string(size_t error, char **str)
{
	switch(error){
		case EDSA_SUCCESS:
			*str = "EDSA_SUCCESS\n";
			break;
		case EDSA_STACK_INIT_STACK_MALLOC_FAILED:
			*str = "EDSA_STACK_INIT_STACK_MALLOC_FAILED\n";
			break;
		case EDSA_STACK_INIT_STACK_METADATA_MALLOC_FAILED:
			*str = "EDSA_STACK_INIT_STACK_METADATA_MALLOC_FAILED\n";
			break;
		case EDSA_STACK_INIT_STACK_SIZE_MULTIPLICATION_OVERFLOW:
			*str = "EDSA_STACK_INIT_STACK_SIZE_MULTIPLICATION_OVERFLOW\n";
			break;
		case EDSA_STACK_INIT_ZERO_ALLOC_SIZE:
			*str = "EDSA_STACK_INIT_ZERO_ALLOC_SIZE\n";
			break;
		case EDSA_STACK_POP_STACK_EMPTY:
			*str = "EDSA_STACK_POP_STACK_EMPTY\n";
			break;
		case EDSA_STACK_PUSH_STACK_FULL:
			*str = "EDSA_STACK_PUSH_STACK_FULL\n";
			break;
		default:
			*str = "UNKNOWN_ERROR\n";
			break;

	}

	return EDSA_SUCCESS;
}
