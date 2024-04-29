#ifndef __edsa_stack__
#define __edsa_stack__

#include <stddef.h>

typedef struct{
	size_t stack_place;//place in stack

	size_t data_size;//size of each element stored

	void *elements;//pointer to the element stack
}edsa_stack;
#endif
