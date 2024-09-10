#ifndef __edsa_stack__
#define __edsa_stack__

#include <stddef.h>

typedef struct{
	size_t stack_place;//place in stack
	size_t data_size;//size of each element stored
	size_t stack_size;//number of elements allocated for the stack
	void *elements;//pointer to the element stack
}edsa_stack;

size_t edsa_stack_init(const size_t type_size, const size_t element_number, edsa_stack **const restrict stack);
size_t edsa_stack_push(edsa_stack *const restrict stack, void *const restrict element);
size_t edsa_stack_available_elements(edsa_stack *const restrict stack, size_t *const restrict value);
size_t edsa_stack_free(edsa_stack *const restrict stack);
size_t edsa_stack_size(edsa_stack *const restrict stack, size_t *const restrict value);
size_t edsa_stack_place(edsa_stack *const restrict stack, size_t *const restrict value);
size_t edsa_stack_pop(edsa_stack *const restrict stack, void *const restrict element);
size_t edsa_stack_realloc(edsa_stack *const restrict stack, const size_t new_size);


#endif
