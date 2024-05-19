#ifndef __edsa_stack__
#define __edsa_stack__

#include <stddef.h>

typedef struct{
	size_t stack_place;//place in stack

	size_t data_size;//size of each element stored

	size_t stack_size;//number of elements allocated for the stack

	void *elements;//pointer to the element stack
}edsa_stack;

size_t edsa_stack_init(size_t type_size, size_t element_number, edsa_stack **stack);

size_t edsa_stack_push_unsafe(edsa_stack *stack, void *element);

size_t edsa_stack_push_safe(edsa_stack *stack, void *element);

size_t edsa_stack_available_elements(edsa_stack *stack, size_t *value);

size_t edsa_stack_free(edsa_stack *stack);

size_t edsa_stack_size(edsa_stack *stack, size_t *value);

size_t edsa_stack_place(edsa_stack *stack, size_t *value);

size_t edsa_stack_pop_unsafe(edsa_stack *stack, void *element);

enum __edsa_stack_error_codes__{
	EDSA_STACK_SUCCESS,//sucess
	EDSA_STACK_INIT_ZERO_ALLOC_SIZE,//stack of zero size allocation attempted
	EDSA_STACK_INIT_STACK_SIZE_MULTIPLICATION_OVERFLOW,//stack size multiplication overflowed
	EDSA_STACK_INIT_STACK_MALLOC_FAILED,//stack malloc failed
	EDSA_STACK_INIT_STACK_METADATA_MALLOC_FAILED,//stack metadata malloc failed
	EDSA_STACK_PUSH_SAFE_STACK_FULL//attempted to push to full stack

};

#endif
