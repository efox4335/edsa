#ifndef __edsa_stack__
#define __edsa_stack__

#include <stddef.h>

typedef struct{
	size_t stack_place;//place in stack

	size_t data_size;//size of each element stored

	void *elements;//pointer to the element stack
}edsa_stack;

const char __edsa_stack_no_alloc_size__[] = "Edsa stack: stack of zero size allocation attempted\n";
const char __edsa_stack_multiplication_overflow__[] = "Edsa stack: stack size multiplication overflowed\n";
const char __edsa_stack_stack_malloc_failed__[] = "Edsa stack: stack malloc failed\n";
const char __edsa_stack_stack_data_malloc_failed__[] = "Edsa stack: stack data malloc failed\n";

#endif
