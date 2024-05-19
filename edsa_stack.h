#ifndef __edsa_stack__
#define __edsa_stack__

#include <stddef.h>

typedef struct{
	size_t stack_place;//place in stack

	size_t data_size;//size of each element stored

	size_t stack_size;//number of elements allocated for the stack

	void *elements;//pointer to the element stack
}edsa_stack;

edsa_stack *edsa_stack_init(size_t type_size, size_t element_number);

void edsa_stack_free(edsa_stack *stack);

size_t edsa_stack_place(edsa_stack *stack);

#endif
