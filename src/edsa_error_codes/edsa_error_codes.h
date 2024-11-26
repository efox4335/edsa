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
	EDSA_EXPARR_INIT_ZERO_ALLOC_SIZE,
	EDSA_EXPARR_INIT_MALLOC_FAILED,
	EDSA_EXPARR_INIT_MULTIPLICATION_OVERFLOW,
	EDSA_EXPARR_INS_INDEX_TO_HIGH,
	EDSA_EXPARR_INS_REALLOC_FAIL,
	EDSA_EXPARR_READ_INVALID_INDEX,
	EDSA_EXPARR_COPY_INVALID_SRC_INDEX,
	EDSA_EXPARR_COPY_INVALID_DEST_INDEX,
	EDSA_EXPARR_COPY_REALLOC_FAIL,
	EDSA_HEAP_INIT_MALLOC_FAILED,
	EDSA_HEAP_INIT_ZERO_ALLOC_SIZE,
	EDSA_HEAP_INIT_MULTIPLICATION_OVERFLOW,
	EDSA_HEAP_INS_HEAP_FULL,
	EDSA_HEAP_INS_REALLOC_FAIL,
	EDSA_HEAP_INS_MALLOC_FAIL,
	EDSA_HEAP_REMOVE_MALLOC_FAIL,
	EDSA_HEAP_REMOVE_HEAP_EMPTY,
	EDSA_HEAP_REPLACE_HEAP_EMPTY,
	EDSA_HEAP_REPLACE_MALLOC_FAIL,
	EDSA_HEAP_BUILD_REALLOC_FAIL,
	EDSA_HEAP_BUILD_MALLOC_FAIL,
	EDSA_HEAP_BUILD_AMOUNT_TO_HIGH,
	EDSA_HEAP_CHANGE_CMP_FUNC_MALLOC_FAIL,
	EDSA_HTABLE_INIT_MALLOC_FAIL,
	EDSA_HTABLE_INIT_HTABLE_SIZE_TOO_LARGE,
	EDSA_HTABLE_INIT_HTABLE_SIZE_ZERO,
	EDSA_HTABLE_INIT_REALLOC_FAIL,
	EDSA_HTABLE_INS_HTABLE_TOO_LARGE,
	EDSA_HTABLE_INS_MALLOC_FAIL,
	EDSA_HTABLE_INS_REALLOC_FAIL,
	EDSA_HTABLE_READ_NO_ENTRY,
	EDSA_HTABLE_READ_MALLOC_FAIL,
	EDSA_HTABLE_REMOVE_NO_ENTRY,
	EDSA_HTABLE_REMOVE_MALLOC_FAIL
};


#endif
