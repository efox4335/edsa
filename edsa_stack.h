#ifndef __edsa_stack__
#define __edsa_stack__

#include <stddef.h>

typedef struct{
	size_t stack_place;//place in stack

	size_t data_size;//size of each element stored

	void *elements;//pointer to the element stack
}edsa_stack;

const char __edsa_stack_init_no_alloc_size__[] = "edsa_stack_init: stack of zero size allocation attempted\n";
const char __edsa_stack_init_multiplication_overflow__[] = "edsa_stack_init: stack size multiplication overflowed\n";
const char __edsa_stack_init_stack_malloc_failed__[] = "edsa_stack_init: stack malloc failed\n";
const char __edsa_stack_init_stack_data_malloc_failed__[] = "edsa_stack_init: stack data malloc failed\n";

#endif
