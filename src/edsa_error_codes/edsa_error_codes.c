#include <stdio.h>
#include <stddef.h>
#include "edsa_error_codes.h"

//prints error to file
size_t edsa_print_error(FILE *file, size_t error)
{
	switch(error){
		case EDSA_SUCCESS:
			fprintf(file, "no error\n");
			break;
		case EDSA_STACK_INIT_STACK_MALLOC_FAILED:
			fprintf(file, "edsa_stack_init: malloc failed on stack allocation\n");
			break;
		case EDSA_STACK_INIT_STACK_METADATA_MALLOC_FAILED:
			fprintf(file, "edsa_stack_init: malloc failed on stack metadata allocation\n");
			break;
		case EDSA_STACK_INIT_STACK_SIZE_MULTIPLICATION_OVERFLOW:
			fprintf(file, "edsa_stack_init: multiplaication on calculating stack size overflowed\n");
			break;
		case EDSA_STACK_INIT_ZERO_ALLOC_SIZE:
			fprintf(file, "edsa_stack_init: stack of zero size allocation attempted\n");
			break;
		case EDSA_STACK_POP_STACK_EMPTY:
			fprintf(file, "edsa_stack_pop: attempted to pop from empty stack\n");
			break;
		case EDSA_STACK_PUSH_STACK_FULL:
			fprintf(file, "edsa_stack_push: attempted to push to full stack\n");
			break;
		default:
			fprintf(file, "unknown error\n");
			break;
	}

	return EDSA_SUCCESS;
}

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
