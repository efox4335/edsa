#include <stddef.h>

#ifndef __edsa_error_codes__
#define __edsa_error_codes__

size_t edsa_get_error_string(size_t error, char **str);

enum __edsa_error_codes__{
	EDSA_SUCCESS,//sucess
	EDSA_STACK_INIT_ZERO_ALLOC_SIZE,//stack of zero size allocation attempted
	EDSA_STACK_INIT_STACK_SIZE_MULTIPLICATION_OVERFLOW,//stack size multiplication overflowed
	EDSA_STACK_INIT_STACK_MALLOC_FAILED,//stack malloc failed
	EDSA_STACK_INIT_STACK_METADATA_MALLOC_FAILED,//stack metadata malloc failed
	EDSA_STACK_PUSH_STACK_FULL,//attempted to push to full stack
	EDSA_STACK_POP_STACK_EMPTY,//attempted to pop empty stack
	EDSA_STACK_REALLOC_FAILED,//realloc failed
	EDSA_EXPARR_INTI_ZERO_ALLOC_SIZE,
	EDSA_EXPARR_INIT_MALLOC_FAILED,
	EDSA_EXPARR_INIT_MULTIPLICATION_OVERFLOW
};


#endif
